/**
 * A To Do list application
 * The product of a tutorial on goswagger.io
 *
 * The version of the OpenAPI document: 1.0.0
 *
 * NOTE: This class is auto generated by OpenAPI-Generator 5.2.1.
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */

/*
 * TodosApi.h
 *
 * 
 */

#ifndef ORG_OPENAPITOOLS_CLIENT_API_TodosApi_H_
#define ORG_OPENAPITOOLS_CLIENT_API_TodosApi_H_


#include "../ApiClient.h"

#include "Error.h"
#include "Item.h"


#include <boost/optional.hpp>

namespace org {
namespace openapitools {
namespace client {
namespace api {

using namespace org::openapitools::client::model;



class  TodosApi 
{
public:

    explicit TodosApi( std::shared_ptr<const ApiClient> apiClient );

    virtual ~TodosApi();

    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="body"> (optional)</param>
    pplx::task<std::shared_ptr<Item>> addOne(
        boost::optional<std::shared_ptr<Item>> body
    ) const;
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="id"></param>
    pplx::task<void> destroyOne(
        int64_t id
    ) const;
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="since"> (optional, default to 0L)</param>
    /// <param name="limit"> (optional, default to 0)</param>
    pplx::task<std::vector<std::shared_ptr<Item>>> findTodos(
        boost::optional<int64_t> since,
        boost::optional<int32_t> limit
    ) const;
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="id"></param>
    /// <param name="body"> (optional)</param>
    pplx::task<std::shared_ptr<Item>> updateOne(
        int64_t id,
        boost::optional<std::shared_ptr<Item>> body
    ) const;

protected:
    std::shared_ptr<const ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* ORG_OPENAPITOOLS_CLIENT_API_TodosApi_H_ */

