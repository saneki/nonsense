#include <cstdio>
#include <iostream>
#include <shared_mutex>
#include <string>
#include <utility>

#include "include/nonsense/utility.hxx"

// RAII lock types.
using ReadLock = std::shared_lock<std::shared_mutex>;
using WriteLock = std::unique_lock<std::shared_mutex>;

class Dummy {
	// Wrapper function for runtime-conditional locking of member function calls for this instance.
	template<typename TLock, auto Function, typename... TArgs>
	constexpr decltype(auto) LockCall(TArgs&&... args) {
		return ::nonsense::utility::ConditionalLockMemberCall<TLock, Function>(_locking, _mutex, this, std::forward<TArgs>(args)...);
	}

public:
	Dummy() : _locking(false) {
	}

	explicit Dummy(bool locking) : _locking(locking) {
	}

	void HelloWorld() {
		LockCall<ReadLock, &Dummy::HelloWorld_NoLock>();
	}

	void HelloWorld_NoLock() {
		std::cout << "Hello World!\n";
	}

	std::string HelloName(const std::string &name) {
		return LockCall<ReadLock, &Dummy::HelloName_NoLock>(name);
	}

	std::string HelloName_NoLock(const std::string &name) {
		char buffer[1024];
		std::snprintf(buffer, sizeof(buffer), "Hello %s!", name.c_str());
		return std::string(buffer);
	}

private:
	bool _locking;
	std::shared_mutex _mutex;
};

int main() {
	Dummy dummy(true);
	dummy.HelloWorld();
	std::cout << dummy.HelloName("Squeakums") << "\n";
	return 0;
}
