#pragma once

#include <algorithm>

namespace nonsense {

template <typename T, std::size_t Size>
constexpr bool array_equal(const T (&x)[Size], const T (&y)[Size]) {
	return std::equal(x, x + Size, y);
}

} // namespace nonsense
