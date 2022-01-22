#include "todoclient.h"
#include "typefactory.h"
#include <iostream>
// #include <boost/stacktrace.hpp>
#include "openapi/runtime/auth.h"
#include "openapi/runtime/executor.h"

int main()
{
    // Set the async launcher for runtime
    Executor::GetInstance().SetExecutor([](std::function<void(void)> f)
    {
        std::thread(f).detach();
    });

    try
    {
        ClientConfig cfg = {
            "localhost",
            "12345",
            "/",
            };
        
        std::shared_ptr<IClient> cli =  TypeFactory::NewClient(cfg);

        todoservice ts(cli);
        ts.SetDefaultAuth(APIAuth("x-todolist-token", "example token"));
        {
            FindTodosParams p;
            // p.limit = 3;
            std::future<FindTodoResponse> r = ts.FindTodos(p);
            std::cout << "Find Todo: " << r.get() << std::endl;
        }

        {
            AddOneParams p;
            p.Body = Item{0, openapi::StringT("hello")};
            std::future<AddOneResponse> r = ts.AddOne(p);
            std::cout << "Add one: " << r.get() << std::endl;
        }

        {
            DestroyOneParams p;
            p.id = 0;
            std::future<DestroyOneResponse> r = ts.DestroyOne(p);
            std::cout << "destroy one: " << r.get() << std::endl;
        }
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        // std::cout << boost::stacktrace::stacktrace();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}