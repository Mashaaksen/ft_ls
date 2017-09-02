cmake_minimum_required(VERSION 3.7)
project(ft_ls)

set(CMAKE_C_STANDARD 99)

include_directories(includes libft) # headers

link_directories(libft) # libraries

set(SOURCE_FILES main.c ft_ls.h ft_keys.c ft_fill_name.c ft_alpha_sort.c error.c recursion.c ordinary.c ft_time_sort.c ft_print.c ela.cpp)
add_executable(ft_ls ${SOURCE_FILES})

target_link_libraries(ft_ls libft.a) # linkage
