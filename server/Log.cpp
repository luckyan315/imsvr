#include "Log.h"

#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
namespace imsvr{
namespace common{

void Log::Out(const int moduleIndex, const int lvl, const char * fileName, const char * funcName, int line, const char * fmt, ...)
{
    static const char * moduleName[]={
        "IMSVR",
    };
    static const char * levelName[] = {
        "FATAL",
        "ERROR",
        "WARNING",
        "Debug",
        "INFO"
    };
    time_t now;                                                      
    char dbgtime[26] ;                                                  
    time(&now);                                                         
    ctime_r(&now, dbgtime);                                             
    dbgtime[24] = '\0';       
    // with time
    // printf("[%s] [%s][%s][%s:%d]", moduleName[moduleIndex], levelName[lvl], dbgtime, fileName, line);
    // no time - no funcName
    // printf("[%s] [%s][%s:%d]", moduleName[moduleIndex], levelName[lvl], fileName, line);
    // no time with funcName 
    printf("[%s] [%s][%s:%s:%d]", moduleName[moduleIndex], levelName[lvl], fileName, funcName, line);
    va_list pArg;
    va_start(pArg, fmt);
    vprintf(fmt, pArg);
    va_end(pArg);
    printf("\n");
}
}/*   Namespace common */
}/*   Namespace imsvr */
