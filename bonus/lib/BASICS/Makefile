##
## EPITECH PROJECT, 2023
## makefile
## File description:
## compiler
##

SRC =	my_printf.c \
		my_printf2.c \
		my_atoi.c \
		my_itoa.c \
		my_put_nbr.c \
		my_putstr.c\
		my_strcat.c \
		my_strcmp.c \
		my_strcat.c \
		my_strcmp.c \
		my_strcpy.c \
		my_strlen.c \
		my_realloc.c \
		my_str_to_all_array.c \
		my_str_begin_with.c \
		free_str_array.c \
		concatmem.c \
		my_strdup_array.c \
		append.c

OBJ =	$(SRC:.c=.o)

NAME =	../using/libbasics.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
