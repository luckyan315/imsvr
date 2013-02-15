/*
 * File     :   AcquireExecutionTime.h
 * Descript :   计算时间间隔，例如一段代码的执行时间
 */
#ifndef ACQUIRE_EXECUTION_TIME_H
#define ACQUIRE_EXECUTION_TIME_H


#include <windows.h>

/*
 * Class    :   AcquireExecutionTime
 * Function :   用于计算时间间隔； 构造时开始计时，调用GetTimeSpan系列函数则结束计时。
 */
class AcquireExecutionTime
{

public:
    AcquireExecutionTime(void);
    ~AcquireExecutionTime(void);

public:
    /*
     *  param[in]   : isReset   如果设置为true，再计算时间间隔后，将计时器重置。
     *                         如果设置为false，则不会重置计时器,可以获取暂时的时间间隔
     *  return      : 返回 对象实例化到调用该函数时的时间间隔，单位为秒
     *  Descript    : 获取对象实例化后到调用该函数时的时间间隔，单位为秒
     * */
    double GetTimeSpanSec(bool isReset = false);
    /*
     *  param[in]   : isReset   如果设置为true，再计算时间间隔后，将计时器重置。
     *                         如果设置为false，则不会重置计时器,可以获取暂时的时间间隔
     *  return      : 返回 对象实例化到调用该函数时的时间间隔，单位为毫秒
     *  Descript    : 获取对象实例化后到调用该函数时的时间间隔，单位为毫秒
     * */
    double GetTimeSpanMS(bool isReset = false){ return GetTimeSpanSec(isReset) * 1000; }

    /*
     *  return      : 返回bool变量，标识操作系统是否支持该类所调用的接口。
     *  Descript    : 查询操作系统是否支持该类的接口
     */
    BOOL IsSupport() const { return m_bSupport; }

    /*
     *  return      : 返回操作是否成功
     *  Descript    : 重置对象内部的计时器,重新开始计时
     */
    BOOL Reset();
protected:


private:
    BOOL			m_bSupport;
    LARGE_INTEGER	m_lFrequency;
    LARGE_INTEGER	m_lStartTime;

};
#endif
