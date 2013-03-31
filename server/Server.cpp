#include "Server.h"

#include "Log.h"
#include "SessionManager.h"

#include <boost/lexical_cast.hpp>

namespace imsvr{
namespace server{


Server::Server(boost::asio::io_service & ios, const int port)
    :m_ios(ios)
    , m_acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
}
Server::~Server()
{
}

void Server::Run()
{
    static int id = 10000; //TODO : alloca the tmp id, after register and replace the real_id with tmp id

    SessionManager * sm = SessionManager::Instance();
    assert(sm);

    LOG_DEBUG("online clients number is : [%d], next id[%d]", sm->size(), id);
    Session::PtrType pses(new Session(m_ios, boost::lexical_cast<std::string>(id))); //TODO:
    sm->AddSession(pses);

    m_acceptor.async_accept(pses->socket(), 
        boost::bind(&Server::handle_accept, this, pses, 
        boost::asio::placeholders::error));

    ++id;
}
void Server::handle_accept(Session::PtrType pses, const boost::system::error_code  & error)
{
    if(!error)
    {
        LOG_DEBUG("accept one client!");
        pses->Run();
    }
    Run();
}

} /*  namespace server */
} /*  namespace imsvr */
