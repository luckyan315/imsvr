#include <iostream>
#include <boost/asio.hpp>

#include "Server.h"

using namespace boost::asio;

void test_server()
{
    const int port = 5800;
    io_service ios;
    Server s(ios, port);
    s.Run();
    ios.run();
}

int main(int argc, char * argv[])
{
    //test_client();
    test_server();
    return 0;
}
