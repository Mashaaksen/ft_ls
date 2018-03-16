# cmake_minimum_required(VERSION <specify CMake version here>)
project(ls C)

include_directories(includes libft) # headers

link_directories(libft) # libraries

set(CMAKE_C_STANDARD 99)

add_executable(ls main.c ft_initialization.c ft_error.c ft_verification_param.c ft_insert_files.c ft_opendir.c)

target_link_libraries(ls libft.a) # linkage