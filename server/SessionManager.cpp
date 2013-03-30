#include "SessionManager.h"

#include <utility>
#include "Log.h"

namespace imsvr{
namespace server{

SessionManager * SessionManager::_inst = NULL;

SessionManager * SessionManager::Instance()
{
    if(SessionManager::_inst == NULL)
    {
        SessionManager::_inst = new SessionManager(); 
    }
    return SessionManager::_inst;
}
void SessionManager::AddSession(Session::PtrType ses)
{
    assert(ses != NULL);
    m_seses[ses->GetID()] = ses;
}
void SessionManager::RemoveSession(const Session::IDType  & id)
{
    Container::iterator it = m_seses.find(id);
    if(it != m_seses.end())
    {
        m_seses.erase(it);
    }
}
void SessionManager::RemoveSession(Session::PtrType ses)
{
    assert(ses != NULL);
    RemoveSession(ses->GetID());
}
void SessionManager::Clear()
{
    m_seses.clear();
}

void SessionManager::Print()
{
    LOG_DEBUG("session count %d", m_seses.size());
}

} /*  namespace server */
} /*  namespace imsvr */
