cmake_minimum_required(VERSION 2.6)

#configuration
project("libIRC")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib/)

if (NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif (NOT DEFINED CMAKE_BUILD_TYPE)

add_definitions(-D_GNU_SOURCE)

#dependencies

#includes directories
include_directories(include/)

#sources files
set(SRCS
  src/buffer.c
  src/channel.c
  src/irc_cmd_001.c
  src/irc_cmd_005.c
  src/irc_cmd_353.c
  src/irc_cmd_join.c
  src/irc_cmd_kick.c
  src/irc_cmd_mode.c
  src/irc_cmd_nick.c
  src/irc_cmd_part.c
  src/irc_cmd_ping.c
  src/irc_cmd_quit.c
  src/irc_commands.c
  src/irc_eval_cmd.c
  src/irc_handle_cmd.c
  src/ircconnection.c
  src/mapstring.c
  src/mode_utils.c
  src/string.c
  src/user.c
)

#library
add_library(IRC STATIC ${SRCS})

#linking
target_link_libraries(IRC)

set_property(TARGET IRC PROPERTY C_STANDARD 99)
set_property(TARGET IRC PROPERTY C_STANDARD_REQUIRED ON)

