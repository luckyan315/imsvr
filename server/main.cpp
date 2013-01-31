#include <iostream>
#include <boost/asio.hpp>


class Client
{
public:
    Client(boost::asio::io_service & ios, const char * ip, const int port)
    :m_ios(ios), m_ip(ip), m_port(port)
    {

    }
    ~Client()
    {

    }
    void Run()
    {
        ip::address addr = ip::address::from_string(m_ip);
        ip::tcp::socket
    }
private:
    boost::asio::io_service & m_ios;
    const char * m_ip;
    const int m_port;
};


void test_client()
{
    const char * ip = "127.0.0.1";
    const int port = 10883;
    Client c(ip, port);
    c.Run();
}

int main(int argc, char * argv[])
{
    test_client();
    return 0;
}
