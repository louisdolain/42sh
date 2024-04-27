##
## EPITECH PROJECT, 2024
## makefile
## File description:
## compiler
##

INCLUDE_FOLDER = ./include/
SRC_FOLDER = ./src/
LIB_BASIC_FOLDER = ./lib/BASICS/
TEST_FOLDER = ./tests/

MAIN = 	$(SRC_FOLDER)main.c

SRC =	$(SRC_FOLDER)tools.c \
		$(SRC_FOLDER)process.c \
		$(SRC_FOLDER)specific_functions.c \
		$(SRC_FOLDER)cd_function.c \
		$(SRC_FOLDER)ls_function.c \
		$(SRC_FOLDER)error_handle.c \
		$(SRC_FOLDER)env_management.c \
		$(SRC_FOLDER)error/cd_errors.c \
		$(SRC_FOLDER)bulletins/exit.c \
		$(SRC_FOLDER)error/execve_errors.c \
		$(SRC_FOLDER)parsing/remove_parentheses.c \
		$(SRC_FOLDER)parsing/ll_parser.c \
		$(SRC_FOLDER)backticks/backticks.c \
		$(SRC_FOLDER)error/parantheses_error.c

SRC_BASIC =	$(LIB_BASIC_FOLDER)my_printf.c \
		$(LIB_BASIC_FOLDER)my_printf2.c \
		$(LIB_BASIC_FOLDER)my_atoi.c \
		$(LIB_BASIC_FOLDER)my_itoa.c \
		$(LIB_BASIC_FOLDER)my_put_nbr.c \
		$(LIB_BASIC_FOLDER)my_putstr.c \
		$(LIB_BASIC_FOLDER)my_strcat.c \
		$(LIB_BASIC_FOLDER)my_strcmp.c \
		$(LIB_BASIC_FOLDER)my_strcpy.c \
		$(LIB_BASIC_FOLDER)my_strlen.c \
		$(LIB_BASIC_FOLDER)my_realloc.c \
		$(LIB_BASIC_FOLDER)my_str_to_all_array.c \
		$(LIB_BASIC_FOLDER)my_str_begin_with.c \
		$(LIB_BASIC_FOLDER)free_str_array.c \
		$(LIB_BASIC_FOLDER)concatmem.c \
		$(LIB_BASIC_FOLDER)my_strdup_array.c \
		$(LIB_BASIC_FOLDER)append.c \
		$(LIB_BASIC_FOLDER)cleanstr.c \
		$(LIB_BASIC_FOLDER)open_file.c

SRC_TEST = $(SRC_FOLDER)parsing/ll_parser.c \
		$(SRC_FOLDER)parsing/remove_parentheses.c \
		$(TEST_FOLDER)parser.c \

OBJ_MAIN = $(MAIN:.c=.o)
OBJ_SRC = $(SRC:.c=.o)
OBJ_BASIC =	$(SRC_BASIC:.c=.o)

CFLAGS = -Wall -Wextra
CPPFLAGS = -iquote $(INCLUDE_FOLDER)

LDFLAGS = -L ./
LIBFLAGS = -lmy

CRITFLAGS = -lcriterion
COVERFLAGS = --coverage

CC = gcc
AR = ar rc
RM = rm -f

TEMP_FILES = *.gcda* *.gcno* *vgcore*

NAME =	mysh
TEST_NAME = tests_run
LIBNAME = libmy.a

all: $(NAME)

build_lib: $(OBJ_BASIC)
	$(AR) $(LIBNAME) $(OBJ_BASIC)

$(NAME): $(OBJ_MAIN) $(OBJ_SRC) $(OBJ_BASIC)
	$(CC) -o $(NAME) $(OBJ_MAIN) $(OBJ_SRC) \
	$(OBJ_BASIC) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ_MAIN) $(OBJ_SRC) $(OBJ_BASIC)
	$(RM) $(TEMP_FILES)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)
	$(RM) $(LIBNAME)

tests_run: clean build_lib
	$(CC) -o $(TEST_NAME) $(SRC_TEST) $(LDFLAGS) $(LIBFLAGS) \
	$(CRITFLAGS) $(COVERFLAGS) $(CPPFLAGS)
	./$(TEST_NAME)

re: fclean all

.PHONY: all build_lib clean fclean tests_run re
