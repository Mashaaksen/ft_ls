cmake_minimum_required(VERSION 3.7)
project(ls)

set(CMAKE_C_STANDARD 99)

include_directories(includes libft) # headers

link_directories(libft) # libraries

set(SOURCE_FILES main.c find_keys.c find_path.c ft_ls.h ft_ls.c sort_ls.c libft/ft_strndup.c print_ls.c start.c create_list_files.c)
add_executable(ls ${SOURCE_FILES})

target_link_libraries(ls libft.a) # linkage