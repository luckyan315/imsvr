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
    sp.SetSender(std::string("10000"));
    sp.SetReceiver(std::string("20000"));
    sp.SetReply(std::string("10000"));
    sp.SetContent(std::string("Hello, man"));
    
    char * buf = new char [SimpleProtocol::MAX_MSG_LEN];
    memset(buf, 0, sizeof(char)*SimpleProtocol::MAX_MSG_LEN);
    int ret = 0;
    if( (ret = sp.Building(buf, SimpleProtocol::MAX_MSG_LEN)) > 0)
    {
        assert(strlen(buf) == ret);
        LOG_DEBUG("len(%d) buf(%s)", ret, buf);
    }
    delete buf; buf = NULL;
}
/* 
void test_parse(){
    SimpleProtocol sp;
    std::string  msg = "0062     10000     20000     1000020130303121234  10Hello, man"
    ret = SimpleProtocol::Parse(msg.c_str(), msg.size(), sp);
    if(ret == 0)
    {
        LOG_DEBUG("sender is:%s", p->GetSender().c_str());    
        LOG_DEBUG("receiver is :%s", p->GetReceiver().c_str());    
        LOG_DEBUG("reply to : %s", p->GetReply().c_str());    
        LOG_DEBUG("content is :%s", p->GetContent().c_str());    
        LOG_DEBUG("content len :%d", p->GetContentLength());
        LOG_DEBUG("msg len :%d", p->GetMSg());
    }
    else
    {
        LOG_ERROR("parse msg failed!");
    }
}
*/
int main(int argc, char * argv[])
{
    // test_server();
    test_protocol();
    return 0;
}
