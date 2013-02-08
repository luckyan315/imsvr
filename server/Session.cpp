
#include "Session.h"
#include <boost/bind.hpp>

using namespace boost::asio;

Session::Session(io_service & ios, ip::tcp::socket & sock, const char * rip, const int rport)
:m_ios(ios), m_sock(sock), m_rip(rip), m_rport(rport)
, m_write_buf_len(1024), m_read_buf_len(1024)
{
    m_write_buf = new char[m_write_buf_len];
    m_read_buf = new char[m_read_buf_len];
}
Session::~Session()
{
    if(m_write_buf)
    {
        delete m_write_buf;  m_write_buf = NULL;
    }
    if(m_read_buf)
    {
        delete m_read_buf; m_read_buf = NULL;
    }
}

void Session::StartEcho()
{
    memcpy(m_write_buf, "string\n", 7);
    m_sock.async_send(buffer(m_write_buf, 7)
            , boost::bind(&Session::Write, this, placeholders::error));
}

void Session::Write(const boost::system::error_code & error)
{
    if(!error)
    {
        std::cout << "write OK" << std::endl;
        m_sock.async_receive(buffer(m_read_buf, m_read_buf_len)
            , boost::bind(&Session::Read, this, placeholders::error, placeholders::bytes_transferred));
    }
    else
    {
        std::cout << "write Failed!" << std::endl;
    }
}

void Session::Read(const boost::system::error_code & error, size_t bytes_transferred)
{
    if(!error)
    {
        std::cout << "Read OK" << std::endl;
        std::cout << m_read_buf; 
        memcpy(m_write_buf, m_read_buf, bytes_transferred);
        m_sock.async_send(buffer(m_write_buf, bytes_transferred), boost::bind(&Session::Write, this, placeholders::error));
    }
    else
    {
        std::cout << "Read Failed" << std::endl;
    }
}
