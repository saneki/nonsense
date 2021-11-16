#pragma once

#include <climits>

namespace nonsense {

// Get size of type in bits, factoring in CHAR_BIT constant.
template <typename T, std::size_t Bits>
struct is_bits_count {
	static constexpr inline bool value = (sizeof(T) * CHAR_BIT) == Bits;
};

template <typename T, std::size_t Bits>
static constexpr inline bool is_bits_count_v = is_bits_count<T, Bits>::value;

} // namespace nonsense
