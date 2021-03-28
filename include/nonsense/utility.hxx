#pragma once

#include <type_traits>
#include <utility>

namespace nonsense::utility {

namespace detail {
	template<auto Function, typename TInst, typename... TArgs>
	using MemberCallReturnType = std::enable_if_t<std::is_member_function_pointer_v<decltype(Function)>, std::invoke_result_t<decltype(Function), TInst*, TArgs...>>;
} // end namespace detail

// Utility function for runtime-conditional locking of member function calls.
// Expects TLock to be an RAII lock type which takes a TMutex reference in its constructor.
template<typename TLock,
		 auto Function,
		 typename TMutex,
		 typename TInst,
		 typename... TArgs>
constexpr detail::MemberCallReturnType<Function, TInst, TArgs...>
ConditionalLockMemberCall(bool conditional, TMutex &mutex, TInst *instance, TArgs&&... args) {
	if (conditional) {
		const TLock lock(mutex);
		return (instance->*Function)(std::forward<TArgs>(args)...);
	} else {
		return (instance->*Function)(std::forward<TArgs>(args)...);
	}
}

} // end namespace nonsense::utility
