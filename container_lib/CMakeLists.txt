cmake_minimum_required(VERSION 3.2)

add_library(container_lib SimpleList.cpp)
target_include_directories(container_lib PUBLIC ./include)

set_target_properties(
        container_lib
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


if (MSVC)
    target_compile_options(container_lib PRIVATE
        /W4 /MD
    )
else ()
    target_compile_options(container_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
