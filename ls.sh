#!/bin/sh

make

ls $@ > diff_ls
./ft_ls $@ > diff_my
vim -d diff_ls diff_my
rm diff_ls diff_my