#include "SimpleProtocol.h"
#include <cassert>
#include "Log.h"
#include <boost/lexical_cast.hpp>


namespace imsvr{
namespace protocol{

int SimpleProtocol::Building(char * buf, int cap)
{
    assert(buf && cap > HEAD_LEN);
    // check rule
    if(m_sender.size() > 0  && m_receiver.size() > 0 
        && m_reply.size() > 0 && m_content.size() > 0  && m_send_time.size() > 0 
        && m_content.size() <= GetMaxContentLength()
        && cap > m_content.size() + HEAD_LEN
        )
    {
        int msg_len = snprintf(buf + 4, cap - 4, "%10s%10s%10s%14s%04zd%s", m_sender.c_str(), m_receiver.c_str()
            ,m_reply.c_str(), m_send_time.c_str(), m_content.size(), m_content.c_str());
        if(msg_len >= cap - 4)
        {
            LOG_ERROR("msg buffer is too short ");
            return ERR_BUFFER_TOO_SHORT;
        }
        // fill the msg_len field
        for(int i = 3, tmp = msg_len; i >= 0; --i)
        {
            buf[i] =  (char)(tmp%10 + 0x30);
            tmp /= 10;
        }
        return msg_len + 4;
    }

    LOG_ERROR("sender, receiver, reply, content must existing, and content <= MaxContentLength, and buf size > content_length + head_len");
    return -1;
}
int SimpleProtocol::Parse(const char * buf, int sz, SimpleProtocol & prtcl)
{
    assert(buf && sz >= 0 && sz <= MAX_MSG_LEN  + 4);
    if(sz <  4)
        return ERR_BUFFER_TOO_SHORT;

    int len = boost::lexical_cast<int>(std::string(buf, buf + 4));
    if(len < 48 )
        return  ERR_BUFFER_TOO_SHORT;
    
    prtcl.SetSender(buf + 4, buf + 14);
    prtcl.SetReceiver(buf + 14,  buf + 24);
    prtcl.SetReply(buf + 24, buf + 34);
    prtcl.SetSendTime(buf + 34, buf + 48);

    len = boost::lexical_cast<int>(std::string(buf + 48, buf + 52));
    if(len != sz - 52)
        return ERR_INVALID_MSG_CONTENT;

    prtcl.SetContent(buf + 52 , buf + 52 + len);
    return 0;
}

void SimpleProtocol::SetSender(const char * start, const char * end)
{
    assert(start && end && start < end);
    m_sender.assign(start, end);
}
void SimpleProtocol::SetReceiver(const char * start, const char * end)
{
    assert(start && end && start < end);
    m_receiver.assign(start, end);
}
void SimpleProtocol::SetReply(const char * start, const char * end)
{
    assert(start && end && start < end);
    m_reply.assign(start, end);
}
void SimpleProtocol::SetContent(const char * start, const char * end)
{
    assert(start && end && start < end);
    m_content.assign(start, end);
}
void SimpleProtocol::SetSendTime(const char * start, const char * end)
{
    assert(start && end && start < end);
    m_send_time.assign(start, end);
}
void SimpleProtocol::SetSender(std::string sender)
{
    if(sender != m_sender)
        m_sender = sender;
}
void SimpleProtocol::SetReceiver(std::string receiver)
{
    if(receiver != m_receiver)
        m_receiver = receiver;
}
void SimpleProtocol::SetReply(std::string reply)
{
    if(reply != m_reply)
        m_reply = reply;
}
void SimpleProtocol::SetSendTime(std::string send_time)
{
    if(send_time != m_send_time)
        m_send_time = send_time;
}
void SimpleProtocol::SetContent(std::string content)
{
    if(content != m_content)
        m_content = content;
}

} /*  namespace protocol */
} /*  namespace imsvr */
