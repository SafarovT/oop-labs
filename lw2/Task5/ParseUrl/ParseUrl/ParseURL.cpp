#include "ParseURL.h"
#include <regex>
#include <algorithm>
#include <iostream>


namespace
{
	using namespace std;

	bool SetDefaultPort(int& port, Protocol protocol)
	{
		const int HTTP_PORT = 80;
		const int HTTPS_PORT = 443;
		const int FTP_PORT = 21;
		switch (protocol)
		{
		case Protocol::HTTP: 
			port = HTTP_PORT;
			break;
		case Protocol::HTTPS:
			port = HTTPS_PORT;
			break;
		case Protocol::FTP:
			port = FTP_PORT;
			break;
		default: return false;
		}

		return true;
	}

	string StringToLowerCase(string stringToTransform)
	{
		transform(stringToTransform.cbegin(), stringToTransform.cend(), stringToTransform.begin(), ::tolower);

		return stringToTransform;
	}

	bool SetPort(string portString, int& port, Protocol protocol)
	{
		if (empty(portString))
		{
			return SetDefaultPort(port, protocol);
		}
		else
		{//TODO: упростить
			try
			{
				int portNumber = stoi(portString);
				if (!(portNumber >= 1 && portNumber <= 65535))//TODO: use const
				{
					return false;
				}
				else
				{
					port = portNumber;
				}
			}
			catch (std::exception& e)
			{
				return false;
			}
		}

		return true;
	}

	bool SetProtocol(string protocolString, Protocol& protocol)
	{
		if (protocolString == "http")
		{
			protocol = Protocol::HTTP;
		}
		else if (protocolString == "https")
		{
			protocol = Protocol::HTTPS;

		}
		else if (protocolString == "ftp")
		{
			protocol = Protocol::FTP;
		}
		else
		{
			return false;
		}

		return true;
	}
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	regex reg(R"((http|https|ftp)://([\w.]+)(:(\d+))?(/([^\s]+))?)", regex_constants::icase);//TODO: URL_PATTERN
	smatch matchedResults;
	if (!regex_match(url, matchedResults, reg))
	{
		return false;
	}
	if (!SetProtocol(StringToLowerCase(matchedResults[1]), protocol))
	{
		return false;
	}
	if (!SetPort(matchedResults[4], port, protocol))
	{
		return false;
	} 
	host = matchedResults[2];
	document = matchedResults[6];

	return true;
}