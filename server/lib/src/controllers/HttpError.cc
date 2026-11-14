#include "HttpError.hh"

DgSample::HttpError::HttpError(unsigned int statusCode, const std::string& message) :
	m_StatusCode(statusCode),
	m_Message(message)
{
	m_Json["error"] = message;
}

unsigned int DgSample::HttpError::getStatusCode() const
{
	return m_StatusCode;
}

const char* DgSample::HttpError::what() const noexcept
{
	return m_Message.c_str();
}

const Json::Value& DgSample::HttpError::getJson() const
{
	return m_Json;
}
