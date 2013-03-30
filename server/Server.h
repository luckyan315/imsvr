
#ifndef  SERVER_H
#define  SERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Session.h"

namespace imsvr{
namespace server{

class Server    
{
public:
    Server(boost::asio::io_service & ios, const int port);
    ~Server();

    void Run();

protected:
    void handle_accept(Session::PtrType psess, const boost::system::error_code  & error);

private:
    boost::asio::io_service & m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
};

} /*  namespace protocol */
} /*  namespace imsvr */

#endif   /* SERVER_H */
