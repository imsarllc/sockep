cmake_minimum_required(VERSION 3.13)

add_custom_target(examples)

function(add_example)
  set(TGT_NAME ${ARGV0})
  set(SRC_FILE ${ARGV1})

  add_executable(${TGT_NAME} EXCLUDE_FROM_ALL ${SRC_FILE})

  set_target_properties(${TGT_NAME} PROPERTIES
    OUTPUT_NAME ${TGT_NAME}
  )

  target_link_libraries(${TGT_NAME} PRIVATE ${SOCKEP})

  add_dependencies(examples ${TGT_NAME})
endfunction()


add_example(unixdgram_server unixdgram_server.cpp)
add_example(unixdgram_client unixdgram_client.cpp)
add_example(unixstream_server unixstream_server.cpp)
add_example(unixstream_client unixstream_client.cpp)
add_example(tcp_server tcp_server.cpp)
add_example(tcp_client tcp_client.cpp)
add_example(udp_server udp_server.cpp)
add_example(udp_client udp_client.cpp)
