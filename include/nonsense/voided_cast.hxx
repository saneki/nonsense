#pragma once

#include <type_traits>
#include <nonsense/type_traits.hxx>

namespace nonsense {

/**
 * Performs pointer-casting using static_cast by first casting to an intermediate void pointer.
 **/
template <typename TDest, typename TSrc,
		  std::enable_if_t<std::is_pointer_v<TDest>, bool> = true,
		  std::enable_if_t<std::is_pointer_v<TSrc>, bool> = true
>
constexpr TDest voided_cast(TSrc src) noexcept {
	using TVoid = apply_pointer_cv_t<void *, TSrc>;
	return static_cast<TDest>(static_cast<TVoid>(src));
}

} // namespace nonsense
