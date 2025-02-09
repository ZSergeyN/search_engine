cmake_minimum_required (VERSION 3.24)

project (Google_Tests VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME} ${TESTS_DIR}/InvertedIndex.cc ${TESTS_DIR}/SearchServer.cc
                ${SRC_DIR}/InvertedIndex.cpp ${SRC_DIR}/SearchServer.cpp)

target_link_libraries(${PROJECT_NAME} GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME})