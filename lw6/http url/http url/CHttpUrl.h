#pragma once
#include <string>
#include <regex>
#include "CUrlParsingException.h"
#include "common.h"

class CHttpUrl
{
public:
	static enum class Protocol
	{
		HTTP = 0, HTTPS = 1,
		min = HTTP, max = HTTPS
	};
	
	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP
	)
	try
		: m_domain(ValidateDomain(domain))
		, m_document(ValidateDocument(document))
		, m_protocol(ValidateProtocol(protocol))
		, m_port(GetDefaultProtocolPort(protocol))
	{
	}
	catch (std::invalid_argument& exception)
	{
		throw exception;
	}

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port
	)
	try
		: m_domain(ValidateDomain(domain))
		, m_document(ValidateDocument(document))
		, m_protocol(ValidateProtocol(protocol))
		, m_port(ValidatePort(port))
	{
	}
	catch (std::invalid_argument& exception)
	{
		throw exception;
	}

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;
private:
	static const unsigned short MIN_PORT = 1;
	static const unsigned short MAX_PORT = 65535;
	static const char URL_DELIMITER = '/';

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	static std::string ProtocolToString(Protocol protocol);
	static Protocol StringToProtocol(std::string const& protocol);
	static unsigned short GetDefaultProtocolPort(Protocol protocol);
	static unsigned short ReadPort(std::string const& portStr, Protocol protocol);
	
	static std::string ValidateDomain(std::string const& domain);
	static std::string ValidateDocument(std::string const& document);
	static Protocol ValidateProtocol(Protocol protocol);
	static unsigned short ValidatePort(unsigned short port);
};