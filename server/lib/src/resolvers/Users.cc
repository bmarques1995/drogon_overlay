#include "Users.hh"
#include <iostream>

DgSample::UserResolver::UserResolver()
{
	m_Name = "Default Name";
	m_Email = "default@mail.com";
	m_Id = graphql::response::IdType(std::vector<std::uint8_t>(m_Name.begin(), m_Name.end()));
}

DgSample::UserResolver::UserResolver(const std::string & name, const std::string & email) :
	m_Name(name),
	m_Email(email)
{
	m_Id = graphql::response::IdType(std::vector<std::uint8_t>(name.begin(), name.end()));
}

graphql::response::IdType DgSample::UserResolver::getId()
{
	return m_Id;
}

std::string DgSample::UserResolver::getName()
{
	return m_Name;
}

std::string DgSample::UserResolver::getEmail()
{
	return m_Email;
}

DgSample::UsersResolver::UsersResolver()
{

}

DgSample::UsersResolver::UsersResolver(const std::vector<std::shared_ptr<UserResolver>>& users) :
	m_Users(std::move(users))
{}

std::vector<std::shared_ptr<DgSample::UserResolver>> DgSample::UsersResolver::getUsers()
{
	return m_Users;
}

DgSample::UserRegisterResolver::UserRegisterResolver()
{}

std::shared_ptr<DgSample::UserResolver> DgSample::UserRegisterResolver::createUser(CreateUserInput& input)
{
	std::cout << "Creating user with name: " << input.name << " and email: " << input.email << std::endl;
	return std::make_shared<UserResolver>(input.name, input.email);
}
