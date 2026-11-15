#include "Application.hh"

int main(int argc, char** argv)
{
	DgSample::Application* app = new DgSample::Application("config.json");
	app->Run();
	delete app;

    return 0;
}