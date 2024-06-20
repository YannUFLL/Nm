SRCS = $(wildcard src/*.c) 
CC = gcc
CFLAGS = -Wextra -Werror -Wall -g -I./include 
LDFLAGS = -L./Library -lft -lftprintf
OBJS = $(SRCS:.c=.o)
PRGM = nm 

all : $(PRGM)

$(PRGM): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@  

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: 
	rm -f $(OBJS) $(PRGM) 

re: fclean all

.PHONY: clean fclean all re
