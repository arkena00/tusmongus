cmake_minimum_required(VERSION 3.24)
project(amodus)

set(CMAKE_CXX_STANDARD 20)

if (NOT ARKENAMODS_ROOT)
    set(ARKENAMODS_ROOT ${PROJECT_SOURCE_DIR}/bin/mods)
endif()

add_library(amodus SHARED source/main.cpp)

target_link_directories(amodus PUBLIC shared)
target_link_libraries(amodus PUBLIC ${ARKENAMODS_LIB})
target_include_directories(amodus PUBLIC include shared/include)

set_target_properties(amodus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ARKENAMODS_ROOT}/"
    OUTPUT_NAME "amodus"
)