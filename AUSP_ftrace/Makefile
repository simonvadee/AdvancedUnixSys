##
## main.c for strace in /home/vadee_s/rendu/AUSP_strace
## 
## Made by simon vadée
## Login   <vadee_s@epitech.net>
## 
## Started on  Sun May 17 19:10:55 2015 simon vadée
## Last update Sun May 17 19:10:56 2015 simon vadée
##

RM		=	rm -f

CC		=	gcc

CFLAGS		+=	-I./includes -Wall -Wextra -Werror -D _GNU_SOURCE

COLOR_OFF	=	\033[0m
COLOR_ON	=	\033[32;01m

PROG_STRACE	=	$(COLOR_ON) [/_\ Binary Compiled /_\] $(COLOR_OFF)

SRC_PATH	=	./sources/

SRC		=	$(wildcard $(SRC_PATH)*.c)

OBJ		=	$(SRC:.c=.o)

NAME		=	ftrace

$(NAME)		:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)
			@echo -e "$(PROG_STRACE)"

all		:	$(NAME)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		: 	fclean all

.PHONY		:	all clean fclean re
