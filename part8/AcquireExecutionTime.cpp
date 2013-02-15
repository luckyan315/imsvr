#include "stdafx.h"
#include "AcquireExecutionTime.h"

AcquireExecutionTime::AcquireExecutionTime(void)
{
    this->Reset();
}

AcquireExecutionTime::~AcquireExecutionTime(void)
{
}

BOOL AcquireExecutionTime::Reset()
{
    m_bSupport = QueryPerformanceFrequency(&m_lFrequency) == 0 ? FALSE : TRUE;
    if (m_bSupport)
    {
        return QueryPerformanceCounter(&m_lStartTime);
    }
    return FALSE;
}


double AcquireExecutionTime::GetTimeSpanSec(bool isReset)
{
    if (m_bSupport)
    {
        LARGE_INTEGER	endTime;
        QueryPerformanceCounter(&endTime);
        double ret = (double)(endTime.QuadPart - m_lStartTime.QuadPart)/(double)m_lFrequency.QuadPart;

        if(isReset)
        {
            this->Reset();
        }
        return ret;
    }
    return -1;
}