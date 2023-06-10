#include "../../../external/catch2/catch.hpp"
#include "../http url/CHttpUrl.h";

SCENARIO("Создание ссылки при помощи ручной инициализации всех полей")
{
	WHEN("Все поля валидны")
	{
		std::string domain = "mySite.com";
		std::string document = "/doc.html";
		CHttpUrl::Protocol protocol = CHttpUrl::Protocol::HTTPS;
		unsigned short port = 65000;

		THEN("Урл создается и все поля верны")
		{
			CHttpUrl url(domain, document, protocol, port);

			CHECK(url.GetDomain() == domain);
			CHECK(url.GetDocument() == document);
			CHECK(url.GetProtocol() == protocol);
			CHECK(url.GetPort() == port);
			CHECK(url.GetURL() == "https://mySite.com:65000/doc.html");
		}
	}

	WHEN("Все поля верны и порт совпадает со стандартным портом")
	{
		std::string domain = "mySite.com";
		std::string document = "/doc.html";
		CHttpUrl::Protocol protocol = CHttpUrl::Protocol::HTTPS;
		unsigned short port = 443;

		THEN("Порт не выводится")
		{
			CHttpUrl url(domain, document, protocol, port);

			CHECK(url.GetURL() == "https://mySite.com/doc.html");
		}
	}

	WHEN("Все поля верны и порт не указан")
	{
		std::string domain = "mySite.com";
		std::string document = "/doc.html";
		CHttpUrl::Protocol protocol = CHttpUrl::Protocol::HTTP;

		THEN("Порт не выводится")
		{
			CHttpUrl url(domain, document, protocol);

			CHECK(url.GetPort() == 80);
			CHECK(url.GetURL() == "http://mySite.com/doc.html");
		}
	}

	WHEN("Все поля верны и документ без / в начале")
	{
		std::string domain = "mySite.com";
		std::string document = "folder/anotherFolder/document.html";
		CHttpUrl::Protocol protocol = CHttpUrl::Protocol::HTTP;

		THEN("К документу добавился /")
		{
			CHttpUrl url(domain, document, protocol);

			CHECK(url.GetDocument() == "/folder/anotherFolder/document.html");
			CHECK(url.GetURL() == "http://mySite.com/folder/anotherFolder/document.html");
		}
	}

	WHEN("Домен не валиден")
	{
		std::string domain = "12!$#";
		std::string document = "/doc.html";
		CHttpUrl::Protocol protocol = CHttpUrl::Protocol::HTTPS;
		unsigned short port = 65000;

		THEN("Ошибка при создании")
		{
			try
			{
				CHttpUrl url(domain, document, protocol, port);
				CHECK(false);
			}
			catch (std::exception& e)
			{
				CHECK(true);
			}
		}
	}

	WHEN("Протокол не валиден (нижняя граница)")
	{
		std::string domain = "mySite.com";
		std::string document = "/doc.html";
		CHttpUrl::Protocol protocol = static_cast<CHttpUrl::Protocol>(-1);
		unsigned short port = 1;

		THEN("Ошибка при создании")
		{
			try
			{
				CHttpUrl url(domain, document, protocol, port);
				CHECK(false);
			}
			catch (std::exception& e)
			{
				CHECK(true);
			}
		}
	}

	WHEN("Протокол не валиден (верхняя граница)")
	{
		std::string domain = "mySite.com";
		std::string document = "/doc.html";
		CHttpUrl::Protocol protocol = static_cast<CHttpUrl::Protocol>(3);
		unsigned short port = 1;

		THEN("Ошибка при создании")
		{
			try
			{
				CHttpUrl url(domain, document, protocol, port);
				CHECK(false);
			}
			catch (std::exception& e)
			{
				CHECK(true);
			}
		}
	}

	WHEN("Порт не валиден (нижняя граница)")
	{
		std::string domain = "mySite.com";
		std::string document = "/doc.html";
		CHttpUrl::Protocol protocol = CHttpUrl::Protocol::HTTPS;
		unsigned short port = 0;

		THEN("Ошибка при создании")
		{
			try
			{
				CHttpUrl url(domain, document, protocol, port);
				CHECK(false);
			}
			catch (std::exception& e)
			{
				CHECK(true);
			}
		}
	}

	WHEN("Порт не валиден (верхняя граница)")
	{
		std::string domain = "mySite.com";
		std::string document = "/doc.html";
		CHttpUrl::Protocol protocol = CHttpUrl::Protocol::HTTPS;
		unsigned short port = 65536;

		THEN("Ошибка при создаии")
		{
			try
			{
				CHttpUrl url(domain, document, protocol, port);
				CHECK(false);
			}
			catch (std::exception& e)
			{
				CHECK(true);
			}
		}
	}
}

SCENARIO("Проверка чтения данных ссылки из строки")
{
	WHEN("Валидная строка со всемозможными данными")
	{
		std::string urlStr = "http://hostName.com:20/folder/file?isLogged=true&userType=admin";

		THEN("Данные из ссылки читаются верно")
		{
			CHttpUrl url(urlStr);

			CHECK(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
			CHECK(url.GetPort() == 20);
			CHECK(url.GetDocument() == "/folder/file?isLogged=true&userType=admin");
			CHECK(url.GetDomain() == "hostName.com");
		}
	}

	WHEN("Не валидная строка ссылки, в которой после : идет слишком большой порт")
	{
		std::string urlStr = "http://hostName:570598374";

		THEN("Выбрасывается верное исключение при создании объекта")
		{
			try
			{
				CHttpUrl url(urlStr);
				CHECK(false);
			}
			catch (CUrlParsingException& e)
			{
				CHECK(true);
			}
		}
	}
}