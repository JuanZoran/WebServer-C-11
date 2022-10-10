#include "Task.h"


Task::Task(function func, void* arg):m_func(func), m_arg(arg){}


void Task::process(){
    this->m_func(m_arg);
}



