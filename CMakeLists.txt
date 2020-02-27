cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
  message("TRAVIS_BUILD_NUMBER not defined. Setting its value to 1.")
  set(ENV{TRAVIS_BUILD_NUMBER} 1)
endif(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})

project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) 
conan_basic_setup(TARGETS)

add_executable(allocator allocator_usage.cpp )

set_target_properties(
	allocator
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

add_subdirectory(allocator_lib)
add_subdirectory(container_lib)

target_link_libraries(allocator PRIVATE
        allocator_lib
        container_lib
)


if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4 /MD
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

if (MSVC)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/)
endif()
install(TARGETS allocator RUNTIME DESTINATION bin)

if (MSVC)
    set(CPACK_GENERATOR NSIS)
else ()
    set(CPACK_GENERATOR DEB)
endif()

set(CPACK_PACKAGE_NAME "allocator")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_SOURCE_DIR}/README.md)

include(CPack)

enable_testing()
