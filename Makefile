NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

LMX = -lmlx -lXext -lX11

LIBFTDIR = ./libft

HEADER = includes/cub3d.h

RM = rm -rf

SRC = main.c map_utils.c parse/parse1.c parse/parse2.c parse/parse3.c parse/parse4.c parse/parse5.c parse/free.c iniat.c \
		srcs/src1.c srcs/src2.c srcs/src3.c srcs/src4.c srcs/src5.c srcs/src6.c event_handle.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFTDIR) bonus
		$(CC) $(CFLAGS) $(OBJ) $(LIBFTDIR)/libft.a $(LMX) -lm -lz -o $(NAME)

%.o: %.c $(HEADER)
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
