cmake_minimum_required(VERSION 3.2)

add_library(allocator_lib logging_allocator.cpp simple_allocator.cpp)
target_include_directories(allocator_lib PUBLIC ./include)

set_target_properties(
	allocator_lib
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


if (MSVC)
    target_compile_options(allocator_lib PRIVATE
        /W4 /MD
    )
else ()
    target_compile_options(allocator_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
