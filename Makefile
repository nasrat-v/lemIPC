##
## Makefile for lemipc in /home/nasrat_v/Dev/tek2/C/Concurrence/PSU_2016_lemipc/PSU_2016_lemipc/bonus
## 
## Made by Valentin Nasraty
## Login   <valentin.nasraty@epitech.eu>
## 
## Started on  Thu Oct 26 19:02:13 2017 Valentin Nasraty
## Last update Thu Oct 26 19:07:38 2017 Valentin Nasraty
##

CC	=	gcc -g3

RM	=	rm -rf

NAME	=	lemipc

SCRS	= aff.c \
          create.c \
          dead.c \
          end_game.c \
          main.c \
          move.c \
          semcontrol.c \
	  ia_core.c \
	  ia_attack.c \
	  ia_defense.c \
	  add_player.c


OBJS	=	$(SCRS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror

NCURSES	= 	-lncurses -ltinfo

MATH	=	-lm

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(NCURSES) $(MATH)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
