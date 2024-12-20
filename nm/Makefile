SRCS = $(wildcard src/*.c)
BAD_ELF_GENERATOR_SRC = bad_elf_generator/bad_elf_generator.c
CC = gcc
CFLAGS = -Wextra -Werror -Wall  -Wfatal-errors   -g  -I./include 
LDFLAGS = $(LIBFTPLUS)
OBJS = $(SRCS:.c=.o)
PRGM = ft_nm 
TEST_ELF = bad_elf_generator/bad_elf_generator
DEBUG = #-g -fsanitize=address 
LIBFTPLUS_DIR = libftplus
LIBFTPLUS = $(LIBFTPLUS_DIR)/libftplus.a


all : $(PRGM) $(TEST_ELF)
	cd bad_elf_generator && ./bad_elf_generator

$(LIBFTPLUS) : 
	@make -C $(LIBFTPLUS_DIR)

$(PRGM): $(OBJS) $(LIBFTPLUS)
	$(CC) $^ $(LDFLAGS) $(DEBUG) -o $@  

$(TEST_ELF): $(BAD_ELF_GENERATOR_SRC) 
	$(CC) $^ -o $(TEST_ELF)

%.o : %.c 
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

clean: 
	rm -f $(OBJS)
	@make -C $(LIBFTPLUS_DIR) clean

fclean: 
	rm -f $(OBJS) $(PRGM) 
	@make -C $(LIBFTPLUS_DIR) fclean
	find ./bad_elf_generator -type f ! -name "*.*" ! -name "executable_file" -exec rm -f {} +
	rm -f ./bad_elf_generator/a.out

re: fclean all 

.PHONY: clean fclean all re
