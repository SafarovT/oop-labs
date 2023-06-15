#include "CMyArray.h"
#include <algorithm>

namespace
{
	using namespace std;
}

template <typename T>
CMyArray<T>::CMyArray(initializer_list<T> items)
    : m_size(items.size())
    , m_pItems(new T[m_size])
{
    copy(items.begin(), items.end(), m_pItems.get());
}

template <typename T>
void CMyArray<T>::Push(T const& item)
{
    if (m_size == SIZE_MAX)
    {
        throw logic_error("Array is full of elements");
    }

    /*m_pItems + m_size = new T(item);
    m_size++;*/
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
        throw logic_error("Array can't be larger then max value of size_t");
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
    /*for (; m_size > 0; m_size--)
    {
        delete m_pItems + m_size - 1;
    }
    delete m_pItems;*/
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