#pragma once
#ifdef DEBUG
#include <iostream>
using std::cout, std::endl;
#endif

template <typename T>
class SingleTon
{
public:
    // 返回该对象实例
    static T& instance() noexcept
    {
        // 懒汉模式: 第一次创建的时候获得实例子
        // T SingleTon<T>::m_instance{};
        static T m_instance {};
#ifdef DEBUG
        cout << "create instance successfully!" << endl;
#endif
        return m_instance;
    }

protected:
    SingleTon<T>() = default;
};
