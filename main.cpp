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

        findTodosParams p;
        findTodoResponse r = ts.findTodos(p);
        std::cout << r.code << " " << r.data << std::endl;
        std::cout << "item length: " << r.payload.size() << std::endl; 
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << boost::stacktrace::stacktrace();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}