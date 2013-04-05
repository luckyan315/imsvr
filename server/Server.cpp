#include "Server.h"

#include <boost/lexical_cast.hpp>

#include "Log.h"
#include "SessionManager.h"
#include "IDGenerator.h"

namespace imsvr{
namespace server{

using namespace imsvr::common;

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
    std::string id;
    IDGenerator::Next(id);

    SessionManager * sm = SessionManager::Instance();
    assert(sm);

    LOG_DEBUG("online clients number is : [%d], next id[%s]", sm->size(), id.c_str());
    Session::PtrType pses(new Session(m_ios, id));
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
