#include "gtest/gtest.h"
#include "executor.h"
#include <thread>
#include <future>
#include <chrono>


TEST(Executor_test, execute) 
{    
    Executor::GetInstance().Submit([](){});

    int i = 1;
    Executor::GetInstance().Submit([&i](){ i++; });

    ASSERT_EQ(2,i);
}


TEST(Executor_Async, execute) 
{    
    Executor e;

    // execute stuff async in a thread

    std::promise<int> p;
    std::future<int> ft = p.get_future();
    auto ff = [&p](){
        // std::this_thread::sleep_for(std::chrono::seconds(2));
        p.set_value_at_thread_exit(2);
    };

    e.SetExecutor([](std::function<void(void)> f)
    {
        std::thread(f).detach();
    });
    e.Submit(ff);

    ASSERT_EQ(2,ft.get());
}