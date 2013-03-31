#ifndef  SESSIONMANAGER_H
#define  SESSIONMANAGER_H

#include <map>
#include "Session.h"

namespace imsvr{
namespace server{


class SessionManager
{
public:
    ~SessionManager (){m_seses.clear();}

static SessionManager * Instance();

    void AddSession(Session::PtrType ses);
    void RemoveSession(const Session::IDType & id);
    void RemoveSession(Session::PtrType ses);
    void Clear();

    const int size() {return m_seses.size();}

    void Print();

    Session::PtrType FindSession(const Session::IDType & id);

protected:
    SessionManager (){}
    

private:
    static SessionManager * _inst;

    typedef std::map<Session::IDType, Session::PtrType> Container;
    Container m_seses; 
};


} /*  namespace server */
} /*  namespace imsvr */

#endif   /* SESSIONMANAGER_H */
