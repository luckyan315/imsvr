#ifndef LOG_H_
#define  LOG_H_

#define MODULE     0
#define LOG_FATAL(fmt,...)      imsvr::common::Log::Out(MODULE, 0, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt,...)      imsvr::common::Log::Out(MODULE, 1, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt,...)    imsvr::common::Log::Out(MODULE, 2, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt,...)      imsvr::common::Log::Out(MODULE, 3, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt,...)       imsvr::common::Log::Out(MODULE, 4, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
namespace imsvr{
namespace common{
class Log
{
public:
    static void Out(const int moduleIndex, const int lvl, const char * fileName, const char * funcName, int line, const char * fmt, ...);
}; 

}/*   Namespace common */
}/*   Namespace lfs */
#endif /*  LOG_H */
