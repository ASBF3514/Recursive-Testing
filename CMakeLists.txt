cmake_minimum_required(VERSION 3.14)
project(rekursif_tools VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Pustaka header-only
add_library(rekursif INTERFACE)
target_include_directories(rekursif INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
  set(REK_WARN /W4)
else()
  set(REK_WARN -Wall -Wextra -Wpedantic)
endif()

add_executable(rekursif_cli src/main.cpp)
set_target_properties(rekursif_cli PROPERTIES OUTPUT_NAME rekursif)
target_link_libraries(rekursif_cli PRIVATE rekursif)
target_compile_options(rekursif_cli PRIVATE ${REK_WARN})

enable_testing()
add_executable(test_rekursif tests/test_rekursif.cpp)
target_link_libraries(test_rekursif PRIVATE rekursif)
target_compile_options(test_rekursif PRIVATE ${REK_WARN})
add_test(NAME rekursif COMMAND test_rekursif)

install(TARGETS rekursif_cli RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
