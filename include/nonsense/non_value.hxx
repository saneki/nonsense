#pragma once

#include <limits>
#include <stdexcept>
#include <type_traits>

namespace nonsense {

template <typename T, T Exempt>
class non_value {
public:
	constexpr non_value() = default;

	constexpr non_value(T value)
		: _value(value) {}

	// Return the underlying value, regardless of whether or not it contains the exempt value.
	constexpr T operator*() const noexcept {
		return _value;
	}

	// Return the underlying value or throw an exception if it contains the exempt value.
	constexpr T get() const {
		if (has_value())
			return _value;
		else
			throw std::runtime_error("Does not contain non-exempt value.");
	}

	// Whether or not the contained value is distinct from the exempt value.
	constexpr bool has_value() const noexcept {
		return _value != Exempt;
	}
private:
	T _value = Exempt;
};

template <typename T>
using non_zero = non_value<T, 0>;

template <typename T>
using non_max = non_value<T, std::numeric_limits<T>::max()>;

template <typename T>
using non_min = non_value<T, std::numeric_limits<T>::min()>;

template <typename T>
using non_lowest = non_value<T, std::numeric_limits<T>::lowest()>;

template <typename T, std::enable_if_t<std::is_pointer_v<T>, bool> = true>
using non_null = non_value<T, nullptr>;

} // namespace nonsense
