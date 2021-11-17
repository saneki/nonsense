#pragma once

#include <limits>
#include <stdexcept>
#include <type_traits>

namespace nonsense {

template <typename T, T Exempt>
class non_value {
public:
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	constexpr non_value() = default;

	constexpr non_value(T value)
		: _value(value) {}

	// Return the underlying value or throw an exception if it contains the exempt value.
	constexpr value_type get() const {
		if (has_value())
			return _value;
		else
			throw std::runtime_error("Does not contain non-exempt value.");
	}

	// Whether or not the contained value is distinct from the exempt value.
	constexpr bool has_value() const noexcept {
		return _value != Exempt;
	}

	// Return a reference to the underlying value.
	constexpr reference raw() noexcept {
		return _value;
	}

	// Return a const reference to the underlying value.
	constexpr const_reference raw() const noexcept {
		return _value;
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
