#include <iostream>
#include <drogon/drogon.h>

int main(int argc, char** argv)
{
    auto& app = drogon::app();

    app.loadConfigFile("config.json");

    const auto& config = app.getCustomConfig();

    LOG_INFO << "======================================";
    LOG_INFO << "          DrogonSample Server         ";
    LOG_INFO << "======================================";

    LOG_INFO << " Environment : "
        << config["environment"].asString();

    LOG_INFO << " Application : "
        << config["application_name"].asString();

    LOG_INFO << "======================================";

    app.run();

    return 0;
}