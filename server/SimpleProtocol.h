
#ifndef  SIMPLE_PROTOCOL_H
#define  SIMPLE_PROTOCOL_H

#include <string>
namespace imsvr{
namespace protocol{

enum ProtocolCode{
    OK = 0,
    ERR_BUFFER_TOO_SHORT = -1,
    ERR_INVALID_MSG_CONTENT = -2,
};

class SimpleProtocol
{
public:
    static const int MAX_MSG_LEN    = 9999;
    SimpleProtocol (){}
    ~SimpleProtocol (){}

    int Building(char * buf, int cap);
    static int Parse(const char * buf, int cap, SimpleProtocol & prtcl);


    void SetSender(const char * start, const char * end);
    void SetReceiver(const char * start, const char * end);
    void SetReply(const char * start, const char * end);
    void SetSendTime(const char * start, const char * end);
    void SetContent(const char * start, const char * end);

    void SetSender(std::string sender);
    void SetReceiver(std::string receiver);
    void SetReply(std::string reply);
    void SetSendTime(std::string send_time);
    void SetContent(std::string content);

    const std::string & GetSender(){return m_sender;}
    const std::string & GetReceiver(){return m_receiver;}
    const std::string & GetReply(){return m_reply;}
    const std::string & GetContent(){return m_content;}
    const std::string & GetSendTime(){return m_send_time;}

    int GetContentLength(){return m_content.size();}
    int GetMsgLength(){return m_content.size() + GetHeadLength();}
    const int GetHeadLength() const  {return HEAD_LEN;}

    int GetMaxContentLength(){return MAX_MSG_LEN - GetHeadLength();}
    int GetMaxMsgLength(){return MAX_MSG_LEN;}
    
protected:
    static const int HEAD_LEN       = 52;

private:
    std::string m_sender;
    std::string m_receiver;
    std::string m_reply;
    std::string m_content;
    std::string m_send_time;
};
} /*  namespace protocol */
} /*  namespace imsvr */


#endif   /* SIMPLE_PROTOCOL_H */
