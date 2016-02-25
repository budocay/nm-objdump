##
## Makefile for makefile in 
## 
## Made by lina_a
## Login   <lina_a@epitech.net>
## 
## Started on  Mon Feb 15 10:26:12 2016 lina_a
## Last update Mon Feb 15 10:26:12 2016 lina_a
##

CC	= gcc

RM	= rm -f

CFLAGS	+= -Wall -Wextra -I./include

NAME_OBJDUMP	= my_objdump

NAME_NM		= my_nm

SRCS_OBJDUMP	= ./src_objdump/main.c \
		  ./src_objdump/check_map_data.c \
		  ./src_objdump/Objdump_elf32.c \
		  ./src_objdump/verify_header.c \
		  ./src_objdump/FlagsObjdump.c \
		  ./src_objdump/Print_Flags_Type.c \
          	  ./src_objdump/read_files.c


SRCS_NM		= ./src_nm/main.c \
           	  ./src_objdump/verify_header.c \
           	  ./src_objdump/read_files.c \
		  ./src_nm/check_set_tab.c

OBJS_OBJDUMP	= $(SRCS_OBJDUMP:.c=.o)

OBJS_NM		= $(SRCS_NM:.c=.o)

all:	$(NAME_OBJDUMP) $(NAME_NM)

$(NAME_OBJDUMP):	$(OBJS_OBJDUMP)
		$(CC) -o $(NAME_OBJDUMP) $(OBJS_OBJDUMP)

$(NAME_NM):	$(OBJS_NM)
		$(CC) -o $(NAME_NM) $(OBJS_NM)

clean:
	$(RM) $(OBJS_OBJDUMP)
	$(RM) $(OBJS_NM)

fclean: clean
	$(RM) $(NAME_OBJDUMP)
	$(RM) $(NAME_NM)

re: fclean all

.PHONY: re fclean clean all
