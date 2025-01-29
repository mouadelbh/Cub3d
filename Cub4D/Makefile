# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 10:29:21 by asebaai           #+#    #+#              #
#    Updated: 2025/01/28 15:58:49 by asebaai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

LMX = -lmlx -lXext -lX11

LIBFTDIR = ./libft

RM = rm -rf

SRC = main.c initialize.c

			
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFTDIR) bonus
		$(CC) $(CFLAGS) $(OBJ) $(LIBFTDIR)/libft.a $(LMX) -lm -lz -o $(NAME)

%.o: %.c
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