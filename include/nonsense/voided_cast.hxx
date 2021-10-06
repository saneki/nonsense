#pragma once

#include <type_traits>

namespace nonsense {

/**
 * Performs pointer-casting using static_cast by first casting to an intermediate void pointer.
 **/
template <typename TDest, typename TSrc,
		  std::enable_if_t<std::is_pointer_v<TDest>, bool> = true,
		  std::enable_if_t<std::is_pointer_v<TSrc>, bool> = true
>
constexpr TDest voided_cast(TSrc src) noexcept {
	// NOTE: This assumes a pointer depth of no more than 1.
	using TVoid =
		std::conditional_t<std::is_const_v<std::remove_pointer_t<TSrc>>,
			const void *,
			void *
		>;
	return static_cast<TDest>(static_cast<TVoid>(src));
}

} // namespace nonsense
