cmake_minimum_required(VERSION 3.0.0)
project(db_updated VERSION 0.1.0)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
add_executable(db_updated main.cpp
    condition_parser.cpp
    condition_parser_test.cpp
    database.cpp
    date.cpp
    node.cpp
    token.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})