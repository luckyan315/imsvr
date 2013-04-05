
#ifndef  ID_GENERATOR_H
#define  ID_GENERATOR_H


#include <string>

namespace imsvr{
namespace common{


class IDGenerator
{
public:

    static void Next(std::string & id);
protected:

private:
    static int _seq ;
};


} /*  namespace server */
} /*  namespace common */

#endif   /* IDGENERATOR_H */
