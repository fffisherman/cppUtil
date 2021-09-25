#pragma once
// 单例模板，适用于无参数的构造函数的对象
template <class T>
class Singleton {
public:
    static T* Instance() {
        static T* t;
        return &t;
    }

    virtual ~Singleton() = default;

protected:
    Singleton() = default;

private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};