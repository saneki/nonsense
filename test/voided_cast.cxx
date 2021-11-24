#include <gtest/gtest.h>
#include <nonsense/voided_cast.hxx>

namespace ns = nonsense;

TEST(voided_cast, SignedPointerCasting) {
	{
		int value = 0;
		const auto signed_pointer = &value;
		const auto unsigned_pointer = reinterpret_cast<unsigned int *>(&value);
		const auto casted = ns::voided_cast<int *>(unsigned_pointer);
		EXPECT_EQ(signed_pointer, casted);
	} {
		int value = 0;
		const auto signed_pointer = const_cast<const int *>(&value);
		const auto unsigned_pointer = const_cast<const unsigned int *>(reinterpret_cast<unsigned int *>(&value));
		const auto casted = ns::voided_cast<const int *>(unsigned_pointer);
		EXPECT_EQ(signed_pointer, casted);
	}
}

