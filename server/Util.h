
#ifndef  UTIL_H
#define  UTIL_H

#include <string>

namespace imsvr{
namespace common{

class Util
{
public:
    static int toInt(const char * start, const char * end);
    static std::string trimEnd(std::string &str);
};

} /*  namespace server */
} /*  namespace imsvr */


#endif   /* UTIL_H */
