/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:04:33 by ydumaine          #+#    #+#             */
/*   Updated: 2024/09/26 19:13:209 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"
#include "utils.h"
#include <elf.h>
#include <unistd.h>

#define SH_OFFSET 0x18


// char* find_associated_section(st_shndx, )
// {

// }

const char *find_section_name(Elf64_Shdr *section_header_tab, const char *shstrtab_section, int index)
{
    Elf64_Shdr section = section_header_tab[index];
    const char * section_name = (const char *)(shstrtab_section + section.sh_name);
    return (section_name);
}

char determine_symbol_type(const Elf64_Sym *sym, Elf64_Shdr *section_header_tab, const char *shstrtab_section, const char *symb_name)
{
 
    unsigned char type = sym->st_info & 0xf;
    unsigned char bind = sym->st_info >> 4;

    (void)symb_name;


    static const char type_chars[] = {'U', 'D', 'T', 'S', 'f', 'C', 'L', 'O', 'U', 'U', 'O', 'U', 'E', 'P'};
    char type_char = (type < sizeof(type_chars) / sizeof(type_chars[0])) ? type_chars[type] : 'U';
    
    if (sym->st_shndx == 0)
    {
        type_char = 'U';
    }
    if (sym->st_shndx != 0xFFF1)
    {
        const char * name = find_section_name(section_header_tab, shstrtab_section, sym->st_shndx);
        if (!strcmp(".rodata", name))
            type_char = 'R';
        else if (!strcmp(".data", name))
            type_char = 'D';
        else if (!strcmp(".note.ABI-tag", name))
            type_char = 'R';
        else if (!strcmp(".bss", name))
            type_char = 'B';
        else if (!strcmp(".eh_frame", name))
            type_char = 'R';
        else if (!strcmp(".eh_frame", name))
            type_char = 'R';
        else if (!strcmp(".eh_frame_hdr", name))
            type_char = 'R';
        else if (!strcmp(".eh_frame_hdr", name))
            type_char = 'R';
        else if (!strcmp(".eh_frame_hdr", name))
            type_char = 'R';
    }
    else
        type_char = 'A';

    if (type == 'D')
    {
        const char * name = find_section_name(section_header_tab, shstrtab_section, sym->st_shndx);
        if (!strcmp(".bss", name))
            type = 'B';
    }
    if (bind == STB_WEAK)
    {
        if (sym->st_shndx == SHN_UNDEF || sym->st_shndx == 0xFFF1)
            return 'w';
        return 'W';
    }
    if (type_char == 'U') return 'U';

    return (bind == STB_LOCAL) ? ft_tolower(type_char) : ft_toupper(type_char);
}


Elf64_Shdr *find_section_header(const char *section_name, Elf64_Shdr *section_headers_start_adress, char *shstrtab_section, size_t shnum)
{
    Elf64_Shdr *section = section_headers_start_adress;
    // write(1, shstrtab_section, 100);
    for (size_t i = 0; i < shnum; i++)
    {
        const char *current_section_name = shstrtab_section + section[i].sh_name;
        if (strcmp(current_section_name, section_name) == 0)
        {
            return &section[i];
        }
    }
    return (NULL);
}


char *ignore_underscore(char *name)
{
    int i = 0; 
    while (name[i] == '_' && name[i])
        i++;
    return (&name[i]);
}

int compare_symbols(Elf64_Sym *sym1, Elf64_Sym* sym2, char *sym_str_tab)
{
    char *name1 = sym_str_tab + sym1->st_name;
    char *name2 = sym_str_tab + sym2->st_name;

    // step 1: compare the name 
    int cmp = ft_strcmp(name1, name2);
    if (cmp != 0)
        return (cmp);

    // step 2: compare the adress
    if (sym1->st_value < sym2->st_value)
        return (-1);
    else if (sym1->st_value > sym2->st_value)
        return (1);
    
    // step 3: compare the weakness
    short int bind1 = sym1->st_info >> 4;
    short int bind2 = sym2->st_info >> 4;
    if (bind1 != STB_WEAK && bind2 == STB_WEAK)
        return (-1);
    else if (bind1 == STB_WEAK && bind2 == STB_WEAK)
        return (1);
    return (0);
}

void print_sym_tab(Elf64_Sym *symtab, Elf64_Off symtab_size, char *sym_str_tab)
{
    Elf64_Off i = 0;

    while (i < symtab_size)
    {
        ft_printf("[%s]", sym_str_tab + symtab[i].st_name);
        i++;
    }
    ft_printf("\n");
    ft_printf("\n");
}

void sort_sym_tab(Elf64_Sym *symtab, Elf64_Off symtab_size,char *sym_str_tab)
{
    Elf64_Off i = 1;
    Elf64_Off j = 0;
    Elf64_Sym symb;

    while (i < symtab_size)
    {
        j = i;
        symb = symtab[i];

        while (j > 0 && compare_symbols(&symb,  &symtab[j - 1], sym_str_tab) < 0)
        {
            symtab[j] = symtab[j - 1];
            j--;
        }
        symtab[j] = symb;
        i++;
        // print_sym_tab(symtab, symtab_size, sym_str_tab);
    }
}

void display_symbol_info(const Elf64_Sym *symb_tab, size_t sym_tab_size, const char *sym_str_tab, Elf64_Shdr *section_header_tab, const char *shstrtab_section)
{
    Elf64_Off addr; 
    short int zero_number = 16;
    for (size_t i = 0; i < (sym_tab_size / sizeof(Elf64_Sym)); i++) 
    {
        if (symb_tab[i].st_name == 0)
            continue;
        char symbol_type = determine_symbol_type(&symb_tab[i], section_header_tab, shstrtab_section, sym_str_tab+ (Elf64_Off)symb_tab[i].st_name);
        if (symbol_type == 'f')
            continue;
        if (symb_tab[i].st_value != 0)
        {
            addr =  symb_tab[i].st_value;
            zero_number = 16;
            while(addr > 0)
            {
                addr = addr / 16;
                zero_number--;
            }
            while(zero_number > 0)
            {
                ft_printf("0");
                zero_number--;
            }
            ft_printf("%x ", (Elf64_Off *)symb_tab[i].st_value);
        }
        else
            ft_printf("                 ");
        ft_printf("%c ", symbol_type);
        if (symb_tab[i].st_name != 0)
        {
            ft_printf("%s", (char *)(sym_str_tab+ (Elf64_Off)symb_tab[i].st_name));
        }
        ft_printf("\n");
    }

}


MappedFile get_mapped_file_memory(const char * file_name)
{
    int fd = open(file_name, O_RDONLY);
    void *mapped = MAP_FAILED;
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    struct stat filestat; 
    if (fstat(fd, &filestat) == -1 )
    {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }
    mapped = mmap(NULL, filestat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED)
    {
        perror("mapped");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    MappedFile mf = {mapped, filestat.st_size};
    return (mf);
}


int ft_check_header(Elf64_Ehdr *ehdr)
{
    if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr->e_ident[EI_MAG1] != ELFMAG1 || 
        ehdr->e_ident[EI_MAG2] != ELFMAG2 || 
        ehdr->e_ident[EI_MAG3] != ELFMAG3)
        {
            printf("This file is not an ELF file");
            return (EXIT_FAILURE);
        }
    if (ehdr->e_ident[EI_CLASS] == ELFCLASSNONE)
    {
        printf("nm: invalid_magic_number: file format not recognized");
        return (EXIT_FAILURE);
    }
    if (ehdr->e_ident[EI_DATA] == ELFDATANONE)
    {
        printf("nm: invalid_magic_number: file format not recognized");
        return (EXIT_FAILURE);
    }
    return (0);
}


void parse_elf_file(char *file_name, int print_file_name)
{
    MappedFile mapped_file = get_mapped_file_memory(file_name);
    Elf64_Ehdr* ehdr =  mapped_file.mapped;
    if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
        printf("little endian");
    else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
        printf("big endian ");
    if (ft_check_header(ehdr))
    {
        munmap(mapped_file.mapped, mapped_file.size);
        exit(1);
    }
    short int index_section_header_sections_names = ehdr->e_shstrndx;
    Elf64_Off section_header_tab_addr_offset = ehdr->e_shoff;
    if (section_header_tab_addr_offset >= mapped_file.size) {
        fprintf(stderr, "Invalid section section_header_tab_addr_offset\n");
        munmap(mapped_file.mapped, mapped_file.size);
        exit(EXIT_FAILURE);
    }
    Elf64_Shdr *section_header_tab = (Elf64_Shdr *)((uint64_t)(ehdr) + section_header_tab_addr_offset);
    Elf64_Shdr *section_header_shstrtab = &section_header_tab[index_section_header_sections_names];
    Elf64_Off section_shstrtab_offset = section_header_shstrtab->sh_offset;
    if (section_shstrtab_offset >= mapped_file.size) {
        fprintf(stderr, "Invalid section header string table offset\n");
        munmap(mapped_file.mapped, mapped_file.size);
        exit(EXIT_FAILURE);
    }
    char *section_shstrtab = (char *)ehdr + section_shstrtab_offset;
    // Nice, we have find the section header string tab. 

    Elf64_Shdr *sym_tab_section_header = find_section_header( ".symtab", section_header_tab, section_shstrtab, ehdr->e_shnum);
    Elf64_Off  symb_tab_offset = sym_tab_section_header->sh_offset;
    if (symb_tab_offset >= mapped_file.size) {
        fprintf(stderr, "Invalid section symb tab offset\n");
        munmap(mapped_file.mapped, mapped_file.size);
        exit(EXIT_FAILURE);
    }
    Elf64_Sym  *sym_tab = (Elf64_Sym *)((char *)ehdr + symb_tab_offset);
    // We now have the symbole tab, with all the symboles. Nice ! 

    Elf64_Off symb_str_offset  = (find_section_header(".strtab", section_header_tab, section_shstrtab, ehdr->e_shnum))->sh_offset;
    if (symb_str_offset >= mapped_file.size) {
        fprintf(stderr, "Invalid section symb tab offset\n");
        munmap(mapped_file.mapped, mapped_file.size);
        exit(EXIT_FAILURE);
    }
    Elf64_Off sym_tab_size = (Elf64_Off)(sym_tab_section_header->sh_size);
    char *sym_str_tab= (char *)ehdr + symb_str_offset;

    
    Elf64_Sym *symtab_copy = malloc(sym_tab_size);
    if (!symtab_copy) 
    {
        perror("malloc");
        munmap(mapped_file.mapped, mapped_file.size);
        exit(EXIT_FAILURE);
    }
    ft_memcpy(symtab_copy, sym_tab, sym_tab_size);
    sort_sym_tab(symtab_copy, sym_tab_size / sizeof(Elf64_Sym), sym_str_tab);
    if (print_file_name == 1)
        ft_printf("\n%s:\n", file_name);
    display_symbol_info(symtab_copy, sym_tab_size, sym_str_tab, section_header_tab, section_shstrtab);
    free(symtab_copy);
    munmap(mapped_file.mapped, mapped_file.size);
}


int main(int argc, char **argv)
{
    if (argc == 1)
            parse_elf_file("a.out", 0);
    else if (argc == 2)
            parse_elf_file(argv[1], 0);
    else
    {
        for (int i = 1; i < argc; i++)
            parse_elf_file(argv[i], 1);
    }
}