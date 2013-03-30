#include "Session.h"

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "Log.h"

#include "SessionManager.h"

namespace imsvr{
namespace server{

int Session::id = 10000;

Session::Session(boost::asio::io_service & ios)
    :m_ios(ios), m_sock(ios), m_read_buf(new char[MAX_BUF_SZ]), m_write_buf(new char[MAX_BUF_SZ])
{
    memset(m_read_buf, 0, sizeof(m_read_buf));
    memset(m_write_buf, 0, sizeof(m_write_buf));
    m_id = boost::lexical_cast<std::string>(id); //TODO:TmpID
    ++id; 
}

Session::~Session()
{
    LOG_DEBUG("Session Free");
    delete m_write_buf; m_write_buf = NULL;
    delete m_read_buf;       m_read_buf = NULL;
}
void Session::Run()
{
    boost::asio::async_read(m_sock, 
        boost::asio::buffer(m_read_buf, sizeof(m_read_buf)),
        boost::asio::transfer_at_least(1),
        boost::bind(&Session::HandleRead, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Session::Send(const char * buf, size_t sz)
{
    assert(buf);
    sz = sz > MAX_BUF_SZ ? MAX_BUF_SZ : sz;
    memcpy(m_write_buf, buf,  sz);

    boost::asio::async_write(m_sock,
            boost::asio::buffer(m_write_buf, sz),
            boost::bind(&Session::HandleWrite, this,
                boost::asio::placeholders::error));
}
void Session::HandleRead(const boost::system::error_code & error
    , const std::size_t & bytes_transferred)
{
    if(!error && bytes_transferred > 0)
    {
        LOG_DEBUG("Read data is :[%s]", m_read_buf);

        //TODO: Send to another Client
        this->Send(m_read_buf, bytes_transferred); 

        memset(m_read_buf, 0, sizeof(m_read_buf));
        boost::asio::async_read(m_sock, 
            boost::asio::buffer(m_read_buf, sizeof(m_read_buf)),
            boost::asio::transfer_at_least(1),
            boost::bind(&Session::HandleRead, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        LOG_DEBUG("Got en error when read data");
        SessionManager::Instance()->RemoveSession(m_id);
    }
}
void Session::HandleWrite(const boost::system::error_code & error)
{
    if(!error)
    {
        LOG_DEBUG("Write OK!");
    }
    else
    {
        LOG_ERROR("Got an error when write data");
        SessionManager::Instance()->RemoveSession(m_id);
    }
}

} /*  namespace server */
} /*  namespace imsvr */
