#include "Server.h"

#include "Log.h"
#include "SessionManager.h"
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

    SessionManager * sm = SessionManager::Instance();
    
    LOG_DEBUG("online clients number is : [%d]", sm->size());
    
    Session::PtrType pses(new Session(m_ios));
    sm->AddSession(pses);

    m_acceptor.async_accept(pses->socket(), 
        boost::bind(&Server::handle_accept, this, pses, 
        boost::asio::placeholders::error));
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
