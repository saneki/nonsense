#pragma once

#include <cstring>
#include <memory>
#include <type_traits>
#include <nonsense/type_traits.hxx>

namespace nonsense {

// NOTE: Is is_standard_layout the proper check for this? Idk but uvector uses it.
template <typename T, typename Alloc = std::allocator<T>,
		  std::enable_if_t<std::is_standard_layout_v<T>, bool> = true>
class mem_array : private Alloc {
public:
	using value_type = T;
	using allocator_type = Alloc;
	using size_type = std::size_t;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;
	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	constexpr explicit mem_array(const allocator_type &allocator = Alloc()) noexcept :
		Alloc(allocator),
		_begin(nullptr),
		_length(0) {}

	constexpr mem_array(std::size_t length, const allocator_type &allocator = Alloc()) :
		Alloc(allocator),
		_begin(allocate(length)),
		_length(length) {}

	constexpr mem_array(const mem_array<T, Alloc> &other) :
		Alloc(std::allocator_traits<Alloc>::select_on_container_copy_construction(static_cast<allocator_type>(other))),
		_begin(allocate(other.length())),
		_length(other.length())
	{
		std::copy(other.begin(), other.end(), _begin);
	}

	constexpr mem_array(const mem_array<T, Alloc> &other, const allocator_type &allocator) :
		Alloc(allocator),
		_begin(allocate(other.length())),
		_length(other.length())
	{
		std::copy(other.begin(), other.end(), _begin);
	}

	constexpr mem_array(mem_array<T, Alloc>&& other) :
		Alloc(std::move(other)),
		_begin(other._begin),
		_length(other._length)
	{
		other._begin = nullptr;
		other._length = 0;
	}

	constexpr mem_array(mem_array<T, Alloc>&& other, const allocator_type& allocator) :
		Alloc(allocator),
		_begin(other._begin),
		_length(other._length)
	{
		other._begin = nullptr;
		other._length = 0;
	}

	constexpr mem_array(std::initializer_list<T> initlist, const allocator_type& allocator = Alloc()) :
		Alloc(allocator),
		_begin(allocate(initlist.size())),
		_length(initlist.size())
	{
		pointer iter = _begin;
		for (auto i = initlist.begin(); i != initlist.end(); i++) {
			*iter++ = *i;
		}
	}

	constexpr ~mem_array() {
		deallocate();
	}

	constexpr reference operator[](std::size_t index) noexcept {
		return _begin[index];
	}

	constexpr const_reference operator[](std::size_t index) const noexcept {
		return _begin[index];
	}

	constexpr pointer allocate(std::size_t n) {
		return Alloc::allocate(n);
	}

	constexpr void deallocate() {
		deallocate(_begin, _length);
	}

	constexpr void deallocate(pointer p, std::size_t n) {
		if (p != nullptr)
			Alloc::deallocate(p, n);
	}

	constexpr pointer data() noexcept {
		return _begin;
	}

	constexpr const_pointer data() const noexcept {
		return _begin;
	}

	constexpr size_type length() const noexcept {
		return _length;
	}

	constexpr iterator begin() noexcept {
		return _begin;
	}

	constexpr const_iterator begin() const noexcept {
		return _begin;
	}

	constexpr const_iterator cbegin() const noexcept {
		return begin();
	}

	constexpr iterator end() noexcept {
		return _begin + _length;
	}

	constexpr const_iterator end() const noexcept {
		return _begin + _length;
	}

	constexpr const_iterator cend() const noexcept {
		return end();
	}

	constexpr reverse_iterator rbegin() noexcept {
		return std::reverse_iterator(end());
	}

	constexpr const_reverse_iterator rbegin() const noexcept {
		return std::reverse_iterator(end());
	}

	constexpr const_reverse_iterator crbegin() const noexcept {
		return rbegin();
	}

	constexpr reverse_iterator rend() noexcept {
		return std::reverse_iterator(begin());
	}

	constexpr const_reverse_iterator rend() const noexcept {
		return std::reverse_iterator(begin());
	}

	constexpr const_reverse_iterator crend() const noexcept {
		return rend();
	}

	/**
	 * Copy existing data into a created mem_array via std::copy, and return it.
	 **/
	constexpr static mem_array<std::remove_cv_t<T>, Alloc> copy_into(const_pointer p, size_type length) {
		mem_array<T, Alloc> array(length);
		std::copy(p, p + length, array.data());
		return array;
	}

	/**
	 * Copy existing data into a created mem_array via std::memcpy, and return it.
	 **/
	static mem_array<std::remove_cv_t<T>, Alloc> memcpy_into(const_pointer p, size_type length) {
		// NOTE: Should this be inline?
		mem_array<T, Alloc> array(length);
		std::memcpy(array.data(), p, sizeof(T) * length);
		return array;
	}
private:
	pointer _begin;
	size_type _length;
};

// Compare two mem_array instances for equality.
template <typename T, typename Alloc>
constexpr bool operator==(const mem_array<T, Alloc> &lhs, const mem_array<T, Alloc> &rhs) noexcept(is_nothrow_equality_v<T>) {
	return lhs.length() == rhs.length() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

// Compare two mem_array instances for inequality.
template <typename T, typename Alloc>
constexpr bool operator!=(const mem_array<T, Alloc> &lhs, const mem_array<T, Alloc> &rhs) noexcept(is_nothrow_equality_v<T>) {
	return !(lhs == rhs);
}

} // namespace nonsense
