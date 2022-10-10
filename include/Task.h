#ifndef TASK
#define TASK


class Task{
public:
using function = void(*)(void*arg);
    //构造函数
    Task(function func = nullptr, void* arg = nullptr);

    //执行任务
    void process();


private:
    function m_func; // 函数指针
    void* m_arg;     // 参数
};

#endif
