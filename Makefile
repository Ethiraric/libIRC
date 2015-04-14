##
## Makefile for  in /home/sabour_f/rendu/libIRC
##
## Made by Florian SABOURIN
## Login   <sabour_f@epitech.net>
##
## Started on  Tue Apr 14 15:47:15 2015 Florian SABOURIN
## Last update Tue Apr 14 16:10:14 2015 Florian SABOURIN
##

NAME		=	libIRC.a
CC		=	gcc
AR		=	ar rcs
CFLAGS		=	-W -Wall -Iinclude
LDFLAGS		=
RM		=	@rm -vf

SRC		=	src/buffer.c
SRC		+=	src/string.c

OBJ		=	$(addprefix out/, $(notdir $(SRC:.c=.o)))

out/%.o:	src/%.c
	$(CC) -c $(CFLAGS)            -o $@ $^

$(NAME):	$(OBJ)
	$(AR) $(NAME) $(OBJ)

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
