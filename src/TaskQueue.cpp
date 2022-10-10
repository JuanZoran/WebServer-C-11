#include "TaskQueue.h"

// 默认初始化
TaskQueue::TaskQueue(){
    pthread_mutex_init(&mutex, NULL);
}

//取出任务
Task TaskQueue::popTask(){
    pthread_mutex_lock(&mutex);
    Task ret = this->Q.front();
    this->Q.pop();
    pthread_mutex_unlock(&mutex);
    return ret;
}



void TaskQueue::addTask(Task task){
    pthread_mutex_lock(&mutex);
    this->Q.push(task);
    pthread_mutex_unlock(&mutex);
}


bool TaskQueue::empty(){
    return Q.empty();
}


TaskQueue::~TaskQueue(){
    pthread_mutex_destroy(&mutex);
}
