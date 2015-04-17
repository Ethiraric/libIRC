##
## Makefile for  in /home/sabour_f/rendu/libIRC
##
## Made by Florian SABOURIN
## Login   <sabour_f@epitech.net>
##
## Started on  Tue Apr 14 15:47:15 2015 Florian SABOURIN
## Last update Fri Apr 17 12:18:45 2015 Florian SABOURIN
##

NAME		=	libIRC.a
CC		=	gcc
AR		=	ar rcs
override CFLAGS	+=	-W -Wall -Iinclude -D_GNU_SOURCE -ggdb3
export CFLAGS
LDFLAGS		=
RM		=	@rm -vf
MAKE		+=	--no-print-directory
OUT		=	out

SRC		=	src/buffer.c
SRC		+=	src/string.c
SRC		+=	src/mapstring.c
SRC		+=	src/user.c
SRC		+=	src/channel.c
SRC		+=	src/ircconnection.c
SRC		+=	src/irc_commands.c
SRC		+=	src/irc_eval_cmd.c
SRC		+=	src/irc_handle_cmd.c
SRC		+=	src/irc_cmd_join.c

OBJ		=	$(addprefix $(OUT)/, $(notdir $(SRC:.c=.o)))

$(OUT)/%.o:	src/%.c
	$(CC) -c $(CFLAGS)            -o $@ $^

$(NAME):	$(OBJ)
	$(AR) $(NAME) $(OBJ)

all:	$(NAME)

tests:
	@$(MAKE) -C tests

clean:
	$(RM) $(OBJ)
	@$(MAKE) -C tests clean

fclean: clean
	$(RM) $(NAME) a.out
	@$(MAKE) -C tests fclean

ex:	$(NAME)
	$(CC) main.c $(CFLAGS) -L. -lIRC

re:	fclean all

.PHONY: all clean fclean re tests ex
