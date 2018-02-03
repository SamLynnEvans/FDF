# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/03 11:42:19 by slynn-ev          #+#    #+#              #
#    Updated: 2018/02/03 12:54:50 by slynn-ev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC_NAME = main.c \
fdf.c \
draw.c \
lines.c \
border.c \

SRC_PATH = src

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

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

$(NAME) : $(OBJ)
	@gcc $(FLAGS) $(CPPFLAGS) -o $@ $(OBJ) $(LIB) $(FRAME)
	@echo "##############" | tr -d '\n'
	@echo "\nFDF ready"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(OBJ_PATH)
	@gcc $(FLAGS) $(CPPFLAGS) -o $@ -c $<
	@echo "##############" | tr -d '\n'


library :
	make -C minilibx/
	make -C lib/

clean :
	rm -r $(OBJ_PATH)	
	make clean -C lib/
	make clean -C minilibx/

fclean :
	make fclean -C lib/
	rm -f $(NAME)

re : clean all
