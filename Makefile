##
## Makefile for  in /home/ethiraric/github/libIRC
##
## Made by Ethiraric
## Login   <ethiraric@epitech.net>
##
## Started on  Sat Apr 23 18:21:54 2016 Ethiraric
## Last update Sat Apr 23 18:21:54 2016 Ethiraric
##

# Executables
CC		=	gcc
CXX		=	g++
AR		=	ar rcs
RM		=	@rm -vf
MAKE		+=	--no-print-directory

# Names
LIBNAME		=	libIRC.a

# Flags
CFLAGS		=	-W -Wall -Wshadow -fno-diagnostics-show-caret -D_GNU_SOURCE -std=gnu99  -Iinclude 
CXXFLAGS	=	-W -Wall -Wshadow -fno-diagnostics-show-caret -D_GNU_SOURCE -std=gnu99  -Iinclude 
LDFLAGS		=	 

# Files
CSRC		=	src/buffer.c
CSRC		+=	src/channel.c
CSRC		+=	src/irc_cmd_001.c
CSRC		+=	src/irc_cmd_005.c
CSRC		+=	src/irc_cmd_353.c
CSRC		+=	src/irc_cmd_join.c
CSRC		+=	src/irc_cmd_kick.c
CSRC		+=	src/irc_cmd_mode.c
CSRC		+=	src/irc_cmd_nick.c
CSRC		+=	src/irc_cmd_part.c
CSRC		+=	src/irc_cmd_ping.c
CSRC		+=	src/irc_cmd_quit.c
CSRC		+=	src/irc_commands.c
CSRC		+=	src/irc_eval_cmd.c
CSRC		+=	src/irc_handle_cmd.c
CSRC		+=	src/ircconnection.c
CSRC		+=	src/mapstring.c
CSRC		+=	src/mode_utils.c
CSRC		+=	src/string.c
CSRC		+=	src/user.c

# Objects
OBJ		=	$(CSRC:.c=.o) $(CXXSRC:.cpp=.o)

# Rules
$(LIBNAME): $(OBJ)
	$(AR) $(LIBNAME) $(filter-out main.o, $(OBJ))

all: $(LIBNAME)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(OBJ) $(LIBNAME)

re: fclean all

.PHONY: 	all clean fclean re

src/buffer.o: src/buffer.c include/buffer.h
	$(CC) $(CFLAGS) -c -o src/buffer.o src/buffer.c

src/channel.o: src/channel.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/channel.o src/channel.c

src/irc_cmd_001.o: src/irc_cmd_001.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_cmd_001.o src/irc_cmd_001.c

src/irc_cmd_005.o: src/irc_cmd_005.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_cmd_005.o src/irc_cmd_005.c

src/irc_cmd_353.o: src/irc_cmd_353.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_cmd_353.o src/irc_cmd_353.c

src/irc_cmd_join.o: src/irc_cmd_join.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_cmd_join.o src/irc_cmd_join.c

src/irc_cmd_kick.o: src/irc_cmd_kick.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_cmd_kick.o src/irc_cmd_kick.c

src/irc_cmd_mode.o: src/irc_cmd_mode.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_cmd_mode.o src/irc_cmd_mode.c

src/irc_cmd_nick.o: src/irc_cmd_nick.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_cmd_nick.o src/irc_cmd_nick.c

src/irc_cmd_part.o: src/irc_cmd_part.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_cmd_part.o src/irc_cmd_part.c

src/irc_cmd_ping.o: src/irc_cmd_ping.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_cmd_ping.o src/irc_cmd_ping.c

src/irc_cmd_quit.o: src/irc_cmd_quit.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_cmd_quit.o src/irc_cmd_quit.c

src/irc_commands.o: src/irc_commands.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_commands.o src/irc_commands.c

src/irc_eval_cmd.o: src/irc_eval_cmd.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_eval_cmd.o src/irc_eval_cmd.c

src/irc_handle_cmd.o: src/irc_handle_cmd.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/irc_handle_cmd.o src/irc_handle_cmd.c

src/ircconnection.o: src/ircconnection.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/ircconnection.o src/ircconnection.c

src/mapstring.o: src/mapstring.c include/t_mapstring.h include/t_string.h
	$(CC) $(CFLAGS) -c -o src/mapstring.o src/mapstring.c

src/mode_utils.o: src/mode_utils.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/mode_utils.o src/mode_utils.c

src/string.o: src/string.c include/t_string.h
	$(CC) $(CFLAGS) -c -o src/string.o src/string.c

src/user.o: src/user.c include/irc.h include/t_mapstring.h include/t_string.h include/buffer.h
	$(CC) $(CFLAGS) -c -o src/user.o src/user.c

