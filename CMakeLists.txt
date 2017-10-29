cmake_minimum_required(VERSION 3.7)
project(ls)

set(CMAKE_C_STANDARD 99)

include_directories(includes libft) # headers

link_directories(libft) # libraries

set(SOURCE_FILES main.c ft_ls.h find_path.c find_keys.c sort_ls.c ft_ls.c)
add_executable(new_ls ${SOURCE_FILES})

target_link_libraries(new_ls libft.a) # linkage