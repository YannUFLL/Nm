#!/bin/sh
make > /dev/null

# Spécifiez le répertoire contenant les fichiers à traiter

# Parcourir tous les fichiers du répertoire
for file in "$1"/*; do
    if [ -f "$file" ]; then
        echo "Processing $file"
        ./ft_nm "$file" > ft_nm.txt
        nm "$file" > nm.txt
        diff ft_nm.txt nm.txt
        rm nm.txt ft_nm.txt
    fi
done
