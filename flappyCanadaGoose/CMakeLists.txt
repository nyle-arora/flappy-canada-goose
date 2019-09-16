cmake_minimum_required(VERSION 3.3)
project(final-project CXX)
include(.eecs211/cmake/CMakeLists.txt)

add_program(main
        src/main.cpp
        src/model.cpp
        src/ui.cpp
        src/goose.cpp)

target_link_libraries(main ge211)

add_test_program(model_test
    test/model_test.cpp
    src/model.cpp
    src/goose.cpp
    ${MODEL_SRC})
target_link_libraries(model_test ge211)
