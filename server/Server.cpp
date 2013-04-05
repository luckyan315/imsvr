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
    LOG_DEBUG("Server is ready to accept client, and Next id[%s]", id.c_str());
    Session::PtrType pses(new Session(m_ios, id));

    m_acceptor.async_accept(pses->socket(), 
        boost::bind(&Server::handle_accept, this, pses, 
        boost::asio::placeholders::error));
}
void Server::handle_accept(Session::PtrType pses, const boost::system::error_code  & error)
{
    if(!error)
    {
        SessionManager * sm = SessionManager::Instance();
        LOG_DEBUG("Online size (%d), and accept one client!", sm->size());

        sm->AddNewSession(pses);
        pses->Run();
    }
    Run();
}

} /*  namespace server */
} /*  namespace imsvr */
