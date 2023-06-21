#pragma once
#include <vector>
#include <memory>
#include <stdexcept>

#include <iostream>

template <class Base, class Passenger>
class CVehicleImpl : public Base
{
public:
	CVehicleImpl(size_t placesCount)
	{
		m_passengers.reserve(placesCount);
	}

	void AddPassenger(std::shared_ptr<Passenger> pPassenger);
	Passenger const& GetPassenger(size_t index) const;
	void RemovePassenger(size_t index);
	bool IsEmpty() const;
	bool IsFull() const;
	size_t GetPlaceCount() const;
	size_t GetPassengerCount() const;
	void RemoveAllPassengers();
private:
	std::vector<std::shared_ptr<Passenger>> m_passengers;
};

template <class Base, class Passenger>
void CVehicleImpl<Base, Passenger>::AddPassenger(std::shared_ptr<Passenger> pPassenger)
{
	if (IsFull())
	{
		throw std::logic_error("All seats had been already taken");
	}

	m_passengers.push_back(pPassenger);
}

template <class Base, class Passenger>
Passenger const& CVehicleImpl<Base, Passenger>::GetPassenger(size_t index) const
{
	if (index >= m_passengers.size())
	{
		throw std::out_of_range("There is not seat with passed number");
	}

	return *m_passengers[index].get();
}

template <class Base, class Passenger>
void CVehicleImpl<Base, Passenger>::RemovePassenger(size_t index)
{
	if (index >= m_passengers.size())
	{
		throw std::out_of_range("There is not seat with passed number");
	}

	m_passengers.erase(m_passengers.begin() + index);
}

template <class Base, class Passenger>
bool CVehicleImpl<Base, Passenger>::IsEmpty() const
{
	return m_passengers.size() == 0;
}

template <class Base, class Passenger>
bool CVehicleImpl<Base, Passenger>::IsFull() const
{
	return m_passengers.size() == m_passengers.capacity();
}

template <class Base, class Passenger>
size_t CVehicleImpl<Base, Passenger>::GetPlaceCount() const
{
	return m_passengers.capacity();
}

template <class Base, class Passenger>
size_t CVehicleImpl<Base, Passenger>::GetPassengerCount() const
{
	return m_passengers.size();
}

template <class Base, class Passenger>
void CVehicleImpl<Base, Passenger>::RemoveAllPassengers()
{
	m_passengers.clear();
}