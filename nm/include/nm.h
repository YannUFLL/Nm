/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:42:26 by ydumaine          #+#    #+#             */
/*   Updated: 2024/11/06 15:21:49 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
#define NM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <elf.h>
#include "ft_printf.h"
#include "libft.h"
#include "utils.h"

#define SH_OFFSET 0x18

// Generic ELF header structure
typedef struct {
    unsigned char e_ident[EI_NIDENT];
} Elf_Generic_Ehdr;

// Type for storing mapped file information
typedef struct {
    void *mapped;
    size_t size;
} MappedFile;

/* ************************************************************************** */
/*                          Function Prototypes - 64-bit                      */
/* ************************************************************************** */

const char *find_section_name64(Elf64_Shdr *section_header_tab, const char *shstrtab_section, int index);
char determine_symbol_type64(const Elf64_Sym *sym, Elf64_Shdr *section_header_tab, const char *shstrtab_section, const char *symb_name, size_t shnum);
Elf64_Shdr *find_section_header64(const char *section_name, Elf64_Shdr *section_headers_start_adress, char *shstrtab_section, size_t shnum);
int compare_symbols64(Elf64_Sym *sym1, Elf64_Sym *sym2, char *sym_str_tab);
void print_sym_tab64(Elf64_Sym *symtab, Elf64_Off symtab_size, char *sym_str_tab);
void sort_sym_tab64(Elf64_Sym *symtab, Elf64_Off symtab_size, char *sym_str_tab);
void display_symbol_info64(const Elf64_Sym *symb_tab, size_t sym_tab_size, const char *sym_str_tab, Elf64_Shdr *section_header_tab, const char *shstrtab_section, size_t shnum);
int ft_check_offset64(Elf64_Ehdr *ehdr, size_t size);
int ft_check_section_numbers64(Elf64_Ehdr *ehdr, size_t size);
void parse_64_bits(Elf64_Ehdr *ehdr, MappedFile mapped_file, char *file_name, int print_file_name);

/* ************************************************************************** */
/*                          Function Prototypes - 32-bit                      */
/* ************************************************************************** */

int ft_check_offset32(Elf32_Ehdr *ehdr, size_t size);
int ft_check_section_numbers32(Elf32_Ehdr *ehdr, size_t size);
int compare_symbols32(Elf32_Sym *sym1, Elf32_Sym *sym2, char *sym_str_tab);
void print_sym_tab32(Elf32_Sym *symtab, Elf32_Off symtab_size, char *sym_str_tab);
const char *find_section_name32(Elf32_Shdr *section_header_tab, const char *shstrtab_section, int index);
void sort_sym_tab32(Elf32_Sym *symtab, Elf32_Off symtab_size, char *sym_str_tab);
Elf32_Shdr *find_section_header32(const char *section_name, Elf32_Shdr *section_headers_start_adress, char *shstrtab_section, size_t shnum);
char determine_symbol_type32(const Elf32_Sym *sym, Elf32_Shdr *section_header_tab, const char *shstrtab_section, const char *symb_name, size_t shnum);
void display_symbol_info32(const Elf32_Sym *symb_tab, size_t sym_tab_size, const char *sym_str_tab, Elf32_Shdr *section_header_tab, const char *shstrtab_section, size_t shnum);
void parse_32_bits(Elf32_Ehdr *ehdr, MappedFile mapped_file, char *file_name, int print_file_name);

/* ************************************************************************** */
/*                           General Utility Functions                        */
/* ************************************************************************** */

char *ignore_underscore(char *name);
MappedFile get_mapped_file_memory(const char *file_name);
int ft_check_header(Elf_Generic_Ehdr *ehdr);
void parse_elf_file(char *file_name, int print_file_name);
int main(int argc, char **argv);

#endif /* NM_H */
