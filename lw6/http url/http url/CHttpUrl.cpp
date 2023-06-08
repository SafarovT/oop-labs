#include "CHttpUrl.h"

std::string CHttpUrl::ProtocolToString(Protocol protocol)
{
	switch (protocol)
	{
	case CHttpUrl::Protocol::HTTP:
		return "HTTP";
	case CHttpUrl::Protocol::HTTPS:
		return "HTTPS";
	default:
		return "????"; // todo: add exception
	}
}

unsigned short CHttpUrl::GetDefaultProtocolPort(Protocol protocol)
{
	const unsigned short HTTP_PORT = 80;
	const unsigned short HTTPS_PORT = 443;
	switch (protocol)
	{
	case CHttpUrl::Protocol::HTTP:
		return HTTP_PORT;
	case CHttpUrl::Protocol::HTTPS:
		return HTTPS_PORT;
	default:
		throw std::invalid_argument("Invalid protocol. Use HTTP or HTTPS");
	}
}

void CHttpUrl::ValidateDomain(std::string const& domain)
{

}

void CHttpUrl::ValidateDocument(std::string& document)
{
	if (document.size() < 1)
	{
		throw std::invalid_argument("Empty document");
	}
	
	if (document[0] != '/')
	{
		document = '/' + document;
	}
}

void CHttpUrl::ValidateProtocol(Protocol protocol)
{
	if (protocol < Protocol::min || protocol > Protocol::max)
	{
		throw std::invalid_argument("Unknown protocol");
	}
}

void CHttpUrl::ValidatePort(unsigned short port)
{
	if (port < CHttpUrl::MIN_PORT || port > CHttpUrl::MAX_PORT)
	{
		std::string minPortString = std::to_string(MIN_PORT);
		std::string maxPortString = std::to_string(MAX_PORT);
		throw std::invalid_argument("Invalid port. Please enter port in" + minPortString + " - " + maxPortString);
	}
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	// in const in private
	std::regex reg(R"((http|https|ftp)://([\w.]+)(:(\d+))?(/([^\s]+))?)", std::regex_constants::icase);
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

CHttpUrl::Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::GetURL() const
{
	std::string url;
	Protocol protocol = GetProtocol();
	unsigned short port = GetPort();
	url += ProtocolToString(protocol) + GetDomain();
	if (GetDefaultProtocolPort(protocol) != port)
	{
		url += ":" + std::to_string(port);
	}
	url += GetDocument();
	return url;
}