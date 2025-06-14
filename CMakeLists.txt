cmake_minimum_required(VERSION 3.10)
project(SudokuSolver VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(imgui CONFIG REQUIRED)
find_package(json-c CONFIG REQUIRED)
find_package(Allegro CONFIG REQUIRED)

add_executable(SudokuSolver src/main.cpp)

target_link_libraries(SudokuSolver PRIVATE
    imgui::imgui
    json-c::json-c
    Allegro::allegro
    Allegro::allegro_image
    Allegro::allegro_font
    Allegro::allegro_ttf
    Allegro::allegro_primitives
)

target_sources(SudokuSolver PRIVATE
  src/ui.cpp
  src/ui.h

  src/utils/table.cpp
  src/utils/table.h

  src/utils/fs.cpp
  src/utils/fs.h

  src/utils/sudoku.h
)