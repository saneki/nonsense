#pragma once

#include <cstdint>
#include <nonsense/type_traits.hxx>

namespace nonsense::type_aliases {

namespace floating {
	template <std::enable_if_t<is_bits_count_v<float, 32>, bool> = true>
	using f32 = float;

	// TODO: Check if double is 32 bits, and use that if float isn't.

	template <std::enable_if_t<is_bits_count_v<double, 64>, bool> = true>
	using f64 = double;

	// TODO: Check if float is 64 bits, and use that if double isn't.
} // namespace floating

namespace integer {
	using s8 = std::int8_t;
	using s16 = std::int16_t;
	using s32 = std::int32_t;
	using s64 = std::int64_t;
	using u8 = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;
	using usize = std::size_t;
} // namespace integer

namespace arithmetic {
	using namespace floating;
	using namespace integer;
} // namespace arithmetic

} // namespace nonsense::type_aliases
