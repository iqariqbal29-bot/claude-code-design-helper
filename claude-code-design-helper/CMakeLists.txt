cmake_minimum_required(VERSION 3.10)
project(claude-code-design-helper VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(claude-code-design-helper
    src/main.cpp
    src/design_analyzer.cpp
    src/code_generator.cpp
)

target_include_directories(claude-code-design-helper PRIVATE include)

enable_testing()
add_test(NAME test_analyzer COMMAND claude-code-design-helper --test)