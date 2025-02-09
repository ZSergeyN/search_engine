cmake_minimum_required (VERSION 3.24)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} search_engine.cpp
        ConverterJSON.cpp ${INCLUDE_DIR}/ConverterJSON.h
        InvertedIndex.cpp ${INCLUDE_DIR}/InvertedIndex.h
        SearchServer.cpp ${INCLUDE_DIR}/SearchServer.h)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/config.json
        ${CMAKE_CURRENT_BINARY_DIR}/config.json)
add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/requests.json
        ${CMAKE_CURRENT_BINARY_DIR}/requests.json)
add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/answers.json
        ${CMAKE_CURRENT_BINARY_DIR}/answers.json)
add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources)
