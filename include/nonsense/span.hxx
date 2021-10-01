#pragma once

#include <algorithm>
#include <cstdint>
#include <string_view>

namespace nonsense {
	class Span {
	public:
		constexpr Span() = default;

		constexpr Span(std::uint8_t *buffer, std::size_t length) noexcept
			: m_buffer(buffer), m_length(length)
		{
		}

		constexpr explicit Span(std::string_view view) noexcept
			: m_buffer(const_cast<std::uint8_t *>((const std::uint8_t *)(view.data()))),
			  m_length(view.length())
		{
		}

		constexpr std::uint8_t operator[](std::size_t pos) const noexcept {
			return m_buffer[pos];
		}

		constexpr Span absDelta(const Span &other) const noexcept {
			if (m_buffer <= other.m_buffer)
				return other.delta(*this);
			else
				return delta(other);
		}

		constexpr std::uint8_t* buffer() const noexcept {
			return m_buffer;
		}

		/**
		 * Consume entire Span.
		 **/
		constexpr Span consume() noexcept {
			const auto result = Span(m_buffer, m_length);
			m_buffer = end();
			m_length = 0;
			return result;
		}

		constexpr Span consume(std::size_t amount) noexcept {
			const auto count = std::min(amount, m_length);
			const auto result = slice(0, count);
			m_buffer += count;
			m_length -= count;
			return result;
		}

		constexpr Span consumeDelta(const Span &other) noexcept {
			return consumeDelta(other, 0);
		}

		constexpr Span consumeDelta(const Span &other, std::size_t extra) noexcept {
			// NOTE: Assumes "other" is always after "this".
			// NOTE: Assumes delta + extra does not overflow.
			const auto delta = std::size_t(other.m_buffer - m_buffer);
			return consume(delta + extra);
		}

		/**
		 * Return an empty slice at head.
		 * \note Effectively the same as consume(0), but more efficient.
		 **/
		constexpr Span consumeNone() const noexcept {
			return Span(m_buffer, 0);
		}

		constexpr Span delta(const Span &origin) const noexcept {
			return Span(origin.m_buffer, std::size_t(m_buffer - origin.m_buffer));
		}

		constexpr std::ptrdiff_t diff(const Span &other) const noexcept {
			return m_buffer - other.m_buffer;
		}

		constexpr bool empty() const noexcept {
			return m_length == 0;
		}

		constexpr std::uint8_t* end() const noexcept {
			return m_buffer + m_length;
		}

		constexpr bool endsWith(std::uint8_t c) const noexcept {
			return m_length != 0 && m_buffer[m_length - 1] == c;
		}

		constexpr std::size_t length() const noexcept {
			return m_length;
		}

		constexpr Span slice(std::size_t index, std::size_t length) const noexcept {
			// NOTE: Assumes buffer + index will not overflow. In fact, the entire class assumes this.
			const auto begin = (m_buffer + index) <= end() ? (m_buffer + index) : end();
			const auto size = std::min(static_cast<std::size_t>(end() - begin), length);
			return Span(begin, size);
		}

		constexpr Span slice(std::size_t index) const noexcept {
			if (index <= m_length)
				return slice(index, m_length - index);
			else
				return Span(end(), 0);
		}

		constexpr bool startsWith(const std::string_view &view) const noexcept {
			if (m_length < view.length())
				return false;

			for (std::size_t i = 0; i < view.length(); i++) {
				if (m_buffer[i] != static_cast<std::uint8_t>(view[i]))
					return false;
			}

			return true;
		}

		constexpr bool startsWith(const std::uint8_t *zstring) const noexcept {
			for (std::size_t i = 0; i < m_length; i++) {
				if (zstring[i] == 0)
					return true;
				else if (m_buffer[i] != zstring[i])
					return false;
			}

			// If Span matches string until end of Span, check for null terminator (exact match).
			return zstring[m_length] == 0;
		}

		/**
		 * Return an empty tail slice.
		 **/
		constexpr Span tail() const noexcept {
			return Span(end(), 0);
		}

		constexpr std::string_view view() const noexcept {
			return std::string_view(
				const_cast<const char *>((char *)(m_buffer)),
				m_length);
		}
	private:
		std::uint8_t *m_buffer = nullptr;
		std::size_t m_length = 0;
	};
} // namespace nonsense
