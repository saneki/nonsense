#pragma once

#include <numeric>
#include <type_traits>
#include <utility>

namespace nonsense {

namespace details {
	template <typename T>
	struct iota_noexcept {
		// NOTE: This assumes iota iterator type is pointer to type T.
		static inline constexpr bool value = noexcept(*std::declval<T*>() = ++std::declval<T&>());
	};

	template <typename T>
	static inline constexpr bool iota_noexcept_v = iota_noexcept<T>::value;
} // namespace details

// Helper for std::iota with a fixed-size array.
template <typename T, std::size_t Size, T Value = T(0)>
constexpr void iota(T (&buffer)[Size]) noexcept(details::iota_noexcept_v<T>) {
	std::iota(buffer, buffer + Size, Value);
}

} // namespace nonsense
