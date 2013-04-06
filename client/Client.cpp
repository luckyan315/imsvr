#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "Client.h"

Client::Client(const char *ip, const char *port):
    m_ioservice(*new boost::asio::io_service()), m_sock(m_ioservice)
{
    try
    {
        tcp::resolver _resolver(m_ioservice);
        tcp::resolver::query query(tcp::v4(), ip, port);
        tcp::resolver::iterator _iterator = _resolver.resolve(query);

        boost::asio::async_connect(m_sock, _iterator,
            boost::bind(&Client::handleConnect, this,
              boost::asio::placeholders::error));
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    Run();
}

void Client::Run()
{
    boost::thread job(boost::bind(&boost::asio::io_service::run, &m_ioservice));
    job.join();
}

void Client::handleConnect(const boost::system::error_code& error)
{
    if(!error)
    {
        std::cout<<"Connect Success!"<<std::endl;
    }
    else
    {
        std::cout<<"Connect Failed"<<std::endl;
    }
}

void Client::send(const std::string& msg)
{
    std::cout<<"Client::send():"<<msg<<std::endl;
    boost::asio::async_write(m_sock,
        boost::asio::buffer(msg.c_str(),
          msg.length()),
        boost::bind(&Client::handleSend, this,
          boost::asio::placeholders::error));
}

void Client::handleSend(const boost::system::error_code& error)
{
    if(!error)
    {
        std::cout<<"Send Success!"<<std::endl;
    }
    else
    {
        close();
    }
}

void Client::close()
{
    m_sock.close();
}
