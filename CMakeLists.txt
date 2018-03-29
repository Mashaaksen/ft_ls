cmake_minimum_required(VERSION 3.9)
project(ft_ls C)

include_directories(includes libft) # headers

link_directories(libft) # libraries

set(CMAKE_C_STANDARD 99)

add_executable(ft_ls main.c ft_ls.h ft_initialization.c ft_error.c ft_verification_param.c ft_insert_files.c ft_opendir.c)

target_link_libraries(ft_ls libft.a) # linkage