cmake_minimum_required(VERSION 3.12)

project(nonsense_tests)

set(source_files
	algorithm.cxx
	iota_array.cxx
	mem_array.cxx
	non_value.cxx
	sso_single_allocator.cxx
	type_traits.cxx
	voided_cast.cxx)
add_executable(nonsense_tests ${source_files})
target_compile_features(nonsense_tests PUBLIC cxx_std_20)
target_include_directories(nonsense_tests PRIVATE nonsense)
target_link_libraries(nonsense_tests
	nonsense gtest gtest_main)

add_test(NAME nonsense_tests COMMAND nonsense_tests)
