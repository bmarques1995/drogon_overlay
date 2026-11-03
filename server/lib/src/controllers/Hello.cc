#include "Hello.hh"
#include "DgctrlSchema.h"

using namespace drogon;

void DgSample::Hello::GraphQL(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value result;
    result["message"] = "Welcome!";

    callback(HttpResponse::newHttpJsonResponse(result));
}
