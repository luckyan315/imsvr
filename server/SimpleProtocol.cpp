#include "SimpleProtocol.h"
#include <cassert>
#include "Log.h"


namespace imsvr{
namespace protocol{

int SimpleProtocol::Building(char * buf, int cap)
{
    assert(buf && cap > HEAD_LEN);
    // check rule
    if(m_sender.size() > 0  && m_receiver.size() > 0 && m_reply.size() > 0 && m_content.size() > 0 
        && m_content.size() <= GetMaxContentLength()
        && cap > m_content.size() + HEAD_LEN
        )
    {
        int msg_len = snprintf(buf + 4, cap - 4, "%10s%10s%10s%14s%4zd%s", m_sender.c_str(), m_receiver.c_str()
            ,m_reply.c_str(), "20130303121234", m_content.size(), m_content.c_str());
        if(msg_len >= cap - 4)
        {
            LOG_ERROR("msg buffer is too short ");
            return ERR_BUFFER_TOO_SHORT;
        }
        msg_len += 4;
        for(int i = 3, tmp = msg_len; i >= 0; --i)
        {
            buf[i] =  (char)(tmp%10 + 0x30);
            tmp /= 10;
        }
        return msg_len;
    }

    LOG_ERROR("sender, receiver, reply, content must existing, and content <= MaxContentLength, and buf size > content_length + head_len");
    return -1;
}
int SimpleProtocol::Parse(char * buf, int cap, SimpleProtocol & prtcl)
{
    return 0;
}


void SimpleProtocol::SetSender(const std::string & sender)
{
    if(sender.size() > 0 && sender != m_sender)
    {
        m_sender = sender;
    }
}
void SimpleProtocol::SetReceiver(const std::string  & receiver)
{
    if(receiver.size() > 0 && receiver != m_receiver)
    {
        m_receiver = receiver;
    }
}
void SimpleProtocol::SetReply(const std::string & reply)
{
    if(reply.size() > 0 && reply != m_reply)
    {
        m_reply = reply;
    }
}
void SimpleProtocol::SetContent(const std::string & content)
{
    if(content.size() > 0 && content != m_content)
    {
        m_content = content;
    }
}

} /*  namespace protocol */
} /*  namespace imsvr */
