#pragma once

#include "ServerExport.hh"
#include "schemas/QueryObject.h"
#include "schemas/MutationObject.h"

namespace DgSample
{
	using User = graphql::Dgql::object::User;
	class SERVER_API Queries
	{
	public:
		Queries();
		~Queries() = default;

		std::shared_ptr<User> getUser(graphql::response::IdType id);
		std::vector<std::shared_ptr<User>> getUsers();
	};

	class SERVER_API Mutations
	{
	public:
		Mutations();
		~Mutations() = default;

		std::shared_ptr<User> applyCreateUser(graphql::Dgql::CreateUserInput user);
	};
}