#include "todoclient.h"
#include "typefactory.h"
#include <iostream>
#include <boost/stacktrace.hpp>

int main()
{
    try
    {
        ClientConfig cfg = {
            "localhost",
            "12345",
            "/",
            };
        
        std::shared_ptr<IClient> cli =  TypeFactory::NewClient(cfg);

        todoservice ts(cli);
        {
            FindTodosParams p;
            // p.limit = 3;
            FindTodoResponse r = ts.FindTodos(p);
            // std::cout << r.code << " " << r.data << std::endl;
            // debug
            //std::cout << r << std::endl;
            // std::cout << "item length: " << r.payload.size() << std::endl; 
            std::cout << "Find Todo: " << r << std::endl;
        }

        {
            AddOneParams p;
            p.Body = Item{0, "hello"};
            AddOneResponse r = ts.AddOne(p);
            std::cout << "Add one: " << r << std::endl;
        }

        {
            DestroyOneParams p;
            p.id = 0;
            DestroyOneResponse r = ts.DestroyOne(p);
            std::cout << "destroy one: " << r << std::endl;
        }
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << boost::stacktrace::stacktrace();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}