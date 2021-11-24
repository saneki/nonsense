#include <gtest/gtest.h>
#include <nonsense/type_traits.hxx>

namespace ns = nonsense;

TEST(type_traits, ApplyConstVolatile) {
	static_assert(std::is_same_v<
		ns::apply_cv_t<char, const volatile int>,
		const volatile char
	>);

	static_assert(std::is_same_v<
		ns::apply_cv_t<const int, volatile char>,
		const volatile int
	>);
}

TEST(type_traits, ApplyConstVolatileHelper_Char) {
	static_assert(std::is_same_v<
		ns::detail::apply_cv_helper<false, false, char>::type,
		char
	>);

	static_assert(std::is_same_v<
		ns::detail::apply_cv_helper<false, true, char>::type,
		volatile char
	>);

	static_assert(std::is_same_v<
		ns::detail::apply_cv_helper<true, false, char>::type,
		const char
	>);

	static_assert(std::is_same_v<
		ns::detail::apply_cv_helper<true, true, char>::type,
		const volatile char
	>);
}
