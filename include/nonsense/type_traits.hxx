#pragma once

#include <climits>

namespace nonsense {

namespace detail {
	template <bool IsConst, bool IsVolatile, typename T>
	struct apply_cv_helper {
		using type = T;
	};

	template <typename T>
	struct apply_cv_helper<true, false, T> {
		using type = const T;
	};

	template <typename T>
	struct apply_cv_helper<false, true, T> {
		using type = volatile T;
	};

	template <typename T>
	struct apply_cv_helper<true, true, T> {
		using type = const volatile T;
	};
} // namespace detail

// Apply const-volatile qualifiers from one type to another type.
template <typename T, typename U>
struct apply_cv {
	using type = detail::apply_cv_helper<
		std::is_const_v<U>,
		std::is_volatile_v<U>,
		T
	>::type;
};

template <typename T, typename U>
using apply_cv_t = apply_cv<T, U>::type;

// Apply const-volatile qualifiers from one underlying pointer type to another underlying pointer type.
template <typename T, typename U,
		  std::enable_if_t<std::is_pointer_v<T>, bool> = true,
		  std::enable_if_t<std::is_pointer_v<U>, bool> = true
>
struct apply_pointer_cv {
	using type = std::add_pointer_t<apply_cv_t<
		std::remove_pointer_t<T>,
		std::remove_pointer_t<U>
	>>;
};

template <typename T, typename U>
using apply_pointer_cv_t = apply_pointer_cv<T, U>::type;

// Get size of type in bits, factoring in CHAR_BIT constant.
template <typename T, std::size_t Bits>
struct is_bits_count {
	static constexpr inline bool value = (sizeof(T) * CHAR_BIT) == Bits;
};

template <typename T, std::size_t Bits>
static constexpr inline bool is_bits_count_v = is_bits_count<T, Bits>::value;

} // namespace nonsense
