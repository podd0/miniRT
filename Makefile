NAME = miniRT

SRCDIR = .
OBJDIR = .

SOURCES  := controller_keys_basic.c controller_keys_move.c controller_keys_transform.c controller_loop.c controller_movement.c frame2.c frame.c image_utils.c init.c interactions.c intersect.c intersect_cylinder.c intersect_sphere.c light_transform.c main.c math_utils.c parse.c parse_objects.c parse_utils1.c parse_utils2.c rotation.c rot.c shade.c trace1.c trace2.c trace.c transformations.c vec2.c vec.c virtual_resize.c vshape_0.c vshape_1.c vshape_2.c libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/get_next_line_bonus.c libft/get_next_line_utils_bonus.c libft/printf.c libft/printf_utils.c libft/safe_alloc.c libft/to_string.c libft/vector/vch_0.c libft/vector/vch_1.c libft/vector/vch_2.c libft/vector/vec_0.c libft/vector/vec_1.c libft/vector/vec_2.c libft/vector/vi_0.c libft/vector/vi_1.c libft/vector/vi_2.c libft/vector/vl_0.c libft/vector/vl_1.c libft/vector/vl_2.c libft/vector/vlu_0.c libft/vector/vlu_1.c libft/vector/vlu_2.c libft/vector/vstr_0.c libft/vector/vstr_1.c libft/vector/vstr_2.c 
INCLUDES := libft.h
OBJECTS = $(SOURCES:.c=.o)
MLX = minilibx-linux/libmlx.a

CC = gcc

CFLAGS = -Wall -Wextra -gdwarf-2 -I./libft -I. -I./minilibx-linux -Werror -O3 -flto 

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
