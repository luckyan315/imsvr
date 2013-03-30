#ifndef  PROTOCOL_H
#define  PROTOCOL_H

#include <string>

namespace imsvr{
namespace protocol{

enum ProtocolCode{
    OK = 0,
    ERR_BUFFER_TOO_SHORT = -1,
    ERR_INVALID_MSG_CONTENT = -2,
};

class Protocol
{
public:

    virtual int Building(char * buf, int cap) = 0;
    virtual int Parse(const char * buf, int cap) = 0;


    void SetSender(const std::string & sender);
    void SetReceiver(const std::string & receiver);
    void SetReply(const std::string & reply);
    void SetSendTime(const std::string & send_time);
    void SetContent(const std::string & content);

    const std::string & GetSender(){return m_sender;}
    const std::string & GetReceiver(){return m_receiver;}
    const std::string & GetReply(){return m_reply;}
    const std::string & GetContent(){return m_content;}
    const std::string & GetSendTime(){return m_send_time;}
    const int GetContentLength(){return m_content.size();}

    const int GetMsgLength() const {return m_content.size() + GetHeadLength();}
    virtual const int GetHeadLength() const  = 0 ;
    virtual const int GetMaxMsgLength() const  = 0;   

    const int GetMaxContentLength() const {return GetMaxMsgLength() - GetHeadLength();}
    

    void Print();
protected:

    std::string m_sender;
    std::string m_receiver;
    std::string m_reply;
    std::string m_content;
    std::string m_send_time;

private:
};
} /*  namespace protocol */
} /*  namespace imsvr */

#endif   /* PROTOCOL_H */
