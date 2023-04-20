#include "HTMLDecode.h"

namespace
{
	using namespace std;

	const size_t MAX_CODED_SYMBOL_STRING_LENGTH = 6;//TODO: rename MAX_HTML_ENTITY

	map<string_view, char> htmlEntitiesDecodes = { //TODO: htmlEntitiesToSymbols
		{"&quot;", '"'},
		{"&apos;", '\''},
		{"&lt;", '<'},
		{"&gt;", '>'},
		{"&amp;", '&'}
	};

	bool IsElementFound(size_t foundIndex)
	{
		return foundIndex != string::npos;
	}

	optional<char> getSymbolIfReplacingStringFound(string_view stringToSearch)
	{
		size_t entityEnd = stringToSearch.find(';');// TODO use const
		if (IsElementFound(entityEnd))
		{
			auto decodedEntity = htmlEntitiesDecodes.find(stringToSearch.substr(0, entityEnd + 1)); 
			if (decodedEntity != htmlEntitiesDecodes.end())
			{
				return	decodedEntity->second;
			}
		}

		return std::nullopt;
	}
}

string HTMLDecode(string_view html)
{
	string decodedHTML;
	decodedHTML.reserve(html.size());
	size_t lastFindIndex = 0;
	size_t nextEntityStart = html.find('&');//TODO: use const
	while (IsElementFound(nextEntityStart))
	{
		decodedHTML += html.substr(lastFindIndex, nextEntityStart - lastFindIndex);
		auto symbolToReplaceWith = getSymbolIfReplacingStringFound(html.substr(nextEntityStart));
		if (symbolToReplaceWith)
		{
			decodedHTML += *symbolToReplaceWith;
			lastFindIndex = html.find(';', nextEntityStart) + 1;
		}
		else
		{
			decodedHTML += '&';
			lastFindIndex = nextEntityStart + 1;
		}
		nextEntityStart = html.find('&', lastFindIndex);
	}
	decodedHTML += html.substr(lastFindIndex);//TODO: lastFoundIndex

	return decodedHTML;
}