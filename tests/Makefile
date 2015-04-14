##
## Makefile for  in /home/sabour_f/rendu/libIRC/tests
## 
## Made by Florian SABOURIN
## Login   <sabour_f@epitech.net>
## 
## Started on  Wed Apr 15 01:06:40 2015 Florian SABOURIN
## Last update Wed Apr 15 01:10:18 2015 Florian SABOURIN
##

NAME		=	tests
CC		=	gcc
CFLAGS		=	-W -Wall -Werror -I../include
LDFLAGS		=	-L.. -lIRC
RM		=	@rm -vf

SRC		=	tests.c

OBJ		=	$(SRC:.c=.o)

$(NAME):	$(OBJ) ../libIRC.a
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

all:	$(NAME)

../libIRC.a:
	@make -C ..

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re ../libIRC.a
