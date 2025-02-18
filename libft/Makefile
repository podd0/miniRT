NAME = libft.a

SRCDIR = .
OBJDIR = .

SOURCES  := $(wildcard *.c) $(wildcard vector/*.c) 

INCLUDES := libft.h printf_utils.h
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I. -O3

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) -r $@ $?

%.o: %.c
	$(CC) -c $(CFLAGS) $? -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# test: $(NAME) test.c
# 	$(CC) test.c $(NAME) $(CFLAGS) -o test

show:
	echo $(SOURCES)

.PHONY: all bonus clean fclean re