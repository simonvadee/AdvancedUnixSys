##
## Makefile for nmobjdump in /home/vadee_s/rendu/AUSP_nmobjdump
## 
## Made by simon vadée
## Login   <vadee_s@epitech.net>
## 
## Started on  Sun Apr 19 16:10:38 2015 simon vadée
## Last update Sun Apr 19 16:10:39 2015 simon vadée
##

NM		=	nm

OBJDUMP		=	objdump

MY_NM		=	my_nm

MY_OBJDUMP	=	my_objdump

NM_DIR		=	nm_dir

UTILS_DIR	=	utils

OBJDUMP_DIR	=	objdump_dir

SCRS_NM		=	$(NM_DIR)/main.c \
			$(UTILS_DIR)/utils.c \
			$(UTILS_DIR)/string_operations.c \
			$(NM_DIR)/manage_symbols.c \
			$(NM_DIR)/process_nm.c

SCRS_OBJDUMP	=	$(OBJDUMP_DIR)/main.c \
			$(UTILS_DIR)/utils.c \
			$(OBJDUMP_DIR)/manage_flags.c \
			$(OBJDUMP_DIR)/display.c \
			$(OBJDUMP_DIR)/process_objdump.c

NM_OBJS		=	$(SCRS_NM:.c=.o)

OBJDUMP_OBJS	=	$(SCRS_OBJDUMP:.c=.o)

CC		=	gcc

RM		=	rm -rf

CFLAGS		=	-Wall -Wextra -Werror -I./includes

$(NM)		:	my_nm

$(OBJDUMP)	:	my_objdump

$(MY_NM)	:	$(NM_OBJS)
			$(CC) -o $(MY_NM) $(NM_OBJS)

$(MY_OBJDUMP)	:	$(OBJDUMP_OBJS)
			$(CC) -o $(MY_OBJDUMP) $(OBJDUMP_OBJS)

all		:	$(NM) $(OBJDUMP)

clean		:
			$(RM) $(NM_OBJS) $(OBJDUMP_OBJS)

fclean		:	clean
			$(RM) $(MY_NM) $(MY_OBJDUMP)

re		:	fclean all

.PHONY		:	all clean fclean re
