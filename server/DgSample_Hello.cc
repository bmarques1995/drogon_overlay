#include "DgSample_Hello.hh"

using namespace drogon;

void DgSample::Hello::root(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value result;
    result["message"] = "Welcome!";

    callback(HttpResponse::newHttpJsonResponse(result));
}

void DgSample::Hello::hello(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value result;
    result["message"] = "Hello, World!";

    callback(HttpResponse::newHttpJsonResponse(result));
}
