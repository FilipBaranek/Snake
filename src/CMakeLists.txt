#snake
add_executable(snake main.c)
set_target_properties(snake PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(client)
add_subdirectory(server)

