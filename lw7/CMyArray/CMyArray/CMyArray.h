#pragma once
#include <iterator>
#include <stdexcept>
#include <algorithm>

template <typename T>
class CMyArray
{
public:
	/*typedef CMyArrayIterator<T> iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator*/

	CMyArray<T>(size_t size);

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
	T* m_pItems = nullptr;
	size_t m_size;
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

template <typename T>
CMyArray<T>::CMyArray(size_t size)
    : m_size(size)
    , m_pItems(new T[m_size])
{
}

template <typename T>
void CMyArray<T>::Push(T const& item)
{
    if (m_size == SIZE_MAX)
    {
        throw std::logic_error("Array is full of elements");
    }
    
    T* itemToUpdate = m_pItems + m_size;
    itemToUpdate = new T(item);
}

template <typename T>
size_t CMyArray<T>::GetSize() const
{
    return m_size;
}

template <typename T>
void CMyArray<T>::Resize(size_t newSize)
{
    if (newSize == SIZE_MAX)
    {
        throw std::logic_error("Array can't be larger then max value of size_t");
    }
    /*if (newSize < m_size)
    {
        for (; newSize < m_size; m_size--)
        {
            delete m_pItems + m_size - 1;
        }
    }
    else if (newSize > m_size)
    {
        for (; newSize > m_size; m_size++)
        {
            m_pItems + m_size = new T();
        }
    }*/
}

template <typename T>
void CMyArray<T>::Clear()
{
    for (; m_size > 0; m_size--)
    {
        T* itemToDelete = m_pItems + m_size - 1;
        delete itemToDelete;
    }
    delete m_pItems;
}

//template <typename T>
//CMyArray<T>::iterator CMyArray<T>::begin()
//{
//    return iterator(m_pItems);
//}
//
//template <typename T>
//CMyArray<T>::iterator CMyArray<T>::end()
//{
//    return iterator(m_pItems + m_size);
//}
//
//template <typename T>
//CMyArray<T>::reverse_iterator CMyArray<T>::rbegin()
//{
//    return reverse_iterator(end());
//}
//// https://www.sololearn.com/compiler-playground/cXi4oXTxrtyL/?ref=app
//template <typename T>
//CMyArray<T>::reverse_iterator CMyArray<T>::rend()
//{
//    return reverse_iterator(begin());
//}
//
//template <typename T>
//CMyArrayIterator<T>::CMyArrayIterator(T* p)
//    : m_p(p)
//{
//}
//
//template <typename T>
//CMyArrayIterator<T>::CMyArrayIterator(const CMyArrayIterator& iterator) :
//    m_p(iterator.m_p)
//{
//}
//
//template <typename T>
//bool CMyArrayIterator<T>::operator!=(CMyArrayIterator const& other) const
//{
//    return m_p != other.m_p;
//}
//
//template <typename T>
//bool CMyArrayIterator<T>::operator==(CMyArrayIterator const& other) const
//{
//    return m_p == other.m_p;
//}
//
//template <typename T>
//typename CMyArrayIterator<T>::reference CMyArrayIterator<T>::operator*() const
//{
//    return *m_p;
//}
//
//template <typename T>
//CMyArrayIterator<T>& CMyArrayIterator<T>::operator++()
//{
//    ++m_p;
//    return *this;
//}