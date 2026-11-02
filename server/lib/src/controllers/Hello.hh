#pragma once

#include <drogon/HttpController.h>
#include "ServerExport.hh"

using namespace drogon;

namespace DgSample
{
    class SERVER_API Hello : public drogon::HttpController<Hello, false>
    {
    public:
        METHOD_LIST_BEGIN

        ADD_METHOD_TO(Hello::root, "/root", Get);
        ADD_METHOD_TO(Hello::hello, "/hello", Get);

        METHOD_LIST_END

        void root(
            const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback
        );

        void hello(
            const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback
        );
    };
}
