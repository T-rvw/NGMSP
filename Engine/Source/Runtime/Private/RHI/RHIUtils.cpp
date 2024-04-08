#include <RHI/RHIUtils.h>

#include <RHI/RHIAdapter.h>

namespace ow
{

std::optional<int32> FindBestRHIAdapter(const std::vector<RHIAdapter>& adapters)
{
	std::optional<int32> bestAdapterIndex;
	uint64 bestScore = 0;
	for (int32 adapterIndex = 0, adapterCount = static_cast<int32>(adapters.size()); adapterIndex < adapterCount; ++adapterIndex)
	{
		const auto& adapter = adapters[adapterIndex];

		uint64 score = 0;
		if (GPUAdapterType::Discrete == adapter.GetType())
		{
			score += 1ULL << 63;
		}
		else if (GPUAdapterType::Integrated == adapter.GetType())
		{
			score += 1ULL << 62;
		}

		score += adapter.GetVideoMemorySize() >> 20;

		if (score > bestScore)
		{
			bestAdapterIndex = adapterIndex;
			bestScore = score;
		}
	}

	return bestAdapterIndex;
}

std::optional<int32> FindBestCommandQueue(RHICommandQueueType commandType, const std::vector<RHICommandQueueCreateInfo>& createInfos)
{
	std::optional<int32> bestCIIndex;
	uint32 bestScore = 0;
	for (int32 ciIndex = 0, ciCount = static_cast<int32>(createInfos.size()); ciIndex < ciCount; ++ciIndex)
	{
		const auto& createInfo = createInfos[ciIndex];
		if (commandType == createInfo.Type)
		{
			uint32 score = 0;
			if (createInfo.IsDedicated)
			{
				score += 1U << 31;
			}
			
			if (score > bestScore)
			{
				bestCIIndex = ciIndex;
				bestScore = score;
			}
		}
	}

	return bestCIIndex;
}

std::vector<RHICommandQueueCreateInfo> FindBestCommandQueues(const std::vector<RHICommandQueueType>& commandTypes, const std::vector<RHICommandQueueCreateInfo>& createInfos)
{
	std::vector<RHICommandQueueCreateInfo> bestCommandQueueCIs;

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