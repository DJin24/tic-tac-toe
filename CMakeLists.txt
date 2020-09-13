cmake_minimum_required(VERSION 3.9)
project(tic_tac_toe)
include(.cs211/cmake/CMakeLists.txt)

# Defines a variable to stand for the .cxx files that implement
# the model.
set(MODEL_SRC
        src/player.cxx
        src/board.cxx
        src/model.cxx
        src/move.cxx)

# Adds a program named `Tic Tac Toe` built from the listed source
# files and the common model files.
add_program(Tic-tac-toe
        src/tic_tac_toe.cxx
        src/controller.cxx
        src/view.cxx
        ${MODEL_SRC})
target_link_libraries(Tic-tac-toe ge211)

# Adds a test program named `model_test` built from the listed
# source file and the common model files.
add_test_program(model_test
        test/model_test.cxx
        ${MODEL_SRC})
target_link_libraries(model_test ge211)

# Adds a test program named `helper_test` for testing the helper
# classes.
add_test_program(helper_test
        test/player_test.cxx
        test/board_test.cxx
        ${MODEL_SRC})
target_link_libraries(helper_test ge211)


# vim: ft=cmake
