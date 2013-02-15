/*
 * File     :   AcquireExecutionTime.cpp
 * Descript :   计算时间间隔，例如一段代码的执行时间
 */
#include "stdafx.h"
#include "AcquireExecutionTime.h"

AcquireExecutionTime::AcquireExecutionTime(void)
{
    this->Reset();
}

AcquireExecutionTime::~AcquireExecutionTime(void)
{
}

/*
 *  return      : 返回操作是否成功
 *  Descript    : 重置对象内部的计时器,重新开始计时
 */
BOOL AcquireExecutionTime::Reset()
{
    m_bSupport = QueryPerformanceFrequency(&m_lFrequency) == 0 ? FALSE : TRUE;
    if (m_bSupport)
    {
        return QueryPerformanceCounter(&m_lStartTime);
    }
    return FALSE;
}

/*
 *  param[in]   : isReset   如果设置为true，再计算时间间隔后，将计时器重置。
 *                         如果设置为false，则不会重置计时器,可以获取暂时的时间间隔
 *  return      : 返回 对象实例化到调用该函数时的时间间隔，单位为秒
 *  Descript    : 获取对象实例化后到调用该函数时的时间间隔，单位为秒
 * */
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
