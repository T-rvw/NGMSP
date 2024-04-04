#include <RHI/RHIUtils.h>

#include <RHI/RHIAdapter.h>

namespace ow
{

RHIAdapter* FindBestRHIAdapter(std::vector<RHIAdapter>& adapters)
{
	RHIAdapter* pBestAdapter = nullptr;

	uint64 bestScore = 0;
	for (auto& adapter : adapters)
	{
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
			pBestAdapter = &adapter;
			bestScore = score;
		}
	}

	return pBestAdapter;
}

}