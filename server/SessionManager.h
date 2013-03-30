#ifndef  SESSIONMANAGER_H
#define  SESSIONMANAGER_H

#include <boost/shared_ptr.hpp>
#include <map>

namespace imsvr{
namespace server{


class Session
{
public:
    typedef boost::shared_ptr<Session> PtrType;
    typedef std::string IDType;

    Session(IDType id):m_id(id){}
    ~Session(){}
    const IDType GetID(){ return m_id;}
    void SetID(IDType & id) {if(m_id != id) m_id = id;}
private:
    IDType m_id;
};

class SessionManager
{
public:
    ~SessionManager (){m_seses.clear();}

static SessionManager * Instance();

    void AddSession(Session::PtrType ses);
    void RemoveSession(const Session::IDType & id);
    void RemoveSession(Session::PtrType ses);
    void Clear();

    void Print();

    Session::PtrType FindSession(Session::PtrType ses);//TODO:

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
