#pragma once

#include <limits>
#include <stdexcept>

namespace nonsense {
	template <typename T, T Exempt>
	class NonValue {
	public:
		constexpr NonValue() = default;

		constexpr NonValue(T value)
			: m_value(value)
		{
		}

		/**
		 * Return the underlying value, regardless of whether or not it contains the exempt value.
		 **/
		constexpr T operator*() const noexcept {
			return m_value;
		}

		/**
		 * Return the underlying value or throw an exception if it contains the exempt value.
		 **/
		constexpr T get() const {
			if (hasValue())
				return m_value;
			else
				throw std::runtime_error("Does not contain non-exempt value.");
		}

		/**
		 * Whether or not the contained value is distinct from the exempt value.
		 **/
		constexpr bool hasValue() const noexcept {
			return m_value != Exempt;
		}
	private:
		T m_value = Exempt;
	};

	template <typename T>
	using NonZero = NonValue<T, 0>;

	template <typename T>
	using NonMax = NonValue<T, std::numeric_limits<T>::max()>;

	template <typename T>
	using NonMin = NonValue<T, std::numeric_limits<T>::min()>;

	template <typename T>
	using NonLowest = NonValue<T, std::numeric_limits<T>::lowest()>;
} // namespace nonsense
