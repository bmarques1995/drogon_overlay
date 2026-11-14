#pragma once

#include <exception>
#include <string>
#include <Json/Json.h>
#include "ServerExport.hh"

namespace DgSample
{
    class SERVER_API HttpError : public std::exception
    {
    public:
        HttpError(unsigned int statusCode, const std::string& message);
        ~HttpError() = default;

        unsigned int getStatusCode() const;
        const char* what() const noexcept override;
        const Json::Value& getJson() const;

    private:
        unsigned int m_StatusCode;
        std::string m_Message;
        Json::Value m_Json;
    };
}