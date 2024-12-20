
# Libft: Your Very First Own Library

![version](https://img.shields.io/badge/version-15-blue)

## Table of Contents

1. [Introduction](#introduction)
2. [Common Instructions](#common-instructions)
3. [Mandatory Part](#mandatory-part)
    - [Part 1 - Libc Functions](#part-1---libc-functions)
    - [Part 2 - Additional Functions](#part-2---additional-functions)
4. [Bonus Part](#bonus-part)

## Introduction

This library aims to replicate some of the standard C library functions as well as some additional utilities. This serves as an excellent tool for future C projects.

## Common Instructions

- Written in C and conforms to "The Norm".
- No memory leaks.
- Makefile rules: `all`, `clean`, `fclean`, `re`, and `bonus`.

## Mandatory Part

### Part 1 - Libc Functions

The following libc functions are replicated:

- `ft_isalpha`
- `ft_isdigit`
- `ft_isalnum`
- `ft_isascii`
- `ft_isprint`
- `ft_strlen`
- `ft_memset`
- `ft_bzero`
- `ft_memcpy`
- `ft_memmove`
- `ft_strlcpy`
- `ft_strlcat`
- `ft_toupper`
- `ft_tolower`
- `ft_strchr`
- `ft_strrchr`
- `ft_strncmp`
- `ft_memchr`
- `ft_memcmp`
- `ft_strnstr`
- `ft_atoi`

### Part 2 - Additional Functions

Extra utility functions are included such as:

- `ft_substr`
- `ft_strjoin`
- `ft_strtrim`
- `ft_split`
- `ft_itoa`
- `ft_strmapi`
- `ft_striteri`
- `ft_putchar_fd`
- `ft_putstr_fd`
- `ft_putendl_fd`
- `ft_putnbr_fd`

## Bonus Part

Bonus section includes list manipulation functions, with the following structure:

```c
typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;
```
