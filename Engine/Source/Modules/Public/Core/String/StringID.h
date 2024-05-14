#pragma once

#include <Core/HAL/APIDefines.h>
#include <Core/HAL/BasicTypes.h>
#include <Core/Hash/FastCRC32.h>
#include <Core/String/String.h>
#include <Core/String/StringView.h>

namespace ow
{

/// <summary>
/// Generate hash value for string in compile-time or runtime.
/// </summary>
class StringID
{
public:
	using T = uint32;
	static constexpr T InvalidID() { return 0xFFFFFFFF; }
	static constexpr T GetHashValue(const char* data, uint64 length) { return FastCRCHash<T>(data, length); }

public:
	StringID() = default;
	explicit constexpr StringID(StringView sv) : m_hashValue(GetHashValue(sv.data(), sv.size())) {}
	explicit constexpr StringID(const char* str, uint64 n) : m_hashValue(GetHashValue(str, n)) {}
	StringID(const StringID&) = default;
	StringID& operator=(const StringID&) = default;
	StringID(StringID&&) = default;
	StringID& operator=(StringID&&) = default;
	~StringID() = default;

	constexpr T Value() const { return m_hashValue; }

	bool operator==(const StringID& other) const { return m_hashValue == other.m_hashValue; }
	bool operator!=(const StringID& other) const { return m_hashValue != other.m_hashValue; }

private:
	T m_hashValue;
};

}

template<>
struct std::hash<ow::StringID>
{
	std::uint64_t operator()(const ow::StringID& key) const
	{
		return static_cast<std::uint32_t>(key.Value());
	}
};