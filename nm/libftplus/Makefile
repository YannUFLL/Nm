# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 14:41:53 by ydumaine          #+#    #+#              #
#    Updated: 2024/12/19 19:00:12 by ydumaine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #




NAME = libftplus.a

Libft = Libft/libft.a

Ft_printf = Ft_printf/libftprintf.a

Libft_DIR = Libft

Ft_printf_DIR = Ft_printf


all : $(Libft) $(Ft_printf)
	@ar -x $(Libft)              # Extraire les .o de libft.a
	@ar -x $(Ft_printf)          # Extraire les .o de ft_printf.a
	ar -rcs $(NAME) *.o          # Créer libftplus.a avec tous les .o
	rm -f *.o                    # Nettoyer les fichiers objets temporaires

$(Libft) : 
	make -C Libft

$(Ft_printf) :
	make -C Ft_printf

clean :
	make clean -C $(Libft_DIR)
	make clean -C $(Ft_printf_DIR)

fclean :
	make fclean -C $(Libft_DIR)
	make fclean -C $(Ft_printf_DIR)
	rm -f $(NAME)

re : 
	make re -C Libft
	make re -C Ft_printf

.PHONY : all clean fclean re