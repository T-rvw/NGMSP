#pragma once

#include <Core/Base/Hash/FastCRC32.h>
#include <Core/HAL/APIDefinition.h>
#include <Core/HAL/BasicTypes.h>

#include <string>

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

public:
	StringID() = default;
	explicit constexpr StringID(std::string_view sv) : m_hashValue(FastCRCHash<T>(sv.data(), sv.size())) {}
	explicit constexpr StringID(const char* str, uint64 n) : m_hashValue(FastCRCHash<T>(str, n)) {}
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
	uint64_t operator()(const ow::StringID& key) const
	{
		return static_cast<uint32_t>(key.Value());
	}
};