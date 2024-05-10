#pragma once

#include <Core/Base/CString.h>
#include <Core/Base/Map.h>
#include <Core/Base/Optional.h>
#include <Core/Base/String.h>
#include <Core/HAL/APIDefinition.h>
#include <Core/HAL/BasicTypes.h>

namespace ow
{

class CommandLine
{
public:
	CORE_API CommandLine() = default;
	CommandLine(const CommandLine&) = delete;
	CommandLine& operator=(const CommandLine&) = delete;
	CORE_API CommandLine(CommandLine&&) = default;
	CORE_API CommandLine& operator=(CommandLine&&) = default;
	CORE_API ~CommandLine() = default;

	CORE_API void Init(int argc, const char** argv);
	CORE_API Optional<bool> GetBool(const char* key) const;
	CORE_API Optional<int32> GetInt(const char* key) const;
	CORE_API Optional<uint32> GetUInt(const char* key) const;
	CORE_API Optional<float> GetFloat(const char* key) const;
	CORE_API Optional<const char*> GetString(const char* key) const;

	template<typename T>
	Optional<T> GetEnum(const char* key) const
	{
		auto kv = m_argumentMap.find(key);
		if (kv == m_argumentMap.end())
		{
			return NullOpt;
		}

		// Requires enum start from 0 and no holes.
		constexpr auto enumCount = EnumCount<T>();
		for (int32 enumIndex = 0; enumIndex < enumCount; ++enumIndex)
		{
			auto enumValue = static_cast<T>(enumIndex);
			if (CString::Compare(kv->second.c_str(), EnumName<T>(enumValue).data(), false))
			{
				return enumValue;
			}
		}

		return NullOpt;
	}

private:
	Map<String, String> m_argumentMap;
};

}