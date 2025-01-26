FLAGS = #-Wall -Wextra -Werror
LIBF_FILES	= libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c \
	libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c \
	libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \
	libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c \
	libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c \
	libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_lstadd_front.c \
	libft/ft_lstclear.c libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstmap.c libft/ft_lstnew.c libft/ft_lstsize.c \
	libft/ft_lstadd_back.c
LIBFT = libft/libft.a
NAME = cub3d
HEADERS = includes/cub3d.h
HEADER_DIR = includes/
SRC = main.c get_next_line.c get_next_line_utils.c map_utils.c movement.c 2Drendering.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT): $(LIBF_FILES)
	make -C libft

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -I$(HEADER_DIR) -Imlx_linux -O3 -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
