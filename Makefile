##
## Makefile for  in /home/sabour_f/rendu/libIRC
##
## Made by Florian SABOURIN
## Login   <sabour_f@epitech.net>
##
## Started on  Tue Apr 14 15:47:15 2015 Florian SABOURIN
## Last update Mon Apr 20 10:40:31 2015 Florian SABOURIN
##

NAME		=	libIRC.a
CC		=	gcc
AR		=	ar rcs
override CFLAGS	+=	-W -Wall -Iinclude -D_GNU_SOURCE
export CFLAGS
LDFLAGS		=
RM		=	@rm -vf
MAKE		+=	--no-print-directory

SRC		=	src/buffer.c
SRC		+=	src/string.c
SRC		+=	src/mapstring.c
SRC		+=	src/user.c
SRC		+=	src/channel.c
SRC		+=	src/ircconnection.c
SRC		+=	src/irc_commands.c
SRC		+=	src/irc_eval_cmd.c
SRC		+=	src/irc_handle_cmd.c
SRC		+=	src/mode_utils.c
SRC		+=	src/irc_cmd_ping.c
SRC		+=	src/irc_cmd_join.c
SRC		+=	src/irc_cmd_part.c
SRC		+=	src/irc_cmd_quit.c
SRC		+=	src/irc_cmd_mode.c
SRC		+=	src/irc_cmd_nick.c
SRC		+=	src/irc_cmd_001.c
SRC		+=	src/irc_cmd_005.c
SRC		+=	src/irc_cmd_353.c
SRC		+=	src/irc_cmd_kick.c

OBJ		=	$(SRC:.c=.o)

%.o:	%.c
	$(CC) -c $(CFLAGS)            -o $@ $^

$(NAME):	$(OBJ)
	$(AR) $(NAME) $(OBJ)

all:	$(NAME)

tests:
	@$(MAKE) clean
	@$(MAKE) CFLAGS='-fprofile-arcs -ftest-coverage' do_tests

do_tests:	$(NAME)
	$(CC) -c $(CFLAGS)            -o src/tests.o src/tests.c
	$(CC) -fprofile-arcs -ftest-coverage -o tests $(OBJ) src/tests.o
	@echo "./tests && gcov */*.gcda && mkdir -p gcov && mv *.gcov gcov && rm src/*.gcno src/*.gcda" > do_tests.sh && chmod +x do_tests.sh

clean:
	$(RM) $(OBJ) src/tests.o

fclean: clean
	$(RM) $(NAME) a.out tests do_tests.sh $(SRC:.c=.gcda) src/tests.gcda $(SRC:.c=.gcno) src/tests.gcno

ex:
	@$(MAKE) CFLAGS=-ggdb3
	$(CC) main.c $(CFLAGS) -ggdb3 -L. -lIRC

re:	fclean all

.PHONY: all clean fclean re tests ex
