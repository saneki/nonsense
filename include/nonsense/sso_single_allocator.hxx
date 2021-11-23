#pragma once

#include <memory>

/// Single-allocator supporting small-string-optimization (SSO).
/// Allocating twice before deallocating results in undefined behavior.
namespace nonsense {
template <typename T, std::size_t BufferSize = 0, typename Alloc = std::allocator<T>>
class sso_single_allocator : private Alloc {
public:
	using value_type = T;
	using size_type = std::size_t;
	using array_type = T[BufferSize];
	using array_reference = array_type&;
	using const_array_reference = const array_type&;

	static constexpr const std::size_t buffer_size = BufferSize;

	[[nodiscard]] constexpr T* allocate(size_type n) {
		if (n <= BufferSize)
			return _buffer;
		return Alloc::allocate(n);
	}

	constexpr void deallocate(T* p, size_type n) {
		if (p != _buffer)
			Alloc::deallocate(p, n);
	}

	constexpr array_reference buffer() noexcept {
		return _buffer;
	}

	constexpr const_array_reference buffer() const noexcept {
		return _buffer;
	}
private:
	array_type _buffer;
};

} // namespace nonsense
