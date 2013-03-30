#include <cassert>
#include <cstring>

#include "Log.h"
#include "SimpleProtocol.h"
#include "SessionManager.h"
#include "Server.h"


using namespace imsvr::protocol;
void test_protocol()
{
    SimpleProtocol sp;
    sp.SetSender(std::string("10000"));
    sp.SetReceiver("20000");
    sp.SetReply("10000");
    sp.SetSendTime("20130303121234");
    sp.SetContent(std::string("Hello, man I am a good programmer !\r\n\r\n"));
    
    char * buf = new char [SimpleProtocol::MAX_MSG_LEN];
    memset(buf, 0, sizeof(char)*SimpleProtocol::MAX_MSG_LEN);
    int ret = 0;
    if( (ret = sp.Building(buf, SimpleProtocol::MAX_MSG_LEN)) > 0)
    {
        assert(strlen(buf) == ret);
        LOG_DEBUG("len(%d) buf to send: (%s)", ret, buf);
    }

    ret = sp.Parse(buf, ret);
    if(ret == 0)
        sp.Print();
    else
        LOG_ERROR("parse msg failed!");

    delete buf; buf = NULL;
}
void test_parse(){
    SimpleProtocol sp;
    std::string  msg = "0058     10000     20000     10000201303031212340010Hello, man";
    int ret = sp.Parse(msg.c_str(), msg.size());
    if(ret == 0)
        sp.Print();
    else
        LOG_ERROR("parse msg failed!");
}
void test_session_manager()
{
}

void test_server()
{
    const int port = 5800;
    boost::asio::io_service ios;
    imsvr::server::Server s(ios, port);
    s.Run();
    ios.run();
}
int main(int argc, char * argv[])
{
// test_protocol();
// test_parse();
//    test_session_manager();
    test_server();
    return 0;
}
