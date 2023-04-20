#include "ExpandTemplate.h"
#include <vector>

namespace
{
	using namespace std;
	const int voidLink = -1;

	struct BohrVertex
	{
		int next[UCHAR_MAX + 1]; // 256 значений символов
		int parent;
		int suffixLink;
		int suffixGoodLink;
		int autoMove[UCHAR_MAX + 1];
		char symbol;
		bool leaf;
		string fullString; 
	};
	using Bohr = vector<BohrVertex>;
	
	BohrVertex GetNewVertex()
	{
		BohrVertex vertex;
		// std::fill
		memset(vertex.next, 255, sizeof vertex.next);
		memset(vertex.autoMove, 255, sizeof vertex.autoMove);
		vertex.parent = vertex.suffixLink = vertex.suffixGoodLink = voidLink;
		vertex.leaf = false;
		
		return vertex;
	}

	void InitBohr(Bohr& bohr)
	{
		bohr.push_back(GetNewVertex());
	}

	void AddStringInBohr(Bohr& bohr, string const& stringToAdd)
	{
		int currentVertexPos = 0;
		for (size_t i = 0; i < stringToAdd.length(); i++)
		{
			char symbol = stringToAdd[i];
			if (bohr[currentVertexPos].next[symbol] == voidLink)
			{
				BohrVertex newVertex = GetNewVertex();
				newVertex.parent = currentVertexPos;
				newVertex.symbol = symbol;
				bohr[currentVertexPos].next[symbol] = bohr.size();
				bohr.push_back(newVertex);
			}
			currentVertexPos = bohr[currentVertexPos].next[symbol];
		}
		bohr[currentVertexPos].fullString = stringToAdd;
		bohr[currentVertexPos].leaf = true;
	}

	int GetAutoMove(Bohr& bohr, int vertexPos, char symbol);

	int GetSuffixLink(Bohr& bohr, int vertexPos)
	{
		if (bohr[vertexPos].suffixLink == voidLink)
		{
			if (vertexPos == 0 || bohr[vertexPos].parent == 0)
			{
				bohr[vertexPos].suffixLink = 0;
			}
			else
			{
				bohr[vertexPos].suffixLink = GetAutoMove(bohr, GetSuffixLink(bohr, bohr[vertexPos].parent), bohr[vertexPos].symbol);
			}
		}

		return bohr[vertexPos].suffixLink;
	}

	int GetSuffixGoodLink(Bohr& bohr, int vertexPos)
	{
		if (bohr[vertexPos].suffixGoodLink == voidLink) {
			int vertexPosOnSuffixLink = GetSuffixLink(bohr, vertexPos);
			if (vertexPosOnSuffixLink == 0)
			{
				bohr[vertexPos].suffixGoodLink = 0;
			}
			else
			{
				bohr[vertexPos].suffixGoodLink = (bohr[vertexPosOnSuffixLink].leaf)
					? vertexPosOnSuffixLink
					: GetSuffixGoodLink(bohr, vertexPosOnSuffixLink);
			}
		}
		return bohr[vertexPos].suffixGoodLink;
	}

	int GetAutoMove(Bohr& bohr, int vertexPos, char symbol)
	{
		if (bohr[vertexPos].autoMove[symbol] == voidLink)
		{
			if (bohr[vertexPos].next[symbol] != voidLink)
			{
				bohr[vertexPos].autoMove[symbol] = bohr[vertexPos].next[symbol];
			}
			else
			{
				bohr[vertexPos].autoMove[symbol] = vertexPos == 0
					? 0
					: GetAutoMove(bohr, GetSuffixLink(bohr, vertexPos), symbol);
			}
		}

		return bohr[vertexPos].autoMove[symbol];
	}

	bool CheckIfFound(Bohr& bohr, int vertexPos)
	{
		for (; vertexPos != 0; vertexPos = GetSuffixLink(bohr, vertexPos))
		{
			if (bohr[vertexPos].leaf)
			{
				return true;
			}
		}

		return false;
	}

	void AddParamsInBohr(Bohr& bohr, TemplateParams const& params)
	{
		for (auto param : params)
		{
			AddStringInBohr(bohr, param.first);
		}
	}

	void ReadUntilIsParam(Bohr& bohr, int& currentVertexPos, string const& tpl, int& stringIndex)
	{
		int newVertexPos = currentVertexPos;
		bool isParamEnded = false;
		
		while (!isParamEnded)
		{
			currentVertexPos = newVertexPos;
			stringIndex++;
			newVertexPos = GetAutoMove(bohr, newVertexPos, tpl[stringIndex]);
			bool isStringEnd = stringIndex >= tpl.length();
			bool isNewParamStarted = bohr[newVertexPos].parent != currentVertexPos;
			isParamEnded = !CheckIfFound(bohr, currentVertexPos) || isStringEnd || isNewParamStarted;
		}
		stringIndex--;
		while (!CheckIfFound(bohr, currentVertexPos))
		{
			currentVertexPos = bohr[currentVertexPos].parent;
			stringIndex--;
		}
	}

	string GetStringToAdd(string const& tpl, TemplateParams const& params, string const& foundString, int lastCopiedPos, int currentPosition)
	{
		int uncopiedStringLength = currentPosition - lastCopiedPos - foundString.length() + 1;
		string beforeFoundString = tpl.substr(lastCopiedPos, uncopiedStringLength);
		string stringToReplaceWith = params.find(foundString)->second;
		return beforeFoundString + stringToReplaceWith;
	}
}

string ExpandTemplate(string const& tpl, TemplateParams const& params)
{
	Bohr bohr;
	string resultString;
	InitBohr(bohr);
	AddParamsInBohr(bohr, params);

	int vertexPos = 0;
	int lastCopiedPos = 0;
	for (int i = 0; i < tpl.length(); i++)
	{
		vertexPos = GetAutoMove(bohr, vertexPos, tpl[i]);

		if (CheckIfFound(bohr, vertexPos))
		{
			ReadUntilIsParam(bohr, vertexPos, tpl, i);
			resultString += GetStringToAdd(tpl, params, bohr[vertexPos].fullString, lastCopiedPos, i);
			lastCopiedPos = i + 1; 
		}
	}
	resultString += tpl.substr(lastCopiedPos);

	return resultString;
}