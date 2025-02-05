#client
add_executable(client main.c)

add_subdirectory(network)
add_subdirectory(menu)
add_subdirectory(game)

target_sources(snake PRIVATE client.c)
target_sources(client PRIVATE
  client.c
  main.c
)

target_link_libraries(snake PRIVATE ncurses)
target_link_libraries(client PRIVATE ncurses)

set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
