#!/bin/sh
make > /dev/null

# Parcourir tous les fichiers du répertoire donné
for file in "$1"/*; do
    if [ -f "$file" ]; then
        echo "Processing $file"
        ./ft_nm "$file" > ft_nm.txt
        nm "$file" > nm.txt
        diff ft_nm.txt nm.txt
        rm nm.txt ft_nm.txt
        
        # Pause pour l'utilisateur avec message d'instructions
        echo "Press ENTER to continue or CTRL+C to exit."
        read dummy_var
    fi
done
