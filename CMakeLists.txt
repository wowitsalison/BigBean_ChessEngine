cmake_minimum_required(VERSION 3.10)
project(BigBean)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add the source files
set(SOURCES
    src/main.cpp
    src/board.cpp
    src/movegen.cpp
    src/utils.cpp
    src/gameState.cpp
    src/evaluation.cpp
    src/search.cpp
)

# Add the test files
set(TEST_SOURCES
    tests/pawn_test.cpp
    tests/slidingPiece_test.cpp
    tests/specialPiece_test.cpp
    tests/gameState_test.cpp
    tests/evaluation_test.cpp
    tests/minimax_test.cpp
    src/board.cpp
    src/movegen.cpp
)

# Add the executable for the main program
add_executable(BigBean ${SOURCES})

# Add the executable for the tests
add_executable(BigBeanTests ${TEST_SOURCES})