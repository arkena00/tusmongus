cmake_minimum_required(VERSION 3.24)
project(amodus)

set(CMAKE_CXX_STANDARD 20)

if (NOT ARKMONGUS_ROOT)
    set(ARKMONGUS_ROOT ${PROJECT_SOURCE_DIR})
endif()

add_library(amodus SHARED source/main.cpp)

target_link_directories(amodus PUBLIC shared)
target_link_libraries(amodus PUBLIC arkena_mod)
target_include_directories(amodus PUBLIC include shared/include)

set_target_properties(amodus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ARKMONGUS_ROOT}/bin/mods"
    OUTPUT_NAME "amodus"
)