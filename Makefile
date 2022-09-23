CC = clang

NAME = so_long

SRCS =	gnl/get_next_line_bonus.c	gnl/get_next_line_utils_bonus.c	ft_check_map.c\
		ft_itoa.c					init_images.c					main.c\
		move_and_drow.c				utils.c

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

HEADER = header.h

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(OBJS) -lmlx -lXext -lX11 -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(NAME)