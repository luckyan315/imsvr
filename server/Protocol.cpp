#include "Protocol.h"

#include "Log.h"

namespace imsvr{
namespace protocol{

void Protocol::SetSender(const std::string & sender)
{
    if(sender != m_sender)
        m_sender = sender;
}
void Protocol::SetReceiver(const std::string & receiver)
{
    if(receiver != m_receiver)
        m_receiver = receiver;
}
void Protocol::SetReply(const std::string & reply)
{
    if(reply != m_reply)
        m_reply = reply;
}
void Protocol::SetSendTime(const std::string  & send_time)
{
    if(send_time != m_send_time)
        m_send_time = send_time;
}
void Protocol::SetContent(const std::string & content)
{
    if(content != m_content)
        m_content = content;
}
void Protocol::Print()
{
    LOG_DEBUG("\nMsg is:\n"
                "\tsender is:%s\n"
                "\treceiver is :%s\n"
                "\treply to : %s\n"
                "\tcontent is :%s\n"
                "\tcontent len :%d"
            , m_sender.c_str(), m_receiver.c_str(), m_reply.c_str(), m_content.c_str(), m_content.size());
}


} /*  namespace protocol */
} /*  namespace imsvr */
