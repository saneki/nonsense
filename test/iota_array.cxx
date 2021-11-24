#include <gtest/gtest.h>
#include <nonsense/iota_array.hxx>
#include <nonsense/type_aliases.hxx>

namespace ns = nonsense;

using namespace ns::type_aliases::integer;

TEST(iota_array, Constructor_Bytes) {
	const ns::iota_array<u8, 0x200> array;
	EXPECT_EQ(array.length(), 0x200);
	EXPECT_EQ(array[0], 0);
	EXPECT_EQ(array[1], 1);
	EXPECT_EQ(array[0xFF], 0xFF);
	EXPECT_EQ(array[0x100], 0);
	EXPECT_EQ(array[0x101], 1);
	EXPECT_EQ(array[0x1FF], 0xFF);
}

TEST(iota_array, Constructor_SizeType) {
	const ns::iota_array<usize, 0x1000> array;
	EXPECT_EQ(array.length(), 0x1000);
	EXPECT_EQ(array[0], 0);
	EXPECT_EQ(array[1], 1);
	EXPECT_EQ(array[2], 2);
	EXPECT_EQ(array[0xFFE], 0xFFE);
	EXPECT_EQ(array[0xFFF], 0xFFF);
}

TEST(iota_array, TypeTraits) {
	const ns::iota_array<u8, 10> array;
	EXPECT_EQ(decltype(array)::size, 10);
}
