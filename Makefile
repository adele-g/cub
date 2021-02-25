NAME    = cub3D
CC      = gcc -Wall -Werror -Wextra
LIBX	= -L minilibx -lmlx -framework OpenGL -framework AppKit
MLX		= libmlx.dylib
SRC     =	main.c \
			get_next_line/get_next_line_bonus.c \
			get_next_line/get_next_line_utils_bonus.c \
			parsing_resolution.c \
			parser_utils.c \
			parser_utils_second.c \
			parser_color_n_path.c \
			parser_init.c \
			parser_check_map_stuff.c \
			parser_check_map.c \
			parser_map.c \
			parser_find_spec.c \
			raycast_init.c \
			draw.c \
			raycasting.c \
			sprites_init.c \
			bmp.c \
			init.c \
			keys.c \
			key_2.c \
			sprites_utils.c

OBJ = $(SRC:.c=.o)
RM	= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	MAKE -C minilibx
	cp minilibx/libmlx.dylib .
	${CC} -o ${NAME} ${LIBX} ${OBJ}

%.o : %.c
	${CC} -c $< -o $@ -I.

clean:
	${RM} ${OBJ}
	${RM} pic.bmp
	MAKE clean -C minilibx

fclean:			clean
	${RM} ${NAME}
	${RM} ${MLX}

re:				fclean all

.PHONY:			all clean fclean re
