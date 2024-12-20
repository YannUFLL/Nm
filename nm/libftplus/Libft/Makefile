# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 12:48:02 by ydumaine          #+#    #+#              #
#    Updated: 2022/03/11 22:35:24 by ydumaine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_bzero.c ft_isascii.c ft_memchr.c ft_memset.c ft_putstr_fd.c\
ft_striteri.c ft_strlen.c ft_strrchr.c ft_toupper.c ft_calloc.c\
ft_isdigit.c ft_memcmp.c ft_putchar_fd.c ft_split.c ft_strjoin.c\
ft_strmapi.c ft_strtrim.c ft_isalnum.c ft_isprint.c ft_memcpy.c\
ft_putendl_fd.c ft_strchr.c ft_strlcat.c ft_strncmp.c ft_substr.c\
ft_atoi.c ft_isalpha.c ft_itoa.c ft_memmove.c ft_putnbr_fd.c\
ft_strdup.c ft_strlcpy.c ft_strnstr.c ft_tolower.c\

BSRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c\

OBJS = ${SRCS:.c=.o}

BOBJS = ${BSRCS:.c=.o}

NAME = libft.a

CC = cc

BIBL = ar -rc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o: 
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME}:	${OBJS}
			${BIBL} ${NAME} ${OBJS}

bonus:		${OBJS} ${BOBJS}
			${BIBL} ${NAME} ${OBJS} ${BOBJS}


all:		${NAME}

clean:
			${RM} ${OBJS} ${BOBJS}

fclean:     clean
			${RM} ${NAME}

re:					fclean all

.PHONY:			all clean fclean re bonus
