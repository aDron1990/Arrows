cmake_minimum_required(VERSION 3.20)

project(Arrows)

set(CMAKE_TOOLCHAIN_FILE "build/conan_toolchain.cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

file(GLOB_RECURSE sources "src/*.cpp" "src/*.h" "include/*.h" "3th_party/imgui/*.cpp")

add_subdirectory("3th_party/glm")
add_subdirectory("3th_party/stb_image")

add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE "include/" "3th_party/imgui/" ${Boost_INCLUDE_DIRS} ${glad_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw stb_image glm glad::glad)

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