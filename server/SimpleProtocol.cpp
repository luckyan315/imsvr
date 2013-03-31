#include "SimpleProtocol.h"

#include <boost/lexical_cast.hpp>
#include <cassert>

#include "Log.h"


namespace imsvr{
namespace protocol{

int SimpleProtocol::Building(char * buf, int cap)
{
    assert(buf && cap > HEAD_LEN);
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
int SimpleProtocol::Parse(const char * buf, int sz)
{
    assert(buf && sz >= 0 && sz <= MAX_MSG_LEN  + 4);
    if(sz <  4)
        return ERR_BUFFER_TOO_SHORT;

    int len = boost::lexical_cast<int>(std::string(buf, buf + 4));
    if(len < 48 )
        return  ERR_BUFFER_TOO_SHORT;
    
    SetSender(std::string(buf + 4, buf + 14));
    SetReceiver(std::string(buf + 14,  buf + 24));
    SetReply(std::string(buf + 24, buf + 34));
    SetSendTime(std::string(buf + 34, buf + 48));

    len = boost::lexical_cast<int>(std::string(buf + 48, buf + 52));
    if(len != sz - 48)
        return ERR_INVALID_MSG_CONTENT;

    SetContent(std::string(buf + 52 , buf + 52 + len));
    return 0;
}

} /*  namespace protocol */
} /*  namespace imsvr */
