#include "IDGenerator.h"


#include "Util.h"

namespace imsvr{
namespace common{

int IDGenerator::_seq  = 1;

void IDGenerator::Next(std::string & id)
{
    char buf[25];

    int sz = Util::GetDateTimeString(buf, sizeof(buf));
    snprintf(buf + 14, 11, "%010d", int(_seq%10000000000));
    ++_seq;
    id.assign(buf, buf + 24);
}


} /*  namespace server */
} /*  namespace common */
