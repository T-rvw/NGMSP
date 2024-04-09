#include "VulkanTypes.h"

namespace ow
{

VkFormat ToVK(const RHIFormat& rhiType)
{
    switch (rhiType)
    {
    case RHIFormat::Unknown:
        return VK_FORMAT_UNDEFINED;
    case RHIFormat::R8G8B8A8Unorm:
        return VK_FORMAT_R8G8B8_UNORM;
    case RHIFormat::R8G8B8A8UnormSrgb:
        return VK_FORMAT_R8G8B8_SRGB;
    case RHIFormat::R16G16B16A16Float:
        return VK_FORMAT_R16G16B16_UNORM;
    case RHIFormat::R32G32Float:
        return VK_FORMAT_R32G32_SFLOAT;
    case RHIFormat::R32G32B32Float:
        return VK_FORMAT_R32G32B32_SFLOAT;
    case RHIFormat::R32G32B32A32Float:
        return VK_FORMAT_R32G32B32A32_SFLOAT;
    case RHIFormat::D32Float:
        return VK_FORMAT_D32_SFLOAT;
    case RHIFormat::R32Uint:
        return VK_FORMAT_R32_UINT;
    case RHIFormat::R16Uint:
        return VK_FORMAT_R16_UINT;
    case RHIFormat::D24UnormS8Uint:
        return VK_FORMAT_D24_UNORM_S8_UINT;
    case RHIFormat::R11G11B10Float:
        return VK_FORMAT_B10G11R11_UFLOAT_PACK32;
    default:
        return VK_FORMAT_UNDEFINED;
    }
}

}