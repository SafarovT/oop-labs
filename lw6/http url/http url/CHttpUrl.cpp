#include "CHttpUrl.h"

namespace
{
	using namespace std;

	regex URL_REGEX(R"((http|https)://([\w.]+)(:(\d+))?(/([^\s]+))?)", regex_constants::icase);
	regex DOMAIN_REG(R"(([\w.]+))", regex_constants::icase);

	string ERROR_DOMAIN = "Invalid domain";
	string ERROR_PROTOCOL = "Invalid protocol";
	string ERROR_DOCUMENT = "Invalid document";
	string ERROR_PORT = "Invalid port";
	string ERROR_URL = "Invalid URL";
}

string CHttpUrl::ProtocolToString(Protocol protocol)
{
	switch (protocol)
	{
	case CHttpUrl::Protocol::HTTP:
		return "http";
	case CHttpUrl::Protocol::HTTPS:
		return "https";
	default:
		throw invalid_argument(ERROR_PROTOCOL); // todo: add exception
	}
}

unsigned short CHttpUrl::ReadPort(string const& portStr, Protocol protocol)
{
	if (empty(portStr))
	{
		return GetDefaultProtocolPort(protocol);
	}
	int portNum;
	try
	{
		portNum = stoi(portStr); // TODO: скоратить вложенность
	}
	catch (exception& e)
	{
		throw invalid_argument(ERROR_PORT);
	}
	if (portNum < MIN_PORT || portNum > MAX_PORT)
	{
		throw invalid_argument(ERROR_PORT);
	}

	return portNum;
}

CHttpUrl::Protocol CHttpUrl::StringToProtocol(string const& protocol)
{
	string protocolLowerCase = StringToLowerCase(protocol);
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	if (protocol == "https")
	{
		return Protocol::HTTPS;
	}

	throw invalid_argument(ERROR_PROTOCOL);// TODO: скоратить вложенность
}

unsigned short CHttpUrl::GetDefaultProtocolPort(Protocol protocol)
{
	switch (protocol)
	{
	case CHttpUrl::Protocol::HTTP:
		return 80;
	case CHttpUrl::Protocol::HTTPS:
		return 443;
	default:
		throw invalid_argument(ERROR_PROTOCOL);
	}
}

string CHttpUrl::ValidateDomain(string const& domain)
{
	// вынести regexp в const
	if (!regex_match(domain, DOMAIN_REG))
	{
		throw invalid_argument(ERROR_DOMAIN);
	}

	return domain;
}

string CHttpUrl::ValidateDocument(string const& document)
{
	if (document.empty())//лучше empty
	{
		throw invalid_argument(ERROR_DOCUMENT);
	}

	if (document[0] != URL_DELIMITER)//const delemeter
	{
		return URL_DELIMITER + document;
	}
	//вложенность можно убрать

	return document;
}

CHttpUrl::Protocol CHttpUrl::ValidateProtocol(Protocol protocol)
{
	if (protocol < Protocol::min || protocol > Protocol::max)
	{
		throw invalid_argument(ERROR_PROTOCOL);
	}

	return protocol;
}

unsigned short CHttpUrl::ValidatePort(unsigned short port)
{
	if (port < CHttpUrl::MIN_PORT || port > CHttpUrl::MAX_PORT)
	{
		throw invalid_argument(ERROR_PORT);
	}

	return port;
}

CHttpUrl::CHttpUrl(string const& url)
{
	smatch matchedResult;
	if (!regex_match(url, matchedResult, URL_REGEX))
	{
		throw CUrlParsingException(ERROR_URL);
	}
	try
	{
		Protocol protocol = StringToProtocol(matchedResult[1]);
		unsigned short port = ReadPort(matchedResult[4], protocol);
		m_protocol = protocol;
		m_port = port;
		m_document = URL_DELIMITER;
		m_document += matchedResult[6];
		m_domain = matchedResult[2];
	}
	catch (invalid_argument& exception)
	{
		throw CUrlParsingException(exception.what());
	}
}

string CHttpUrl::GetDomain() const
{
	return m_domain;
}

string CHttpUrl::GetDocument() const
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

string CHttpUrl::GetURL() const
{
	string url;
	Protocol protocol = GetProtocol();
	unsigned short port = GetPort();
	try
	{
		url += ProtocolToString(protocol) + "://" + GetDomain();
	}
	catch (exception& e)
	{
		return "Invalid url error";
	}
	if (GetDefaultProtocolPort(protocol) != port)
	{
		url += ":" + to_string(port);
	}
	url += GetDocument();
	return url;
}