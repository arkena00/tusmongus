cmake_minimum_required(VERSION 3.24)
project(tusmongus)

# imgui
set(IMGUI_ROOT ${ARKENAMOD_ROOT}/third_party/imgui)
include(${ARKENAMOD_ROOT}/cmake/imgui.cmake)

file(GLOB_RECURSE AU_GEN_SOURCES
        ${ARKENAMOD_ROOT}/include/gen/au/PlayerControl.cpp
        ${ARKENAMOD_ROOT}/include/gen/au/Console.cpp
        ${ARKENAMOD_ROOT}/include/gen/au/PlayerPhysics.cpp
        )

add_library(tusmongus SHARED
        source/main.cpp
        source/tmg/ui.cpp
        source/tmg/tusmo.cpp
        ${AU_GEN_SOURCES}
        )

target_compile_features(tusmongus PUBLIC cxx_std_23)
target_link_directories(tusmongus PUBLIC ${ARKENAMOD_ROOT}/lib)
target_link_libraries(tusmongus PUBLIC arkena_mod lib_imgui)
target_include_directories(tusmongus PUBLIC
        include
        ${ARKENAMOD_ROOT}/include
        ${ARKENAMOD_ROOT}/include/gen
        )

target_compile_options(tusmongus PUBLIC /bigobj)
set_target_properties(tusmongus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    OUTPUT_NAME "tusmongus"
)

# copy files to the game directory
if (GAME_ROOT)
    add_custom_command(TARGET tusmongus POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:tusmongus> ${GAME_ROOT}/mods/
        COMMENT "Copying mod to ${GAME_ROOT}/mods/"
    )
endif()

add_executable(list_filter
        list_filter/main.cpp
        list_filter/main.cpp)
target_compile_features(list_filter PUBLIC cxx_std_23)