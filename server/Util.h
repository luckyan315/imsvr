
#ifndef  UTIL_H
#define  UTIL_H

#include <string>

namespace imsvr{
namespace common{

class Util
{
public:
    static int toInt(const char * start, const char * end);
    static std::string trimEnd(const std::string &str);

    static std::string GetDateTimeString();
    static void GetDateTimeString(std::string & date_time);
    static int GetDateTimeString(char * buf, const int sz);
};

} /*  namespace server */
} /*  namespace imsvr */


#endif   /* UTIL_H */
