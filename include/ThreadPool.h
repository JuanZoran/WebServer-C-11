#ifndef _THREADPOOL_
#define _THREADPOOL_
#include "TaskQueue.h"
#include <pthread.h>

class ThreadPool
{
public:
    //单例模式
    static ThreadPool *getInstance();
    friend class GC;
    ThreadPool(const ThreadPool &) = delete;

    //获取当前的工作线程数量
    int getCurNum();
    //获取忙线程个数
    int getBusyNum();
    //添加任务
    void addTask(Task task);
    //销毁线程池
    ~ThreadPool();

    // TODO
    bool setStep(int step);

    // TODO
    bool setMaxSize(int maxSize);

    // TODO
    bool setMinSize(int minSize);

private:
    static ThreadPool *instance;
    //构造函数
    ThreadPool(int minSize = 2, int maxSize = 16, int step = 2);
    int step;
    int minSize;
    int maxSize;
    int busyNum;
    int exitNum;
    int curNum;
    bool shutdown;
    pthread_t manager_id;
    TaskQueue *Q;
    pthread_cond_t consumer;
    pthread_mutex_t mutexPool;
    static void *worker(void *arg);
    static void *manager(void *arg);
};

#endif
