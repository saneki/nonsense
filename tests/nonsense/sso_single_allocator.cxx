#include <gtest/gtest.h>
#include <nonsense/sso_single_allocator.hxx>
#include <nonsense/type_aliases.hxx>

namespace ns = nonsense;

using namespace ns::type_aliases::integer;

TEST(sso_single_allocator, AllocateBytes) {
	ns::sso_single_allocator<u8, 0x10> alloc;

	{
		const auto pointer = alloc.allocate(8);
		EXPECT_EQ(pointer, alloc.buffer());
		alloc.deallocate(pointer, 8);
	} {
		const auto pointer = alloc.allocate(0x10);
		EXPECT_EQ(pointer, alloc.buffer());
		alloc.deallocate(pointer, 0x10);
	} {
		const auto pointer = alloc.allocate(0x11);
		EXPECT_NE(pointer, alloc.buffer());
		alloc.deallocate(pointer, 0x11);
	}
}

TEST(sso_single_allocator, AllocateInts) {
	ns::sso_single_allocator<int, 8> alloc;

	{
		const auto pointer = alloc.allocate(0);
		EXPECT_EQ(pointer, alloc.buffer());
		alloc.deallocate(pointer, 0);
	} {
		const auto pointer = alloc.allocate(8);
		EXPECT_EQ(pointer, alloc.buffer());
		alloc.deallocate(pointer, 8);
	} {
		const auto pointer = alloc.allocate(100);
		EXPECT_NE(pointer, alloc.buffer());
		alloc.deallocate(pointer, 100);
	}
}
