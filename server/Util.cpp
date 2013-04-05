#include "Util.h"

#include <boost/lexical_cast.hpp>
#include <time.h>
#include "Log.h"

namespace imsvr{
namespace common{

int Util::toInt(const char * start, const char * end)
{
    int len = 0;
    try{
        len = boost::lexical_cast<int>(std::string(start, end));
    }
    catch(std::exception & e)
    {
        LOG_ERROR("int cast failed: %s", e.what());
        len = 0;
    }
    return len;
}
std::string Util::trimEnd(std::string &str)
{
    const std::string &delim =" " ;
    std::string r = str.erase(str.find_last_not_of(delim)+1);
    return r.erase(0,r.find_first_not_of(delim));
}
//for performance
int Util::GetDateTimeString(char * buf, int sz)
{
    assert(sz >= 15 && buf);
    time_t t;
    struct tm dt;

    time(&t);
    localtime_r(&t, &dt);
    return strftime(buf, 15, "%Y%m%d%H%M%S", &dt);
}

//Just to easy use
void Util::GetDateTimeString(std::string & date_time)
{
    char buf[15];
    int ret = GetDateTimeString(buf, 15);
    date_time.assign(buf, buf+14);
}
//Just to easy use
std::string Util::GetDateTimeString()
{
    std::string tmp;
    Util::GetDateTimeString(tmp);
    return tmp;
}

} /*  namespace server */
} /*  namespace imsvr */
