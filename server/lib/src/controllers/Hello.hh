#pragma once

#include <drogon/HttpController.h>
#include "ServerExport.hh"
#include <memory>
#include <graphqlservice/GraphQLParse.h>
#include "schemas/DgctrlSchema.h"

using namespace drogon;

namespace DgSample
{   
    class SERVER_API Hello : public drogon::HttpController<Hello, false>
    {
    public:
        Hello();

        static void initPathRouting();
        void GraphQL(
            const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback
        );
    private:
		// Private members and methods can be added here
        void ProcessQuery(graphql::peg::ast* ast, const HttpRequestPtr& request);
		void ParseQuery(graphql::peg::ast* ast, std::string_view body);
		void ResolveQuery(graphql::peg::ast* ast, std::string* response);

		//std::shared_ptr<Resolvers> m_Resolvers;
		std::shared_ptr<graphql::Dgql::Operations> m_Operations;
    };
}
