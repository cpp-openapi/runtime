
#pragma once

#include <string>
#include <memory>
#include "openapi/runtime/client.h"

#include "add_one_params.h"
#include "add_one_response.h"

#include "find_todo_params.h"
#include "find_todo_response.h"

#include "destroy_one_params.h"
#include "destroy_one_response.h"
#include "openapi/runtime/auth.h"

// defines api tag methods
class todoservice
{
public:
    todoservice(std::shared_ptr<IClient> cli):_cli(cli) {};
    std::shared_ptr<IClient> _cli;
    AuthInfoWriter _auth = nullptr;
    void SetDefaultAuth(AuthInfoWriter auth);
    std::future<FindTodoResponse> FindTodos(FindTodosParams params);
    std::future<AddOneResponse> AddOne(AddOneParams params);
    std::future<DestroyOneResponse> DestroyOne(DestroyOneParams params);
};

// class todoclient
// {
// public:
//     todoclient(transport tr):_ts(tr){};
//     todoservice _ts;
//     //void addOne(std::string param);
// };