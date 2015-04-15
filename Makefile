##
## Makefile for  in /home/sabour_f/rendu/libIRC
##
## Made by Florian SABOURIN
## Login   <sabour_f@epitech.net>
##
## Started on  Tue Apr 14 15:47:15 2015 Florian SABOURIN
## Last update Wed Apr 15 01:10:31 2015 Florian SABOURIN
##

NAME		=	libIRC.a
CC		=	gcc
AR		=	ar rcs
CFLAGS		=	-W -Wall -Iinclude -D_GNU_SOURCE
LDFLAGS		=
RM		=	@rm -vf
MAKE		+=	--no-print-directory

SRC		=	src/buffer.c
SRC		+=	src/string.c
SRC		+=	src/mapstring.c
SRC		+=	src/ircconnection.c

OBJ		=	$(addprefix out/, $(notdir $(SRC:.c=.o)))

out/%.o:	src/%.c
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
	$(RM) $(NAME)
	@$(MAKE) -C tests fclean

re:	fclean all

.PHONY: all clean fclean re tests
