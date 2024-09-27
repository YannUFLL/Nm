SRCS = $(wildcard src/*.c) 
CC = gcc
CFLAGS = -Wextra -Werror -Wall  -Wfatal-errors   -g -I./include 
LDFLAGS = -L./Library -lft -lftprintf
OBJS = $(SRCS:.c=.o)
PRGM = ft_nm 
DEBUG = -fsanitize=address

all : $(PRGM)

$(PRGM): $(OBJS)
	$(CC) $^ $(LDFLAGS) $(DEBUG) -o $@  

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: 
	rm -f $(OBJS) $(PRGM) 

re: fclean all

.PHONY: clean fclean all re
