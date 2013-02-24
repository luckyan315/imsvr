#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
class Client{

public:
    Client(const char * ip, const char * port);

    void    send(const std::string& msg);

private:
    void    handleConnect(const boost::system::error_code& error);
    void    Run();
    void    handleSend(const boost::system::error_code& error);
    void    close();

private:
    boost::asio::io_service& m_ioservice;
    tcp::socket              m_sock;

};
#endif // CLIENT_H
