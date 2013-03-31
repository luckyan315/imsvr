
#ifndef  SIMPLE_PROTOCOL_H
#define  SIMPLE_PROTOCOL_H

#include "Protocol.h"

namespace imsvr{
namespace protocol{

class SimpleProtocol : public Protocol
{
public:
    static const int MAX_MSG_LEN    = 9999;
    SimpleProtocol (){}
    ~SimpleProtocol (){}

    virtual int Building(char * buf, int cap);
    virtual int Parse(const char * buf, int cap);

    const int GetHeadLength() const {return HEAD_LEN;}
    const int GetMaxMsgLength()const {return MAX_MSG_LEN;}

protected:
    static const int HEAD_LEN       = 52;
private:
};
} /*  namespace protocol */
} /*  namespace imsvr */


#endif   /* SIMPLE_PROTOCOL_H */
