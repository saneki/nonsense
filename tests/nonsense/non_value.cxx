#include <gtest/gtest.h>
#include <nonsense/non_value.hxx>
#include <nonsense/type_aliases.hxx>

namespace ns = nonsense;

using namespace ns::type_aliases::integer;

TEST(non_zero, NonZero) {
	{
		// Implicit zero-value.
		const ns::non_zero<u8> value;
		EXPECT_EQ(*value, 0);
		EXPECT_FALSE(value.has_value());
	} {
		// Explicit zero-value.
		const ns::non_zero<u8> value(0);
		EXPECT_EQ(*value, 0);
		EXPECT_FALSE(value.has_value());
	} {
		// Non-zero value.
		const ns::non_zero<u8> value(1);
		EXPECT_EQ(*value, 1);
		EXPECT_TRUE(value.has_value());
	}
}

TEST(non_value, NonNull) {
	{
		// Implicit nullptr.
		const ns::non_null<const void *> value;
		EXPECT_EQ(*value, nullptr);
		EXPECT_FALSE(value.has_value());
	} {
		// Explicit nullptr.
		const ns::non_null<const void *> value(nullptr);
		EXPECT_EQ(*value, nullptr);
		EXPECT_FALSE(value.has_value());
	} {
		// Non-nullptr value.
		const int dummy = 0;
		const ns::non_null<const void *> value(&dummy);
		EXPECT_EQ(*value, &dummy);
		EXPECT_TRUE(value.has_value());
	}
}
