
#include "todoclient.h"
#include "request.h"
#include "todo_common.h"

AddOneResponse todoservice::AddOne(AddOneParams params)
{
    return ProcessAPI<AddOneParams,AddOneResponse>(params, this->_cli, this->_auth);
}

FindTodoResponse todoservice::FindTodos(FindTodosParams params)
{
   return ProcessAPI<FindTodosParams,FindTodoResponse>(params, this->_cli, this->_auth);
}

DestroyOneResponse todoservice::DestroyOne(DestroyOneParams params)
{
    return ProcessAPI<DestroyOneParams,DestroyOneResponse>(params, this->_cli, this->_auth);
}

void todoservice::SetDefaultAuth(AuthInfoWriter auth)
{
    this->_auth = auth;
}