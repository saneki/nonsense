#include <gtest/gtest.h>
#include <nonsense/algorithm.hxx>

namespace ns = nonsense;

TEST(algorithm, array_equal) {
	{
		const std::uint8_t x[0x20] = { 0 };
		const std::uint8_t y[0x20] = { 0 };
		EXPECT_TRUE(ns::array_equal(x, y));
	} {
		const std::uint8_t x[0x20] = { 0 };
		const std::uint8_t y[0x20] = { 1 };
		EXPECT_FALSE(ns::array_equal(x, y));
	}
}
