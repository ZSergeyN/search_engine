cmake_minimum_required (VERSION 3.24)

project (search_engine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(src)

add_subdirectory(tests)
