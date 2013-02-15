#ifndef ACQUIRE_EXECUTION_TIME_H

#define ACQUIRE_EXECUTION_TIME_H


#include <windows.h>

class AcquireExecutionTime
{

public:
    AcquireExecutionTime(void);
    ~AcquireExecutionTime(void);

public:

    double GetTimeSpanSec(bool isReset = false);
    double GetTimeSpanMS(bool isReset = false){ return GetTimeSpanSec(isReset) * 1000; }

    BOOL IsSupport() const { return m_bSupport; }

    BOOL Reset();
protected:


private:
    BOOL			m_bSupport;
    LARGE_INTEGER	m_lFrequency;
    LARGE_INTEGER	m_lStartTime;

};
#endif
