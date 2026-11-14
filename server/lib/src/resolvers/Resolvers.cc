#include "Resolvers.hh"
#include "Users.hh"
#include "schemas/UserObject.h"

DgSample::Queries::Queries()
{}

std::shared_ptr<DgSample::User> DgSample::Queries::getUser(graphql::response::IdType id)
{
	auto resolver = std::make_shared<UserResolver>("Leonardo", "leonardo@example.com");
	return std::make_shared<User>(resolver);
}

std::vector<std::shared_ptr<DgSample::User>> DgSample::Queries::getUsers()
{
	auto rawUsers = std::vector<std::shared_ptr<UserResolver>>();
	rawUsers.reserve(2); // Reserve space for 2 users
    rawUsers.push_back(std::make_shared<UserResolver>("Alice", "alice@example.com"));
    rawUsers.push_back(std::make_shared<UserResolver>("Daniele", "daniele@example.com"));
    auto resolver = std::make_shared<UsersResolver>(rawUsers);
    std::vector<std::shared_ptr<User>> users;
    for (const auto& userResolver : resolver->getUsers())
    {
        users.push_back(std::make_shared<User>(userResolver));
    }
    return users;
}

DgSample::Mutations::Mutations()
{}

std::shared_ptr<DgSample::User> DgSample::Mutations::applyCreateUser(graphql::Dgql::CreateUserInput user)
{
    auto resolver = std::make_shared<UserRegisterResolver>();

    auto userResolver = resolver->createUser(user);

    return std::make_shared<User>(userResolver);
}
