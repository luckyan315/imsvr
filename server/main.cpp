#include "Log.h"
#include "SimpleProtocol.h"
#include <cassert>
#include <cstring>

/*  
using namespace boost::asio;
void test_server()
{
    const int port = 5800;
    io_service ios;
    Server s(ios, port);
    s.Run();
    ios.run();
}*/

using namespace imsvr::protocol;
void test_protocol()
{
    SimpleProtocol sp;
    sp.SetSender("10000");
    sp.SetReceiver("20000");
    sp.SetReply("10000");
    sp.SetSendTime("20130303121234");
    sp.SetContent("Hello, man I am a good programmer !\r\n\r\n");
    
    char * buf = new char [SimpleProtocol::MAX_MSG_LEN];
    memset(buf, 0, sizeof(char)*SimpleProtocol::MAX_MSG_LEN);
    int ret = 0;
    if( (ret = sp.Building(buf, SimpleProtocol::MAX_MSG_LEN)) > 0)
    {
        assert(strlen(buf) == ret);
        LOG_DEBUG("len(%d) buf to send: (%s)", ret, buf);
    }
    delete buf; buf = NULL;
}
void test_parse(){
    SimpleProtocol sp;
    std::string  msg = "0058     10000     20000     10000201303031212340010Hello, man";
    int ret = SimpleProtocol::Parse(msg.c_str(), msg.size(), sp);
    if(ret == 0)
    {
        LOG_DEBUG("sender is:%s", sp.GetSender().c_str());    
        LOG_DEBUG("receiver is :%s", sp.GetReceiver().c_str());    
        LOG_DEBUG("reply to : %s", sp.GetReply().c_str());    
        LOG_DEBUG("content is :%s", sp.GetContent().c_str());    
        LOG_DEBUG("content len :%d", sp.GetContentLength());
    }
    else
    {
        LOG_ERROR("parse msg failed!");
    }
}
int main(int argc, char * argv[])
{
    test_protocol();
    test_parse();
    return 0;
}
