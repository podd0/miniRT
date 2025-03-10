NAME = rt

SRCDIR = .
OBJDIR = .

SOURCES  := $(wildcard *.c) $(wildcard libft/*.c) $(wildcard libft/vector/*.c)
INCLUDES := libft.h
OBJECTS = $(SOURCES:.c=.o)
MLX = minilibx-linux/libmlx.a

CC = gcc

CFLAGS = -O3 -flto -Wall -Wextra -g -I./libft -I. -I./minilibx-linux -Werror #-fsanitize=address -fsanitize=undefined 

all: $(NAME)

$(MLX):
	make -C minilibx-linux

$(NAME): $(OBJECTS) $(MLX)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) -lm -Lminilibx-linux -lmlx -lXext -lX11 

%.o: %.c
	$(CC) -c $(CFLAGS) $? -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all bonus clean fclean re
