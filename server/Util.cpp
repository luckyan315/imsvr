#include "Util.h"

#include <boost/lexical_cast.hpp>
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

} /*  namespace server */
} /*  namespace imsvr */
