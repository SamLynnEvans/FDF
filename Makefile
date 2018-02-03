# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/03 11:42:19 by slynn-ev          #+#    #+#              #
#    Updated: 2018/02/03 11:42:21 by slynn-ev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = src/main.c \
src/fdf.c \
src/draw.c \
src/lines.c \
src/border.c \

FRAME = -framework Appkit \
-framework OpenGL \

CPPFLAGS = -Iminilibx/ \
-Ilib/includes/ \
-Iincludes/ \

DEPS = includes/fdf.h

FLAGS = -Wall -Wextra -Werror

LIB = minilibx/libmlx.a \
lib/libftprintf.a \

all : library $(NAME)

$(NAME) : $(SRC) $(DEPS)
	gcc $(FLAGS) $(CPPFLAGS) -o $@ $(SRC) $(LIB) $(FRAME)

library :
	make -C minilibx/
	make -C lib/

clean : 
	make clean -C lib/
	make clean -C minilibx/

fclean :
	make fclean -C lib/
	rm -f $(NAME)

re : clean all
