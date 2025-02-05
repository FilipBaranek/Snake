cmake_minimum_required(VERSION 3.22)

project(
  SnakeGame
  VERSION 0.0.1
  DESCRIPTION "Simple snake game"
  LANGUAGES C
)

add_custom_target(clean_all
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
  COMMENT "Cleaning build directory..."
)

add_subdirectory(src)
