#include "CMyString.h"
#include <algorithm>

namespace
{
	using namespace std;

	const char ZERO_CODE_CHAR = '\0';
	const char ZERO_CODE_STRING[1] = { '\0' };
}

CMyString::CMyString()
	: m_pString(nullptr)
	, m_length(0)
{
}

CMyString::CMyString(const char* pString)
	: m_pString(new char[strlen(pString) + 1])
	, m_length(strlen(pString))
{
	copy(pString, pString + m_length, m_pString);
	m_pString[m_length] = ZERO_CODE_CHAR;
}

CMyString::CMyString(const char* pString, size_t length)
	: m_pString(new char[length + 1])
	, m_length(length)
{
	copy(pString, pString + length, m_pString);
	m_pString[m_length] = ZERO_CODE_CHAR;
}

CMyString::CMyString(string const& stlString)
	: m_pString(new char[stlString.size() + 1])
	, m_length(stlString.size())
{
	copy(stlString.begin(), stlString.end(), m_pString);
	m_pString[m_length] = ZERO_CODE_CHAR;
}

CMyString::~CMyString()
{
	delete[] m_pString;
}

CMyString::CMyString(CMyString const& str)
	: m_pString(new char[str.GetLength() + 1])
	, m_length(str.GetLength())
{
	copy(str.GetStringData(), str.GetStringData() + m_length, m_pString);
	m_pString[m_length] = ZERO_CODE_CHAR;
}

CMyString::CMyString(CMyString&& str) noexcept
	: m_pString(str.m_pString)
	, m_length(str.m_length)
{
	str.m_pString = nullptr;
	str.m_length = 0;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	if (m_pString == nullptr)
	{
		return ZERO_CODE_STRING;
	}

	return m_pString;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw logic_error("A substring cannot extend beyond the original string");
	}

	if (start + length >= m_length)
	{
		length = m_length - start;
	}
	
	return CMyString(m_pString + start, length);
}

void CMyString::Clear()
{
	delete[] m_pString;
	m_pString = nullptr;
	m_length = 0;
}

CMyString& CMyString::operator =(CMyString const& str)
{
	if (&str != this)
	{
		CMyString tempStr(str);
		swap(m_pString, tempStr.m_pString);
		swap(m_length, tempStr.m_length);
	}

	return *this;
}

CMyString& CMyString::operator =(CMyString&& str) noexcept
{
	if (&str != this)
	{
		delete[] m_pString;
		m_length = str.m_length;
		m_pString = str.m_pString;
		str.m_pString = nullptr;
		str.m_length = 0;
	}

	return *this;
}

CMyString CMyString::operator +(CMyString str)
{
	if (GetLength() >= SIZE_MAX - str.GetLength())
	{
		throw logic_error("String length cant be larger then max size_t value");
	}

	size_t resultLength = GetLength() + str.GetLength();
	char* pResult = new char(resultLength + 1);
	strcpy_s(pResult, GetLength() + 1, GetStringData());
	strcat_s(pResult, resultLength + 2, str.GetStringData());

	return CMyString(pResult, resultLength);
}

CMyString CMyString::operator +(std::string const& stlString)
{
	CMyString str2(stlString);
	return *this + str2;
}

CMyString CMyString::operator +(const char* pString)
{
	CMyString str2(pString);
	return *this + str2;
}

CMyString& CMyString::operator +=(CMyString str)
{
	*this = *this + str;
	return *this;
}

strong_ordering CMyString::operator<=>(CMyString str) const
{
	const char* leftString = GetStringData();
	const char* rightString = str.GetStringData();

	return lexicographical_compare_three_way(leftString, leftString + m_length, rightString, rightString + str.m_length);
}

bool CMyString::operator ==(CMyString str) const
{
	if (m_length != str.m_length)
	{
		return false;
	}

	const char* str1 = GetStringData();
	const char* str2 = str.GetStringData();
	return equal(str1, str1 + m_length, str2, str2 + str.m_length);
}

char& CMyString::operator [](size_t index)
{
	if (index >= m_length)
	{
		throw out_of_range("Index is out of string range");
	}

	return m_pString[index];
}

const char& CMyString::operator [](size_t index) const
{
	if (index >= m_length)
	{
		throw out_of_range("Index is out of string range");
	}

	return m_pString[index];
}