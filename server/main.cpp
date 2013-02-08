#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Session.h"

using namespace boost::asio;

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
