#pragma once

#include <functional>

class Executor
{
public:
    Executor();
    void Submit(std::function<void(void)> f);

    // executor function takes in a no arg function and execute it
    void SetExecutor(std::function<void(std::function<void(void)>)> exe);

    // global instance for runtime
    static Executor& GetInstance();
private:
    std::function<void(std::function<void(void)>)> _exe;

    static Executor gm_instance;
};