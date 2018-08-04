# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 20:56:57 by apyltsov          #+#    #+#              #
#    Updated: 2017/11/07 20:57:32 by apyltsov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS =  -Wall -Wextra -Werror
GFX = -lmlx -framework OpenGL -framework AppKit
NAME = fdf
SRC = main_fdf.c\
	draw_functions.c\
	get_next_line.c\
	file_funct.c
BINS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(BINS)
	cd libft && make && cd ..
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) libft/libft.a $(GFX)

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	cd libft && make clean && cd ..
	rm -f $(BINS)

fclean: clean
	cd libft && make fclean && cd ..
	rm -f $(NAME)

re: fclean all