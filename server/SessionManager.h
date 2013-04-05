#ifndef  SESSIONMANAGER_H
#define  SESSIONMANAGER_H

#include <map>
#include "Session.h"

namespace imsvr{
namespace server{


class SessionManager
{
public:
    ~SessionManager (){m_seses_new_connected.clear();}

static SessionManager * Instance();

    void AddNewSession(Session::PtrType ses);
    void RemoveSession(Session::PtrType ses);
    void MoveSession(Session::PtrType ses, const std::string &new_id);

    void Clear();

    const int size() {return m_seses_new_connected.size() + m_seses_actived.size();}

    void Print();

    Session::PtrType FindSession(const std::string & id);

protected:
    SessionManager (){}
    

private:
    static SessionManager * _inst;

    typedef std::map<Session::IDType, Session::PtrType> Container;
    Container m_seses_new_connected; 

    typedef std::map<Session::IDType, Session::PtrType> ActiveContainer;
    ActiveContainer m_seses_actived;
};


} /*  namespace server */
} /*  namespace imsvr */

#endif   /* SESSIONMANAGER_H */
