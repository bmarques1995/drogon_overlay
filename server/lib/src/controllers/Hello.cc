#include "Hello.hh"
#include "Resolvers.hh"
#include "schemas/DgctrlSchema.h"
#include "HttpError.hh"

#include "graphqlservice/GraphQLParse.h"
#include "graphqlservice/JSONResponse.h"

using namespace drogon;

DgSample::Hello::Hello()
{
    auto queries = std::make_shared<DgSample::Queries>();
    auto mutations = std::make_shared<DgSample::Mutations>();
    m_Operations =
        std::make_shared<graphql::Dgql::Operations>(
            queries,
            mutations
        );
}

void DgSample::Hello::initPathRouting()
{
    ADD_METHOD_TO(Hello::GraphQL, "/graphql", Post);
    return;
}

void DgSample::Hello::GraphQL(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    try
    {
        graphql::peg::ast ast;
		std::string response;
		ProcessQuery(&ast, req);
		ResolveQuery(&ast, &response);

        auto httpResponse = HttpResponse::newHttpJsonResponse(response);
        httpResponse->setStatusCode(HttpStatusCode::k200OK);
        callback(httpResponse);
    }
    catch(const HttpError& e)
    {
		auto response = HttpResponse::newHttpJsonResponse(e.getJson());
		HttpStatusCode statusCode = static_cast<HttpStatusCode>(e.getStatusCode());
		response->setStatusCode(statusCode);
        callback(response);
        return;
    }
}

void DgSample::Hello::ProcessQuery(graphql::peg::ast* ast, const HttpRequestPtr& request)
{
    auto query = request->body();

	ParseQuery(ast, query);
    // Parse GraphQL document
    
    if (!ast->root)
    {
        throw HttpError(400, "Invalid GraphQL query");
    }
}

void DgSample::Hello::ParseQuery(graphql::peg::ast* ast, std::string_view body)
{
	Json::Value queryJson = Json::Value(body);
    Json::Reader reader;
    if (!reader.parse(body.data(), queryJson))
    {
        throw HttpError(400, "Error parsing the string");
    }
    std::string query;
    try
    {
		query = queryJson["query"].asString();
    }
	catch (const std::exception& e)
	{
		std::cout << "Error parsing JSON body: " << e.what() << std::endl;
		throw HttpError(400, "Missing 'query' field in JSON body");
	}

    *ast = graphql::peg::parseString(
        std::move(query)
    );
}

void DgSample::Hello::ResolveQuery(graphql::peg::ast* ast, std::string* response)
{
    // Execute GraphQL operation
    auto result = m_Operations->resolve({
        *ast,
        ""
        }).get();

    // Serialize GraphQL response
    *response = graphql::response::toJSON(std::move(result));
}


