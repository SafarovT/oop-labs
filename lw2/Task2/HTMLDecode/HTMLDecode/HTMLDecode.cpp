#include "HTMLDecode.h"

namespace
{
	const size_t MAX_CODED_SYMBOL_STRING_LENGTH = 6;

	std::optional<char> getSymbolIfReplacingStringFound(std::string stringToSearch)
	{
		if (stringToSearch.find("&quot;") == 0) return '"';
		else if (stringToSearch.find("&apos;") == 0) return '\'';
		else if (stringToSearch.find("&lt;") == 0) return '<';
		else if (stringToSearch.find("&gt;") == 0) return '>';
		else if (stringToSearch.find("&amp;") == 0) return '&';

		return std::nullopt;
	}
}

// use map
// use std::string_view const& html

std::string HTMLDecode(std::string const& html)
{
	std::string decodedHTML;
	size_t lastFindIndex = 0;
	size_t nextCodedSymbolStart = html.find('&');
	while (nextCodedSymbolStart != std::string::npos)
	{
		decodedHTML += html.substr(lastFindIndex, nextCodedSymbolStart - lastFindIndex);
		auto symbolToReplaceWith = getSymbolIfReplacingStringFound(html.substr(nextCodedSymbolStart));
		if (symbolToReplaceWith)
		{
			decodedHTML += *symbolToReplaceWith;
			lastFindIndex = html.find(';', nextCodedSymbolStart) + 1;
		}
		else
		{
			decodedHTML += '&';
			lastFindIndex = nextCodedSymbolStart + 1;
		}
		nextCodedSymbolStart = html.find('&', lastFindIndex);
	}
	decodedHTML += html.substr(lastFindIndex);

	return decodedHTML;
}