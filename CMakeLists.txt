cmake_minimum_required(VERSION 3.23.0 FATAL_ERROR)

project(Pools VERSION 1.0)

add_compile_options(
  -fsanitize=address
  -g
)

add_link_options(
  -fsanitize=address
  -g
)

add_library(pool STATIC src/pool.cpp src/disjoint_set_union.cpp)
target_include_directories(pool PUBLIC include/)

add_executable(test src/main.cpp)
target_link_libraries(test PUBLIC pool)