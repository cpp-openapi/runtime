
#pragma once

#include <string>
#include <memory>
#include "client.h"
#include "find_todo.h"
#include "add_one.h"
#include "destroy_one.h"

// defines api tag methods
class todoservice
{
public:
    todoservice(std::shared_ptr<IClient> cli):_cli(cli) {};
    std::shared_ptr<IClient> _cli;
    FindTodoResponse FindTodos(FindTodosParams params);
    AddOneResponse AddOne(AddOneParams params);
    DestroyOneResponse DestroyOne(DestroyOneParams params);
};

// class todoclient
// {
// public:
//     todoclient(transport tr):_ts(tr){};
//     todoservice _ts;
//     //void addOne(std::string param);
// };