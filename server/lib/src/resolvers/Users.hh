#pragma once

#include "ServerExport.hh"
#include <memory>
#include <vector>
#include "schemas/QueryObject.h"
#include "schemas/MutationObject.h"

namespace DgSample
{
	using CreateUserInput = graphql::Dgql::CreateUserInput;
	class SERVER_API UserResolver
	{
	public:
		UserResolver();
		UserResolver(const std::string& name, const std::string& email);
		~UserResolver() = default;
		
		graphql::response::IdType getId();
		std::string getName();
		std::string getEmail();

	private:
		std::string m_Name;
		std::string m_Email;
		graphql::response::IdType m_Id;
	};

	class SERVER_API UsersResolver
	{
	public:
		UsersResolver();
		UsersResolver(const std::vector<std::shared_ptr<UserResolver>>& users);

		~UsersResolver() = default;

		std::vector<std::shared_ptr<UserResolver>> getUsers();

	private:
		std::vector<std::shared_ptr<UserResolver>> m_Users;
	};

	class SERVER_API UserRegisterResolver
	{
	public:
		UserRegisterResolver();
		~UserRegisterResolver() = default;

		std::shared_ptr<UserResolver> createUser(CreateUserInput& input);
	};
}