#!/bin/sh
make > /dev/null
./ft_nm cub3D_bonus > output_ft.txt
nm cub3D_bonus > output_system.txt
dff output_ft.txt output_system.txt
rm output_ft.txt
rm output_system.txt

