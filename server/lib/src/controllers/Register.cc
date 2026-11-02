#include "Register.hh"
#include "Hello.hh"
#include <drogon/Drogon.h>
#include <memory>

void DgSample::Register::RegisterControllers()
{
	drogon::app().registerController(std::make_shared<Hello>());
}
