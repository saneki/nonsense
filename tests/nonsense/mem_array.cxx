#include <gtest/gtest.h>
#include <nonsense/iota_array.hxx>
#include <nonsense/mem_array.hxx>
#include <nonsense/type_aliases.hxx>

namespace ns = nonsense;

using namespace ns::type_aliases::integer;

TEST(mem_array, Constructor_Empty) {
	{
		ns::mem_array<u8> array;
		EXPECT_EQ(array.data(), nullptr);
		EXPECT_EQ(array.length(), 0);
	} {
		ns::mem_array<int> array;
		EXPECT_EQ(array.data(), nullptr);
		EXPECT_EQ(array.length(), 0);
	} {
		ns::mem_array<usize> array;
		EXPECT_EQ(array.data(), nullptr);
		EXPECT_EQ(array.length(), 0);
	}
}

TEST(mem_array, Constructor_Length) {
	{
		ns::mem_array<u8> array(0x100);
		EXPECT_EQ(array.length(), 0x100);
	} {
		ns::mem_array<int> array(123);
		EXPECT_EQ(array.length(), 123);
	} {
		ns::mem_array<usize> array(5);
		EXPECT_EQ(array.length(), 5);
	}
}

TEST(mem_array, Constructor_InitializerList) {
	ns::mem_array<u8> array({0x13, 0x37});
	EXPECT_EQ(array.length(), 2);
	EXPECT_EQ(array[0], 0x13);
	EXPECT_EQ(array[1], 0x37);
}

TEST(mem_array, CopyInto_Bytes) {
	const ns::iota_array<u8, 0x1000> buffer;
	const auto array = ns::mem_array<u8>::copy_into(buffer.array(), buffer.length());
	EXPECT_EQ(array.length(), buffer.length());
	for (usize i = 0; i < array.length(); i++)
		EXPECT_EQ(array[i], buffer[i]) << "Index: " << i;
}


TEST(mem_array, MemCpyInto_Bytes) {
	const ns::iota_array<u8, 0x1000> buffer;
	const auto array = ns::mem_array<u8>::memcpy_into(buffer.array(), buffer.length());
	EXPECT_EQ(array.length(), buffer.length());
	for (usize i = 0; i < array.length(); i++)
		EXPECT_EQ(array[i], buffer[i]) << "Index: " << i;
}
