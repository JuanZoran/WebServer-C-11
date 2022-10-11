#include "ThreadPool.h"
#include <unistd.h>

ThreadPool *ThreadPool::getInstance()
{
    if (!instance)
    {
        instance = new ThreadPool();
    }
    return instance;
}

//构造函数
ThreadPool::ThreadPool(int minSize, int maxSize, int step)
    : minSize(minSize), maxSize(maxSize), step(step), busyNum(0), exitNum(0), curNum(minSize), shutdown(false), Q(new TaskQueue())
{
    pthread_mutex_init(&mutexPool, NULL);
    pthread_cond_init(&consumer, NULL);
    for (int i = 0; i < minSize; i++)
    {
        pthread_create(&manager_id, NULL, worker, this);
        pthread_detach(manager_id);
    }
    pthread_create(&manager_id, NULL, manager, this); // 管理者线程的id
}

//销毁线程池
ThreadPool::~ThreadPool()
{
    this->shutdown = true;
    pthread_join(this->manager_id, NULL); // 错误:join的线程必须要有返回值
    int threadNum = curNum - busyNum;
    for (int i = 0; i < threadNum; i++)
    {
        pthread_cond_signal(&consumer);
    }
    pthread_cond_destroy(&this->consumer); // 错误: 释放时有线程在等待该信号量
    pthread_mutex_destroy(&this->mutexPool);

    // delete 内部会判断空指针
    delete Q;
}

void *ThreadPool::worker(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;
    while (true)
    {
        //加锁是为了保证操作的原子性
        pthread_mutex_lock(&pool->mutexPool);
        while (pool->Q->empty() && !pool->exitNum && !pool->shutdown)
        {
            pthread_cond_wait(&pool->consumer, &pool->mutexPool);
        }
        if (pool->shutdown || pool->exitNum > 0)
        {
            if (pool->exitNum > 0)
            {
                pool->exitNum--;
            }
            pool->curNum--;
            pthread_mutex_unlock(&pool->mutexPool);
            pthread_exit(NULL);
        }
        Task task;
        task = pool->Q->popTask();
        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexPool);

        task.process();

        pthread_mutex_lock(&pool->mutexPool);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexPool);
    }
}

void *ThreadPool::manager(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;
    while (!pool->shutdown)
    {
        pthread_mutex_lock(&pool->mutexPool);
        if (pool->busyNum * 2 + pool->step < pool->curNum && pool->curNum - pool->step >= pool->minSize)
        {
            pool->exitNum += pool->step;
            for (int i = 0; i < pool->step; i++)
            {
                pthread_cond_signal(&pool->consumer);
            }
        }
        else if (pool->busyNum + pool->step > pool->curNum && pool->curNum + pool->step <= pool->maxSize)
        {
            pthread_t tid;
            for (int i = 0; i < pool->step; i++)
            {
                pthread_create(&tid, NULL, worker, arg);
                pthread_detach(tid);
            }
            pool->curNum += pool->step;
        }
        pthread_mutex_unlock(&pool->mutexPool);
        usleep(10000);
    }
    pthread_exit(NULL);
}

//获取当前的工作线程数量
int ThreadPool::getCurNum()
{
    return curNum;
}
//获取忙线程个数
int ThreadPool::getBusyNum()
{
    return busyNum;
}
//添加任务
void ThreadPool::addTask(Task task)
{
    if (shutdown)
    {
        return;
    }
    Q->addTask(task);
    pthread_cond_signal(&consumer);
}

//用于回收单例模式的ThreadPool
class GC
{
public:
    ~GC()
    {
        // delete内部会检查空指针
        delete ThreadPool::instance;
    }
};

static GC gc;