#include "RHIUtils.h"

#include <Core/Modules/ModuleManager.h>
#include <RHI/RHI.h>

#include <unordered_set>

namespace ow
{

std::optional<int32> FindBestRHIAdapter(const std::vector<IRHIAdapter*>& adapters)
{
	std::optional<int32> bestAdapterIndex;
	uint64 bestScore = 0;
	for (int32 adapterIndex = 0, adapterCount = static_cast<int32>(adapters.size()); adapterIndex < adapterCount; ++adapterIndex)
	{
		const IRHIAdapter* pAdapter = adapters[adapterIndex];
		const auto& adapterInfo = pAdapter->GetInfo();

		uint64 score = 0;
		if (GPUAdapterType::Discrete == adapterInfo.Type)
		{
			score += 1ULL << 63;
		}
		else if (GPUAdapterType::Integrated == adapterInfo.Type)
		{
			score += 1ULL << 62;
		}
	
		score += adapterInfo.VideoMemorySize >> 20;
	
		if (score > bestScore)
		{
			bestAdapterIndex = adapterIndex;
			bestScore = score;
		}
	}

	return bestAdapterIndex;
}

std::optional<int32> FindBestCommandQueue(RHICommandType commandType, const std::vector<RHICommandQueueCreateInfo*>& createInfos)
{
	std::optional<int32> bestCIIndex;
	float bestScore = 0.0f;
	for (int32 ciIndex = 0, ciCount = static_cast<int32>(createInfos.size()); ciIndex < ciCount; ++ciIndex)
	{
		const auto& createInfo = createInfos[ciIndex];
		if (commandType == createInfo->Type)
		{
			float score = 0.0f;
			if (createInfo->IsDedicated)
			{
				score += 1U << 31;
			}
			score += createInfo->Priority;
			
			if (score > bestScore)
			{
				bestCIIndex = ciIndex;
				bestScore = score;
			}
		}
	}

	return bestCIIndex;
}

std::vector<RHICommandQueueCreateInfo*> FindBestCommandQueues(const std::vector<RHICommandType>& commandTypes, const std::vector<RHICommandQueueCreateInfo*>& createInfos)
{
	std::vector<RHICommandQueueCreateInfo*> bestCommandQueueCIs;

	std::unordered_set<int32> queueIndexes;
	for (auto commandType : commandTypes)
	{
		if (auto optIndex = FindBestCommandQueue(commandType, createInfos); optIndex.has_value())
		{
			queueIndexes.insert(optIndex.value());
		}
	}

	for (auto queueIndex : queueIndexes)
	{
		bestCommandQueueCIs.push_back(createInfos[queueIndex]);
	}

	return bestCommandQueueCIs;
}

}