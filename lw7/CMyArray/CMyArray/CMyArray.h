#pragma once
#include <iterator>
#include <stdexcept>
#include <memory>

template <typename T>
class CMyArray
{
public:
	/*typedef CMyArrayIterator<T> iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator*/

	CMyArray<T>(std::initializer_list<T> items);

	//~CMyArray();
	/*CMyArray(CMyArray const& arr);
	CMyArray(CMyArray&& arr);*/

	/*CMyArray& operator =(CMyArray const& str);
	CMyArray& operator =(CMyArray&& str) noexcept;
	char& operator [](size_t index);
	const char& operator [](size_t index) const;*/

	void Push(T const& item);
	size_t GetSize() const;
	void Resize(size_t newSize);
	void Clear();

	/*iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();*/
private:
	//T* m_pItems = nullptr;
	std::unique_ptr<T[]> m_pItems;
	size_t m_size = 0;
};
// https://habr.com/ru/articles/265491/
//template <typename T>
//class CMyArrayIterator : public std::iterator<std::input_iterator_tag, T>
//{
//	friend class CMyArray;
//public:
//	CMyArrayIterator(const CMyArrayIterator& it);
//
//	bool operator!=(CMyArrayIterator const& other) const;
//	bool operator==(CMyArrayIterator const& other) const;
//	typename CMyArrayIterator::reference operator*() const;
//	CMyArrayIterator& operator++();
//private:
//	T* m_p;
//
//	CMyArrayIterator(T* p);
//};