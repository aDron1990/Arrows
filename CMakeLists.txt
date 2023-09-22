cmake_minimum_required(VERSION 3.5)

project(Arrows VERSION 0.1.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS system)
add_subdirectory(kwee)

include_directories(${Boost_INCLUDE_DIRS})
file(GLOB_RECURSE sources "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${sources})


add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_CURRENT_SOURCE_DIR}/res" "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/res")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res)


add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_CURRENT_SOURCE_DIR}/saves" "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/saves")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/saves ${CMAKE_BINARY_DIR}/saves)


target_link_libraries(${PROJECT_NAME} kwee)
