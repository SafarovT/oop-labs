#include "../../../../external/catch2/catch.hpp"
#include "../ParseURL/ParseURL.h"


TEST_CASE("ParseURL: testing case insensitive protocol with httpS")
{
	std::string url = "httpS://hostName";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	ParseURL(url, protocol, port, host, document);

	REQUIRE(protocol == Protocol::HTTPS);
}

TEST_CASE("ParseURL: testing host with .domain")
{
	std::string url = "http://hostName.com";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	ParseURL(url, protocol, port, host, document);

	REQUIRE(host == "hostName.com");
}

TEST_CASE("ParseURL: testing default port")
{
	std::string url = "ftp://hostName.com";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	ParseURL(url, protocol, port, host, document);

	REQUIRE(port == 21);
}

TEST_CASE("ParseURL: testing set (minimum) port")
{
	std::string url = "ftp://hostName.com:1";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	bool b = ParseURL(url, protocol, port, host, document);

	REQUIRE(b);
}

TEST_CASE("ParseURL: testing set (maximum) port")
{
	std::string url = "ftp://hostName.com:65535";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	ParseURL(url, protocol, port, host, document);

	REQUIRE(port == 65535);
}

TEST_CASE("ParseURL: empty document")
{
	std::string url = "https://hostName.com:10000";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	ParseURL(url, protocol, port, host, document);

	REQUIRE(document == "");
}

TEST_CASE("ParseURL: document")
{
	std::string url = "http://hostName/folder";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	ParseURL(url, protocol, port, host, document);

	REQUIRE(document == "folder");
}

TEST_CASE("ParseURL: document with query params")
{
	std::string url = "ftp://hostName.com:20/folder/file?isLogged=true&userType=admin";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	ParseURL(url, protocol, port, host, document);

	REQUIRE(document == "folder/file?isLogged=true&userType=admin");
}

// Tests with invalid url

TEST_CASE("ParseURL: unknown protocol")
{
	std::string url = "htp://hostName.com";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	bool success = ParseURL(url, protocol, port, host, document);

	REQUIRE(!success);
}

TEST_CASE("ParseURL: no host ")
{
	std::string url = "htp://:20/document";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	bool success = ParseURL(url, protocol, port, host, document);

	REQUIRE(!success);
}

TEST_CASE("ParseURL: error syntax (:/ expected ://) ")
{
	std::string url = "htp:/host/document";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	bool success = ParseURL(url, protocol, port, host, document);

	REQUIRE(!success);
}

TEST_CASE("ParseURL: testing set (minimum - 1) port")
{
	std::string url = "ftp://hostName.com:0";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	bool success = ParseURL(url, protocol, port, host, document);

	REQUIRE(!success);
}

TEST_CASE("ParseURL: testing set (maximum + 1) port")
{
	std::string url = "ftp://hostName.com:65536";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	bool success = ParseURL(url, protocol, port, host, document);

	REQUIRE(!success);
}