#pragma once

#include <Core/Base/TypeTraits.h>
#include <Core/HAL/BasicTypes.h>

#include <atomic>

namespace ow
{

/// <summary>
/// Interface for reference count object which wants to customize implementation.
/// Method names are same to Windows COM so RefCountPtr<T> can replace ComPtr<T> directly. 
/// </summary>
class IRefCountObject
{
public:
	virtual ~IRefCountObject() {}
	virtual uint32 AddRef() const = 0;
	virtual uint32 Release() const = 0;
	virtual uint32 GetRefCount() const = 0;
};

/// <summary>
/// Thread-safe reference count object which can be used to inherit conveniently.
/// </summary>
class RefCountObject
{
public:
	RefCountObject() :
		m_refCount(0)
	{
	}

	RefCountObject(const RefCountObject& other) = delete;
	RefCountObject& operator=(const RefCountObject& other) = delete;
	RefCountObject(RefCountObject&& other) = default;
	RefCountObject& operator=(RefCountObject&& other) = default;

	virtual ~RefCountObject()
	{
		assert(0 == m_refCount.load());
	}

	uint32 AddRef() const
	{
		return m_refCount.fetch_add(1);
	}

	uint32 Release() const
	{
		int32 refCount = m_refCount.fetch_sub(1);
		if (0 == refCount)
		{
			delete this;
		}

		return refCount;
	}

	uint32 GetRefCount() const
	{
		return m_refCount.load();
	}

private:
	mutable std::atomic<int32> m_refCount;
};

/// <summary>
/// RefCountPtr helps to manage lifetime of objects which use heap memory.
/// Windows ComPtr is platform specified implementation.
/// std::shared_ptr/std::weak_ptr may have different STL versions between user program and library.
/// </summary>
/// <typeparam name="T">Reference object type</typeparam>
template<typename T>
class RefCountPtr
{
public:
	RefCountPtr() :
		m_ptr(nullptr)
	{
	}

	RefCountPtr(decltype(__nullptr)) :
		m_ptr(nullptr)
	{
	}

	template<typename U>
	RefCountPtr(U* ptr) :
		m_ptr(ptr)
	{
		InternalAddRef();
	}

	// Copy
	RefCountPtr(const RefCountPtr& other) :
		m_ptr(other.m_ptr)
	{
		InternalAddRef();
	}

	template<typename U>
	RefCountPtr(const RefCountPtr<U>& other) :
		m_ptr(other.m_ptr)
	{
		static_assert(std::is_convertible_v<U*, T*>);
		InternalAddRef();
	}

	// Move
	RefCountPtr(RefCountPtr&& other) :
		m_ptr(other.m_ptr)
	{
		other.m_ptr = nullptr;
	}

	// Destroy
	~RefCountPtr()
	{
		InternalRelease();
	}

	// Assignment
	RefCountPtr& operator=(decltype(__nullptr))
	{
		InternalRelease();
		return *this;
	}

	RefCountPtr& operator=(T* pOther)
	{
		if (m_ptr != pOther)
		{
			RefCountPtr(pOther).Swap(*this);
		}
		return *this;
	}

	template<typename U>
	RefCountPtr& operator=(U* pOther)
	{
		static_assert(std::is_convertible_v<U*, T*>);
		RefCountPtr(pOther).Swap(*this);
		return *this;
	}

	RefCountPtr& operator=(const RefCountPtr& other)
	{
		return *this = other.m_ptr;
	}

	template<typename U>
	RefCountPtr& operator=(const RefCountPtr<U>& other)
	{
		static_assert(std::is_convertible_v<U*, T*>);
		return *this = other.m_ptr;
	}

	RefCountPtr& operator=(RefCountPtr&& other)
	{
		RefCountPtr(other).Swap(*this);
		return *this;
	}

	template<typename U>
	RefCountPtr& operator=(RefCountPtr<U>&& other)
	{
		return *this = other;
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

	operator T() const
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

	T** GetAddressOf()
	{
		return &m_ptr;
	}

	T* const* GetAddressOf() const
	{
		return &m_ptr;
	}

	T** ReleaseAndGetAddressOf()
	{
		InternalRelease();
		return &m_ptr;
	}

	void Reset()
	{
		InternalRelease();
	}

	uint32 GetRefCount() const
	{
		uint32 result = 0;
		if (m_ptr)
		{
			result = m_ptr->GetRefCount();
			assert(result > 0);
		}

		return result;
	}

	void Swap(RefCountPtr& other)
	{
		T* pTemp = m_ptr;
		m_ptr = other.m_ptr;
		other.m_ptr = pTemp;
	}

	void Attach(T* pOther)
	{
		if (m_ptr != nullptr)
		{
			m_ptr->Release();
		}

		m_ptr = pOther;
	}

	T* Detach()
	{
		T* pTemp = m_ptr;
		m_ptr = nullptr;
		return pTemp;
	}

	bool operator==(const RefCountPtr& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const RefCountPtr& other) const
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
	template<class U> friend class RefCountPtr;

	void InternalAddRef()
	{
		if (m_ptr)
		{
			m_ptr->AddRef();
		}
	}

	void InternalRelease()
	{
		T* pTemp = m_ptr;
		if (pTemp)
		{
			m_ptr = nullptr;
			pTemp->Release();
		}
	}

private:
	T* m_ptr;
};

template<typename T, typename... Args>
RefCountPtr<T> MakeRefCountPtr(Args&&... args)
{
	return RefCountPtr<T>(new T(Forward<Args>(args)...));
}

}