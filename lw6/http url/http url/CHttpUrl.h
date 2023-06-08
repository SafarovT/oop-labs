#pragma once
#include <string>
#include <regex>
#include "CUrlParsingError.h"

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
		: m_domain(domain)
		, m_document(document)
		, m_protocol(protocol)
		, m_port(GetDefaultProtocolPort(protocol))
	{
	}

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port
	)
		: m_domain(domain)
		, m_document(document)
		, m_protocol(protocol)
		, m_port(port)
	{
	}

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;
private:
	static const unsigned short MIN_PORT = 1;
	static const unsigned short MAX_PORT = 65535;

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	static std::string ProtocolToString(Protocol protocol);
	static unsigned short GetDefaultProtocolPort(Protocol protocol);
	
	static void ValidateDomain(std::string const& domain);
	static void ValidateDocument(std::string& document);
	static void ValidateProtocol(Protocol protocol);
	static void ValidatePort(unsigned short port);
};