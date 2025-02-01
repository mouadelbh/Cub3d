NAME = cub3D

CC = cc

CFLAGS = #-Wall -Wextra -Werror -g3

LMX = -lmlx -lXext -lX11

LIBFTDIR = ./libft

RM = rm -rf

SRC = main.c map_utils.c movement.c 2Drendering.c 2Ddrawing.c 2Draycasting.c init.c \
	parse/parse1.c parse/parse2.c parse/parse3.c parse/parse4.c parse/parse5.c \
	math.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFTDIR) bonus
	$(CC) $(CFLAGS) $(OBJ) $(LIBFTDIR)/libft.a $(LMX) -lm -lz -o $(NAME)

%.o: %.c includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFTDIR)

fclean:
	$(RM) $(OBJ)
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: clean fclean all re
