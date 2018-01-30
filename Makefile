NAME = fdf

SRC = src/main.c \
src/fdf.c \

FRAME = -framework Appkit \
-framework OpenGL \

CPPFLAGS = -I../minilibx_macos/ \
-Ilib/includes/ \
-Iincludes/ \

FLAGS = -Wall -Wextra -Werror

LIB = ../minilibx_macos/libmlx.a \
lib/libftprintf.a \

all : library $(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(CPPFLAGS) -o $@ $^ $(LIB) $(FRAME)

library :
	make -C lib/

clean : 
	make fclean -C lib/
	rm -f $(NAME)

re : clean all
