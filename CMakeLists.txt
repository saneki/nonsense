cmake_minimum_required(VERSION 3.12)

project(NONSENSE)

# List header files in variable.
set(nonsense_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include/nonsense")
set(header_files
	"${nonsense_include_dir}/iota_array.hxx"
	"${nonsense_include_dir}/iota.hxx"
	"${nonsense_include_dir}/mem_array.hxx"
	"${nonsense_include_dir}/non_value.hxx"
	"${nonsense_include_dir}/sso_single_allocator.hxx"
	"${nonsense_include_dir}/type_aliases.hxx"
	"${nonsense_include_dir}/type_traits.hxx"
	"${nonsense_include_dir}/voided_cast.hxx")

# Add interface.
add_library(nonsense INTERFACE)
target_sources(nonsense INTERFACE "$<BUILD_INTERFACE:${header_files}>")
target_include_directories(nonsense INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_include_directories(nonsense SYSTEM INTERFACE
	$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

# Requires C++20.
set_property(TARGET nonsense PROPERTY CXX_STANDARD 20)
set_property(TARGET nonsense PROPERTY CXX_STANDARD_REQUIRED ON)

# Setup package configuration.
include(CMakePackageConfigHelpers)
set(CONFIG_PACKAGE_INSTALL_DIR "lib/cmake/nonsense")
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/nonsense-config-version.cmake"
	VERSION 0.0.1
	COMPATIBILITY SameMajorVersion
)

# Install target.
install(DIRECTORY include/nonsense DESTINATION include)

# Option to build unit tests.
option(NONSENSE_BUILD_TESTS "Build tests." ON)
if(NONSENSE_BUILD_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()
