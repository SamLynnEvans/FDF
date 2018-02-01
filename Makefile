NAME = fdf

SRC = src/main.c \
src/fdf.c \
src/draw.c \

FRAME = -framework Appkit \
-framework OpenGL \

CPPFLAGS = -Iminilibx/ \
-Ilib/includes/ \
-Iincludes/ \

FLAGS = -Wall -Wextra -Werror -g

LIB = minilibx/libmlx.a \
lib/libftprintf.a \

all : library $(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(CPPFLAGS) -o $@ $^ $(LIB) $(FRAME)

library :
	make -C minilibx/
	make -C lib/

clean : 
	make fclean -C lib/
	rm -f $(NAME)

re : clean all
