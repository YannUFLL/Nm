#!/bin/sh
make > /dev/null
./ft_nm $1 > ft_nm.txt
nm $1 > nm.txt
diff ft_nm.txt nm.txt
rm nm.txt
rm ft_nm.txt
