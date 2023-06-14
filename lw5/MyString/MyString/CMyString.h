#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

#include <vector>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(std::string const& stlString);
	~CMyString();
	CMyString(CMyString const& str);
	CMyString(CMyString&& str) noexcept;

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString& operator =(CMyString const& str);
	CMyString& operator =(CMyString&& str) noexcept;
	CMyString operator +(CMyString str);
	CMyString operator +(std::string const& stlString);
	CMyString operator +(const char* pString);
	CMyString& operator +=(CMyString str);
	std::strong_ordering operator<=>(CMyString str) const;
	bool operator==(CMyString str) const;
	char& operator [](size_t index);
	const char& operator [](size_t index) const;
private:
	char* m_pString;
	size_t m_length;
};

inline std::ostream& operator<<(std::ostream& stream, CMyString const& str)
{
	stream << str.GetStringData();

	return stream;
}

inline std::istream& operator>>(std::istream& stream, CMyString& str)
{
	std::string stlString;
	std::getline(stream, stlString);
	str = CMyString(stlString);

	return stream;
}