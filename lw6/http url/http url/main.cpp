#include <iostream>
#include "CHttpUrl.h"

namespace
{
    using namespace std;

	const std::string EXIT_COMMAND = "exit";
	const std::string STARTUP_MESSAGE = "Для завершения программы введите '" + EXIT_COMMAND + "'";
	const std::string INCORRECT_URL_MESSAGE = "Ссылка не распознана";
	const std::string DOMAIN_MESSAGE = "DOMAIN: ";
	const std::string PORT_MESSAGE = "PORT: ";
	const std::string DOCUMENT_MESSAGE = "DOC: ";

	void WaitUserCommand(string& input)
	{
		do
		{
			getline(cin, input);
		} while (input.empty());
	}

	void PrintUrlInfo(CHttpUrl url)
	{
		cout << DOMAIN_MESSAGE << url.GetDomain() << endl
			<< PORT_MESSAGE << url.GetPort() << endl
			<< DOCUMENT_MESSAGE << url.GetDocument() << endl;
	}
}

int main()
{
	string input;
	cout << STARTUP_MESSAGE << endl;
	WaitUserCommand(input);
	while (input != EXIT_COMMAND)
	{
		try
		{
			CHttpUrl url(input);
			PrintUrlInfo(url);
		}
		catch (CUrlParsingException& exception)
		{
			cout << exception.what() << endl;
		}
		WaitUserCommand(input);
	}

    return EXIT_SUCCESS;
}