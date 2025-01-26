cmake_minimum_required (VERSION 3.17)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} search_engine.cpp ConverterJSON.cpp ${INCLUDE_DIR}/ConverterJSON.h)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})