#include "Session.h"

#include <boost/bind.hpp>

#include "Log.h"
#include "SessionManager.h"
#include "SimpleProtocol.h"
#include "Util.h"


#define SERVER_ID       "9999990000"
#define LOGIN_MSG       "LOGIN"
#define LOGOUT_MSG      "LOGOUT"

namespace imsvr{
namespace server{

Session::Session(boost::asio::io_service & ios, const IDType & id)
    :m_id(id)
    ,m_status(NewConnected)
    , m_ios(ios), m_sock(ios)
    , m_read_buf(new char[MAX_BUF_SZ]), m_write_buf(new char[MAX_BUF_SZ])
    , m_read_ptr(0)
    , m_proto(new imsvr::protocol::SimpleProtocol)
{
    memset(m_read_buf, 0, sizeof(m_read_buf));
    memset(m_write_buf, 0, sizeof(m_write_buf));
}

Session::~Session()
{
    LOG_DEBUG("Session Free");
    delete m_write_buf; m_write_buf = NULL;
    delete m_read_buf;       m_read_buf = NULL;
}
void Session::Run()
{
    memset(m_read_buf, 0, sizeof(m_read_buf));
    m_read_ptr = 0;
    boost::asio::async_read(m_sock, 
        boost::asio::buffer(m_read_buf, MAX_BUF_SZ*sizeof(char)),
        boost::asio::transfer_exactly(4),
        boost::bind(&Session::HandleRead, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Session::Send(const char * buf, size_t sz)
{
    assert(buf);
    sz = sz > MAX_BUF_SZ ? MAX_BUF_SZ : sz;
    memcpy(m_write_buf, buf,  sz);

    boost::asio::async_write(m_sock,
            boost::asio::buffer(m_write_buf, sz),
            boost::bind(&Session::HandleWrite, shared_from_this(),
                boost::asio::placeholders::error));
}


void Session::HandleRead(const boost::system::error_code & error
    , const std::size_t & bytes_transferred)
{
    if(error != 0 || bytes_transferred == 0)
    {
        LOG_DEBUG("Got en error when read data");
        SessionManager::Instance()->RemoveSession(shared_from_this());
        return ;
    }

    if(m_read_ptr == 0)
    {
        LOG_DEBUG("Continue Read data is :[%s], bytes_transferred (%zd)", m_read_buf, bytes_transferred);
        int len = imsvr::common::Util::toInt(m_read_buf, m_read_buf + 4);
        LOG_DEBUG("New Read msg Len is %d", len);
        if(len > 0)
        {
            boost::asio::async_read(m_sock, 
                boost::asio::buffer(m_read_buf + 4, MAX_BUF_SZ*sizeof(char)),
                boost::asio::transfer_exactly(len),
                boost::bind(&Session::HandleRead, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
            m_read_ptr += 4;
        }
        else // read failed reset 
        {
            LOG_DEBUG("Msg is not invalid, len(%d)", len);
            this->Run();
        }
    }
    else
    {
#if 1
        if( 0 == m_proto->Parse(m_read_buf, bytes_transferred))
        {
            HandleMsg();
        }
        else
        {
            LOG_ERROR("invalid msg format to parsed!");
        }
#else 
        this->Send(m_read_buf, strlen(m_read_buf));
#endif
        this->Run();
    }
}
void Session::HandleWrite(const boost::system::error_code & error)
{
    if(!error)
    {
        LOG_DEBUG("Write OK!");
    }
    else
    {
        LOG_ERROR("Got an error when write data");
        SessionManager::Instance()->RemoveSession(shared_from_this());
    }
}
void Session::HandleMsg()
{
    switch(m_status)
    {
        case NewConnected:
            LOG_DEBUG("HandleMsg : New Connected");
            HandleNewConnected();
        break;
        case Logged:
            LOG_DEBUG("HandleMsg : Logged");
            HandleLogged();
        break;
        case Logout:
            LOG_DEBUG("HandleMsg : Logout");
            HandleLogout();
        break;
        default:
            LOG_ERROR("status error!");
        break;
    }
}
void Session::HandleLogged()
{
    LOG_DEBUG("Client login msg");
    if(m_proto->GetReceiver() == SERVER_ID)
    {
        LOG_ERROR("Server Manager Command: no effect");
    }
    else
    {
        LOG_DEBUG("Client msg request sender %s recv %s", m_proto->GetSender().c_str(), m_proto->GetReceiver().c_str());
        std::string id = imsvr::common::Util::trimEnd(m_proto->GetReceiver());
        Session::PtrType pses = SessionManager::Instance()->FindSession(id);
        if(pses != NULL)
            pses->Send(m_read_buf, m_proto->GetMsgLength());
        else
            LOG_DEBUG("cant not find the session, Id(%s)", m_proto->GetReceiver().c_str());
    }
}
void Session::HandleNewConnected()
{
    if(m_proto->GetReceiver() == SERVER_ID && m_proto->GetContent() == LOGIN_MSG)
    {
        LOG_DEBUG("Client call for login");
        //TODO:Validate the id & password
        SessionManager::Instance()->MoveSession(shared_from_this(), m_proto->GetSender());
        m_status = Logged; 
    }
}
void Session::HandleLogout()
{
    if(m_proto->GetReceiver() == SERVER_ID && m_proto->GetContent() == LOGOUT_MSG)
    {
        LOG_DEBUG("Client call for logout");
        SessionManager::Instance()->RemoveSession(shared_from_this());
        m_status = Logout;
    }
}

} /*  namespace server */
} /*  namespace imsvr */
