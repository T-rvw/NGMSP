#pragma once

#include <Core/Base/TypeTraits.h>
#include <Core/HAL/BasicTypes.h>

namespace ow
{

/// <summary>
/// UniquePtr helps to manage heap memory ownship without paying attention to who should delete the memory.
/// No customized deleter applied. TODO : global heap manager needs to replace delete directly here. 
/// </summary>
template<typename T>
class UniquePtr
{
public:
	UniquePtr() :
		m_ptr(nullptr)
	{
	}

	UniquePtr(decltype(__nullptr)) :
		m_ptr(nullptr)
	{
	}

	UniquePtr(T* pOther) :
		m_ptr(pOther)
	{
	}

	template<typename U,
		typename = std::enable_if<std::is_convertible_v<U*, T*>>>
	explicit UniquePtr(U* pOther) :
		m_ptr(pOther)
	{
	}

	// No Copy
	UniquePtr(const UniquePtr& other) = delete;
	UniquePtr& operator=(const UniquePtr& other) = delete;

	// Move
	UniquePtr(UniquePtr&& other) :
		m_ptr(other.Relinquish())
	{
	}

	// Destroy
	~UniquePtr()
	{
		Reset();
	}

	// Assignment
	UniquePtr& operator=(decltype(__nullptr))
	{
		Reset();
		return *this;
	}

	UniquePtr& operator=(UniquePtr&& other)
	{
		if (m_ptr != other.m_ptr)
		{
			Reset(other.Relinquish());
		}
		return *this;
	}

	template<typename U,
		typename = std::enable_if<std::is_convertible_v<U*, T*>>>
	UniquePtr& operator=(UniquePtr<U>&& other)
	{
		Reset(other.Relinquish());
		return *this;
	}

	// Operations
	bool IsValid() const
	{
		return m_ptr != nullptr;
	}

	operator bool() const
	{
		return IsValid();
	}

	T* Get() const
	{
		return m_ptr;
	}

	operator T*() const
	{
		return m_ptr;
	}

	T* operator->() const
	{
		return m_ptr;
	}

	T** operator&()
	{
		return &m_ptr;
	}

	void Reset(T* ptr = nullptr)
	{
		if (m_ptr != ptr)
		{
			T* pTemp = m_ptr;
			m_ptr = ptr;
			delete pTemp;
		}
	}

	[[nodiscard]] T* Relinquish()
	{
		T* pTemp = m_ptr;
		m_ptr = nullptr;
		return pTemp;
	}

	bool operator==(const UniquePtr& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const UniquePtr& other) const
	{
		return m_ptr != other.m_ptr;
	}

	bool operator==(T* pOther) const
	{
		return m_ptr == pOther;
	}

	bool operator!=(T* pOther) const
	{
		return m_ptr != pOther;
	}

protected:
	template<class U> friend class UniquePtr;

private:
	T* m_ptr;
};

template<typename T, typename... Args>
UniquePtr<T> MakeUniquePtr(Args&&... args)
{
	return UniquePtr<T>(new T(Forward<Args>(args)...));
}

}