#pragma once

#include <unordered_map>

namespace ow
{

template<typename K, typename V>
using HashMap = std::unordered_map<K, V>;

}