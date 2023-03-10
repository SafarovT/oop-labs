#include "HTMLDecode.h"


int main()
{
	std::string codedHTMLText;
	if (std::getline(std::cin, codedHTMLText))
	{
		std::cout << HTMLDecode(codedHTMLText);

		return ProgramEndCode::Success;
	}
	else
	{
		return ProgramEndCode::Error;
	}
}