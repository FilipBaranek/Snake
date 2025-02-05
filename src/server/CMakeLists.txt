#server
add_executable(server main.c)

add_subdirectory(network)
add_subdirectory(game)

target_sources(snake PRIVATE server.c)
target_sources(server PRIVATE
  server.c
  main.c
)

set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
