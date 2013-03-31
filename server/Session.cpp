#include "Session.h"

#include <boost/bind.hpp>

#include "Log.h"
#include "SessionManager.h"
#include "SimpleProtocol.h"
#include "Util.h"

namespace imsvr{
namespace server{

Session::Session(boost::asio::io_service & ios, const IDType & id)
    :m_id(id)
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
        boost::bind(&Session::HandleRead, this,
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
            boost::bind(&Session::HandleWrite, this,
                boost::asio::placeholders::error));
}


void Session::HandleRead(const boost::system::error_code & error
    , const std::size_t & bytes_transferred)
{
    if(error != 0 || bytes_transferred == 0)
    {
        LOG_DEBUG("Got en error when read data");
        SessionManager::Instance()->RemoveSession(m_id);
        return ;
    }

    if(m_read_ptr == 0)
    {
        LOG_DEBUG("Continue Read data is :[%s], bytes_transferred (%zd)", m_read_buf, bytes_transferred);
        int len = imsvr::common::Util::toInt(m_read_buf, m_read_buf + 4);
        LOG_DEBUG("len is %d", len);
        if(len > 0)
        {
            boost::asio::async_read(m_sock, 
                boost::asio::buffer(m_read_buf + 4, MAX_BUF_SZ*sizeof(char)),
                boost::asio::transfer_exactly(len),
                boost::bind(&Session::HandleRead, this,
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
            SessionManager * sm = SessionManager::Instance();
            std::string id = m_proto->GetReceiver();
            Session::PtrType pses = sm->FindSession(imsvr::common::Util::trimEnd(id));
            if(pses != NULL)
                pses->Send(m_read_buf, bytes_transferred+4); 
            else
                LOG_DEBUG("cant not find the session, Id(%s)", m_proto->GetReceiver().c_str());
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
        SessionManager::Instance()->RemoveSession(m_id);
    }
}

} /*  namespace server */
} /*  namespace imsvr */
