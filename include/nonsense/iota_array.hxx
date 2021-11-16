#pragma once

#include <nonsense/iota.hxx>

namespace nonsense {

// Fixed-size array with contents initialized by std::iota.
template <typename T, std::size_t Size, T Value = T(0)>
class iota_array {
public:
	using size_type = std::size_t;
	using array_type = T[Size];
	using array_reference = std::add_lvalue_reference_t<T[Size]>;
	using const_array_reference = std::add_lvalue_reference_t<const T[Size]>;
	using reference = T&;
	using const_reference = const T&;
	static constexpr inline std::size_t size = Size;

	constexpr iota_array() noexcept(details::iota_noexcept_v<T>) {
		iota(_array);
	}

	constexpr reference operator[](std::size_t index) noexcept {
		return _array[index];
	}

	constexpr const_reference operator[](std::size_t index) const noexcept {
		return _array[index];
	}

	constexpr array_reference array() noexcept {
		return _array;
	}

	constexpr const_array_reference array() const noexcept {
		return _array;
	}

	constexpr size_type length() const noexcept {
		return Size;
	}
private:
	array_type _array;
};

} // namespace nonsense
