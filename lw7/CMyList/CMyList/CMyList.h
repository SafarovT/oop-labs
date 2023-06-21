#pragma once
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <string>

namespace
{
	const std::string MAX_SIZE_ERROR = "List can't be larger then max value of size_t";
	const std::string EMPTY_ERROR = "List is empty";
	const std::string OUT_OF_RANGE_ERROR = "This element is out of range";
}

template <typename T>
class CMyList
{
public:
	typedef CMyListIterator<T> iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;

	void Push(T item);
	void PushFront(T item);
	void Insert(T item, size_t pos);
	void Erase(size_t pos);
	size_t GetSize() const;

	CMyList() = default;
	~CMyList();
	CMyStack(CMyStack const& stack);
	CMyStack& operator =(CMyStack const& stack);

	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();
private:
	struct ListNode
	{
		ListNode(T initValue, StackNode* prevNode, StackNode* nextNode)
			: value(std::move(initValue))
			, next(nextNode)
			, prev(prevNode)
		{}

		T value;
		ListNode* prev;
		ListNode* next;
	};

	ListNode* m_first = nullptr;
	ListNode* m_last = nullptr;
	size_t m_size = 0;

	void PushFirstElement(T item);
};

template <typename T>
void CMyList<T>::PushFirstElement(T item)
{
	m_first = new ListNode(item, nullptr, nullptr);
	m_last = m_first;
}

template <typename T>
void CMyList<T>::Push(T item)
{
	if (m_size == SIZE_MAX)
	{
		throw std::logic_error(MAX_SIZE_ERROR);
	}
	if (m_size == 0)
	{
		PushFirstElement(item);
	}
	else
	{
		m_first->prev = new ListNode(item, nullptr, m_first);
		m_first = m_first->prev;
	}
	m_size++;
}

template <typename T>
void CMyList<T>::PushFront(T item)
{
	if (m_size == SIZE_MAX)
	{
		throw std::logic_error(MAX_SIZE_ERROR);
	}
	if (m_size == 0)
	{
		PushFirstElement(item);
	}
	else
	{
		m_last->next = new ListNode(item, m_last, nullptr);
		m_last = m_first->next;
	}
	m_size++;
}

template <typename T>
void CMyList<T>::Insert(T item, size_t pos)
{
	if (m_size == SIZE_MAX)
	{
		throw std::logic_error(MAX_SIZE_ERROR);
	}
	if (pos >= m_size)
	{
		throw std::out_of_range("");
	}
	if (m_size == 0)
	{
		PushFirstElement(item);
	}
	else
	{
		ListNode* node = m_first;
		for (size_t i = 0; i < pos; i++)
		{
			node++;
		}
		node->prev->next = new ListNode(item, node->prev, node);
	}
	m_size++;
}

template <typename T>
void CMyList<T>::Erase(size_t pos)
{
	if (m_size == 0)
	{
		throw std::logic_error(EMPTY_ERROR);
	}
}

template <typename T>
size_t CMyList<T>::GetSize() const
{
	return m_size;
}

template <typename T>
class CMyListIterator : public std::iterator<std::input_iterator_tag, T>
{
	friend class CMyList;
public:
	CMyListIterator(const CMyListIterator& it);

	bool operator!=(CMyListIterator const& other) const;
	bool operator==(CMyListIterator const& other) const;
	typename CMyListIterator::reference operator*() const;
	CMyListIterator& operator++();
private:
	T* m_p;

	CMyListIterator(T* p);
};

template <typename T>
CMyList<T>::iterator CMyList<T>::begin()
{
    return iterator(m_first);
}

template <typename T>
CMyList<T>::iterator CMyList<T>::end()
{
    return iterator(m_last);
}

template <typename T>
CMyList<T>::reverse_iterator CMyList<T>::rbegin()
{
    return reverse_iterator(end());
}

template <typename T>
CMyList<T>::reverse_iterator CMyList<T>::rend()
{
    return reverse_iterator(begin());
}

template <typename T>
CMyListIterator<T>::CMyListIterator(T* p)
    : m_p(p)
{
}

template <typename T>
CMyListIterator<T>::CMyListIterator(const CMyListIterator& iterator) :
    m_p(iterator.m_p)
{
}

template <typename T>
bool CMyListIterator<T>::operator!=(CMyListIterator const& other) const
{
    return m_p != other.m_p;
}

template <typename T>
bool CMyListIterator<T>::operator==(CMyListIterator const& other) const
{
    return m_p == other.m_p;
}

template <typename T>
typename CMyListIterator<T>::reference CMyListIterator<T>::operator*() const
{
    return *m_p;
}

template <typename T>
CMyListIterator<T>& CMyListIterator<T>::operator++()
{
    ++m_p;
    return *this;
}