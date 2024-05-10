#include <Core/Base/Assert.h>
#include <Core/Base/NameOf.h>
#include <Core/Misc/CommandLine.h>

namespace ow
{

void CommandLine::Init(int argc, const char** argv)
{
	Assert(argc > 1);
	// The first argument is always the process name. Skip it.
	int argIndex = 1;
	while (argIndex < argc)
	{
		const char* key = argv[argIndex];
		if ('-' == key[0])
		{
			const char* realKey = key + 1;
			const char* value = argv[argIndex + 1];
			if ('-' == value[0])
			{
				// Flag key which has default bool vaule : true.
				m_argumentMap[realKey] = "1";
			}
			else
			{
				++argIndex;
				m_argumentMap[realKey] = value;
			}
		}
		++argIndex;
	}
}

Optional<bool> CommandLine::GetBool(const char* key) const
{
	auto optInt = GetInt(key);
	return optInt.has_value() ? optInt.value() == 1 : optInt;
}

Optional<int32> CommandLine::GetInt(const char* key) const
{
	auto kv = m_argumentMap.find(key);
	if (kv == m_argumentMap.end())
	{
		return NullOpt;
	}
	
	return std::stoi(kv->second);
}

Optional<uint32> CommandLine::GetUInt(const char* key) const
{
	auto optInt = GetInt(key);
	return optInt.has_value() ? static_cast<uint32>(optInt.value()) : optInt;
}

Optional<float> CommandLine::GetFloat(const char* key) const
{
	auto kv = m_argumentMap.find(key);
	if (kv == m_argumentMap.end())
	{
		return NullOpt;
	}

	return std::stof(kv->second);
}

Optional<const char*> CommandLine::GetString(const char* key) const
{
	auto kv = m_argumentMap.find(key);
	if (kv == m_argumentMap.end())
	{
		return NullOpt;
	}

	return kv->second.c_str();
}

}