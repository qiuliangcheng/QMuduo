#include "util.h"
#include "qlc_log.h"
#include <execinfo.h>
#include <sys/time.h>
namespace qlc{
namespace CurrentThread{
    __thread int t_cachedTid = 0;   

    void cacheTid()
    {
        if (t_cachedTid == 0)
        {
            // 通过linux系统调用，获取当前线程的tid值
            t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }
}
    qlc::Logger::ptr g_logger=QLC_LOG_NAME("system");
    pid_t GetThreadId(){
        return syscall(SYS_gettid);
    }

    uint32_t GetFiberId(){
        return 0;
    }

    void Backtrace(std::vector<std::string> &bt, int size, int skip)
    {
        void ** array=(void **)malloc(sizeof(void*)*size);//第一个指针保存栈的地址 第二个指针保存栈的信息 所以需要二级指针
        size_t len=::backtrace(array,size);
        char** stings=backtrace_symbols(array,len);
        if(stings==NULL){
            QLC_LOG_ERROR(g_logger)<<"获取函数栈信息错误";
            return;

        }
        for(size_t i=skip;i<len;i++){
            bt.push_back(stings[i]);
        }
        free(stings);
        free(array);

    }
    std::string BacktraceToString(int size, int skip, const std::string &prefix)
    {
        std::vector<std::string> vec;
        Backtrace(vec,size,skip);
        std::stringstream ss;
        for(size_t i=0;i<vec.size();i++){
            ss<<prefix<<vec[i]<<std::endl;
        }
        return ss.str();
    }
    uint64_t GetCurrentMS()
    {
        struct timeval tv;
        gettimeofday(&tv,NULL);
        return tv.tv_sec*1000ul+tv.tv_usec/1000;
    }
    uint64_t GetCurrentUS()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec * 1000 * 1000ul  + tv.tv_usec;
    }
}
