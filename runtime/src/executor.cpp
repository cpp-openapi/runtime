#include "executor.h"

Executor Executor::gm_instance = Executor();

Executor& Executor::GetInstance()
{
    return Executor::gm_instance;
}

Executor::Executor()
{
    // default executor executes function synchronosly
    this->_exe = [](std::function<void(void)> f)
    {
        f();
    };
}

void Executor::Submit(std::function<void(void)> f)
{
    this->_exe(f);    
}

void Executor::SetExecutor(std::function<void(std::function<void(void)>)> exe)
{
    this->_exe = exe;
}