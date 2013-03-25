
#ifndef  SIMPLE_PROTOCOL_H
#define  SIMPLE_PROTOCOL_H

#include <string>
namespace imsvr{
namespace protocol{

enum ProtocolCode{
    OK = 0,
    ERR_BUFFER_TOO_SHORT = -1,
};

class SimpleProtocol
{
public:
    static const int MAX_MSG_LEN    = 9999;
    SimpleProtocol (){}
    ~SimpleProtocol (){}

    int Building(char * buf, int cap);
    static int Parse(char * buf, int cap, SimpleProtocol & prtcl);


    void SetSender(const std::string & sender);  
    void SetReceiver(const std::string  & receiver);
    void SetReply(const std::string & reply);
    void SetContent(const std::string & content);

    const std::string & GetSender(){return m_sender;}
    const std::string & GetReceiver(){return m_receiver;}
    const std::string & GetReply(){return m_reply;}
    const std::string & GetContent(){return m_content;}

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
};
} /*  namespace protocol */
} /*  namespace imsvr */


#endif   /* SIMPLE_PROTOCOL_H */
