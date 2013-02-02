#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;

class Session
{
public:
    Session(io_service & ios, ip::tcp::socket & sock, const char * rip, const int rport)
    :m_ios(ios), m_sock(sock), m_rip(rip), m_rport(rport)
    , m_write_buf_len(1024), m_read_buf_len(1024)
    {
        m_write_buf = new char[m_write_buf_len];
        m_read_buf = new char[m_read_buf_len];
    }
    ~Session()
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

    void StartEcho()
    {
        memcpy(m_write_buf, "string\n", 7);
        m_sock.async_send(buffer(m_write_buf, 7)
                , boost::bind(&Session::Write, this, placeholders::error));
    }

    void Write(const boost::system::error_code & error)
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

    void Read(const boost::system::error_code & error, size_t bytes_transferred)
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
private:
    io_service & m_ios;
    ip::tcp::socket & m_sock;
    const char * m_rip;
    const int m_rport;
    char * m_write_buf;
    size_t m_write_buf_len;
    char * m_read_buf;
    size_t m_read_buf_len;
};
class Client
{
public:
    Client(io_service & ios, const char * ip, const int port)
    :m_ios(ios), m_sock(ios), m_ip(ip), m_port(port)
    , m_session(NULL)
    {
    }
    ~Client()
    {
        if(m_session)
        {
            delete m_session; m_session = NULL;
        }
        m_sock.close();
    }
    void Run()
    {
        if(!m_sock.is_open())
        {
            m_sock.open(ip::tcp::v4());
        }
        m_sock.async_connect(ip::tcp::endpoint(ip::address::from_string(m_ip), m_port)
        , boost::bind(&Client::Connected, this, placeholders::error));

        m_ios.run();

    }
    void Connected(const boost::system::error_code & error)
    {
        if(!error)
        {
            std::cout << "connected!" << std::endl;
            //Create Session & Save it into Session Manager
            m_session = new Session(m_ios, m_sock, m_ip, m_port);
            m_session->StartEcho();
        }
        else
        {
            std::cout << "Connected failed, " <<  error << std::endl;
        }
    }
    
private:
    io_service & m_ios;
    Session * m_session;
    ip::tcp::socket m_sock; 
    const char * m_ip;
    const int m_port;
};


void test_client()
{
    const char * ip = "127.0.0.1";
    const int port = 5800;
    io_service ios;
    Client c(ios, ip, port);
    c.Run();
}

int main(int argc, char * argv[])
{
    test_client();
    return 0;
}
