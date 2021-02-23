cmake_minimum_required(VERSION 3.17)
project(cub3d C)

set(CMAKE_C_FLAGS "-Lmlx -lmlx -framework OpenGL -framework AppKit")

link_directories(/usr/local/lib)
include_directories(/usr/local/include)

add_executable(cub3d main.c get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c get_next_line/get_next_line_bonus.h cub3d.h parsing_resolution.c parser_utils.c paser_utils_second.c parser_color_n_path.c parser_init.c parser_check_map_stuff.c parser_check_map.c parser_map.c parser_find_spec.c)