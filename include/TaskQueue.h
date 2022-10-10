#ifndef _TASKQUEUE_
#define _TASKQUEUE_
#include "Task.h"
#include <pthread.h>
#include <queue>

class TaskQueue
{
public:
    // 默认初始化
    TaskQueue();

    //取出任务
    Task popTask();

    //判断当前队列是否为空
    bool empty();

    //添加任务
    void addTask(Task task);

    ~TaskQueue();

private:
    pthread_mutex_t mutex;
    std::queue<Task> Q;
};

#endif
