#include "SessionManager.h" 
#include <utility>

#include "Log.h"
#include "Util.h"
#include "SessionStatus.h"

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
void SessionManager::AddNewSession(Session::PtrType ses)
{
    assert(ses != NULL);
    LOG_DEBUG("add session into container");
    m_seses_new_connected[ses->GetID()] = ses;
}
void SessionManager::RemoveSession(Session::PtrType ses)
{
    if(ses->Status() == NewConnected)
    {
        LOG_DEBUG("Remove the session from new_connected container");
        Container::iterator it = m_seses_new_connected.find(ses->GetID());
        if(it != m_seses_new_connected.end())
        {
            m_seses_new_connected.erase(it);
        }
    }
    else 
    {
        LOG_DEBUG("Remove the session from actived container");
        ActiveContainer::iterator it = m_seses_actived.find(ses->GetID());
        if(it != m_seses_actived.end())
        {
            m_seses_actived.erase(it);
        }
    }
}
void SessionManager::MoveSession(Session::PtrType ses, const std::string &new_id)
{
    if(ses->Status() == NewConnected)
    {
        LOG_DEBUG("Move New connected session into actived Container");
        Container::iterator it = m_seses_new_connected.find(imsvr::common::Util::trimEnd(ses->GetID()));
        if(it != m_seses_new_connected.end())
        {
            m_seses_new_connected.erase(it);
            Session::PtrType pses = it->second;
            std::string id = imsvr::common::Util::trimEnd(new_id);
            pses->SetID(id);
            m_seses_actived[id] = pses;
        }
    }
}
void SessionManager::Clear()
{
    m_seses_new_connected.clear();
}

void SessionManager::Print()
{
    LOG_DEBUG("session count %d", m_seses_new_connected.size());
}

Session::PtrType SessionManager::FindSession(const std::string &id)
{
    ActiveContainer::iterator it = m_seses_actived.find(id);
    if(it != m_seses_actived.end())
    {
        return it->second;
    }
    return Session::PtrType();
}
} /*  namespace server */
} /*  namespace imsvr */
