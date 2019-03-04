#pragma once
#include <functional>

template <typename T>
class Property
{
	T& internalData;
	std::function<T&(void)> m_getter = [&]() { return internalData; };
	std::function<void(const T&)> m_setter = [&](const T& newData) { internalData = newData; };

public:
	Property() = delete;

	Property(T& value) : internalData(value)
	{
	}

	Property(T& value, std::function<T&(void)> getter) : Property(value), m_getter(getter)
	{
	}

	Property(T& value, std::function<void(const T&)> setter) : Property(value), m_setter(setter)
	{
	}

	Property(T& value, std::function<T&(void)> getter, std::function<void(const T&)> setter)
		: Property(value), m_getter(getter), m_setter(setter)
	{
	}

	Property(T& value, std::function<void(const T&)> setter, std::function<T&(void)> getter)
		: Property(value), m_getter(getter), m_setter(setter)
	{
	}

	inline void set(const T& newvalue)
	{
		m_setter(newvalue);
	}
	inline T& get()
	{
		return m_getter();
	}

	void operator= (const T& newvalue)
	{
		m_setter(newvalue);
	}
	operator T()
	{
		return m_getter();
	}
};