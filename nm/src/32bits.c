/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32bits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:56:13 by ydumaine          #+#    #+#             */
/*   Updated: 2024/11/06 15:49:35 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "nm.h"

int ft_check_offset32(Elf32_Ehdr *ehdr, size_t size)
{
    if (ehdr->e_shoff >= size)
        return (1);
    if (ehdr->e_phoff >= size)
        return (1);
    if (ehdr->e_shstrndx >= ehdr->e_shnum)
        return (1);
    return (0);
}

int ft_check_section_numbers32(Elf32_Ehdr *ehdr, size_t size)
{
    if (ehdr->e_shnum == 0xFFFF)
        return (1);
    if (ehdr->e_shnum == 0)
        return (1);
    size_t sh_table_size = ehdr->e_shnum * ehdr->e_shentsize;
    if (ehdr->e_shoff + sh_table_size > size)
        return (1);
    if (ehdr->e_shstrndx >= ehdr->e_shnum)
        return (1);
    return (0);
}

int compare_symbols32(Elf32_Sym *sym1, Elf32_Sym* sym2, char *sym_str_tab)
{
    char *name1 = sym_str_tab + sym1->st_name;
    char *name2 = sym_str_tab + sym2->st_name;

    // step 1: compare the name 
    int cmp = ft_strcmp_custom(name1, name2);
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

void print_sym_tab32(Elf32_Sym *symtab, Elf32_Off symtab_size, char *sym_str_tab)
{
    Elf32_Off i = 0;

    while (i < symtab_size)
    {
        ft_printf("[%s]", sym_str_tab + symtab[i].st_name);
        i++;
    }
    ft_printf("\n");
    ft_printf("\n");
}

const char *find_section_name32(Elf32_Shdr *section_header_tab, const char *shstrtab_section, int index)
{
    Elf32_Shdr section = section_header_tab[index];
    const char * section_name = (const char *)(shstrtab_section + section.sh_name);
    return (section_name);
}

void sort_sym_tab32(Elf32_Sym *symtab, Elf32_Off symtab_size,char *sym_str_tab)
{
    Elf32_Off i = 1;
    Elf32_Off j = 0;
    Elf32_Sym symb;

    while (i < symtab_size)
    {
        j = i;
        symb = symtab[i];

        while (j > 0 && compare_symbols32(&symb,  &symtab[j - 1], sym_str_tab) < 0)
        {
            symtab[j] = symtab[j - 1];
            j--;
        }
        symtab[j] = symb;
        i++;
    }
}

Elf32_Shdr *find_section_header32(const char *section_name, Elf32_Shdr *section_headers_start_adress, char *shstrtab_section, size_t shnum)
{
    Elf32_Shdr *section = section_headers_start_adress;
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

char determine_symbol_type32(const Elf32_Sym *sym, Elf32_Shdr *section_header_tab, const char *shstrtab_section, const char *symb_name, size_t shnum)
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
        if (sym->st_shndx > shnum)
            return 'U';
        const char * name = find_section_name32(section_header_tab, shstrtab_section, sym->st_shndx);
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
        const char * name = find_section_name32(section_header_tab, shstrtab_section, sym->st_shndx);
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

void display_symbol_info32(const Elf32_Sym *symb_tab, size_t sym_tab_size, const char *sym_str_tab, Elf32_Shdr *section_header_tab, const char *shstrtab_section, size_t shnum)
{
    Elf32_Off addr; 
    short int zero_number = 8;
    for (size_t i = 0; i < (sym_tab_size / sizeof(Elf32_Sym)); i++) 
    {
        if (symb_tab[i].st_name == 0)
            continue;
        char symbol_type = determine_symbol_type32(&symb_tab[i], section_header_tab, shstrtab_section, sym_str_tab+ (Elf32_Off)symb_tab[i].st_name, shnum);
        if (symbol_type == 'f' || symbol_type == 'F' || symbol_type == 'a' || symbol_type == 'A')
            continue;
        if (symb_tab[i].st_value != 0)
        {
            addr =  symb_tab[i].st_value;
            zero_number = 8;
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
            ft_printf("%x ", symb_tab[i].st_value);
        }
        else
            ft_printf("         ");
        ft_printf("%c ", symbol_type);
        if (symb_tab[i].st_name != 0)
        {
            ft_printf("%s", (char *)(sym_str_tab+ (Elf32_Off)symb_tab[i].st_name));
        }
        ft_printf("\n");
    }

}

void parse_32_bits(Elf32_Ehdr *ehdr, MappedFile mapped_file, char *file_name, int print_file_name)
{
    if (ft_check_offset32(ehdr, mapped_file.size))
    {
        printf("ft_nm: %s: File format not recognized\n", file_name);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    if (ft_check_section_numbers32(ehdr, mapped_file.size))
    {
        printf("ft_nm: %s: File format not recognized\n", file_name);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }

    short int index_section_header_sections_names = ehdr->e_shstrndx;
    Elf32_Off section_header_tab_addr_offset = ehdr->e_shoff;

    if (section_header_tab_addr_offset >= mapped_file.size) {
        fprintf(stderr, "Invalid section section_header_tab_addr_offset\n");
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    Elf32_Shdr *section_header_tab = (Elf32_Shdr *)((char *)(ehdr) + section_header_tab_addr_offset);
    Elf32_Shdr *section_header_shstrtab = &section_header_tab[index_section_header_sections_names];
    Elf32_Off section_shstrtab_offset = section_header_shstrtab->sh_offset;
    if (section_shstrtab_offset >= mapped_file.size) {
        fprintf(stderr, "Invalid section header string table offset\n");
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    char *section_shstrtab = (char *)ehdr + section_shstrtab_offset;
    // Nice, we have find the section header string tab. 

    Elf32_Shdr *sym_tab_section_header = find_section_header32( ".symtab", section_header_tab, section_shstrtab, ehdr->e_shnum);
    if (!sym_tab_section_header)
    {
        printf("ft_nm: %s: no symbols\n", file_name);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    Elf32_Off  symb_tab_offset = sym_tab_section_header->sh_offset;
    if (symb_tab_offset >= mapped_file.size) {
        fprintf(stderr, "Invalid section symb tab offset\n");
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    Elf32_Sym  *sym_tab = (Elf32_Sym *)((char *)ehdr + symb_tab_offset);
    // We now have the symbole tab, with all the symboles. Nice ! 

    Elf32_Off symb_str_offset  = (find_section_header32(".strtab", section_header_tab, section_shstrtab, ehdr->e_shnum))->sh_offset;
    if (symb_str_offset >= mapped_file.size) {
        fprintf(stderr, "Invalid section symb tab offset\n");
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    Elf32_Off sym_tab_size = (Elf32_Off)(sym_tab_section_header->sh_size);
    char *sym_str_tab= (char *)ehdr + symb_str_offset;

    
    Elf32_Sym *symtab_copy = malloc(sym_tab_size);
    if (!symtab_copy) 
    {
        perror("malloc");
        munmap(mapped_file.mapped, mapped_file.size);
        exit(EXIT_FAILURE);
    }
    ft_memcpy(symtab_copy, sym_tab, sym_tab_size);
    sort_sym_tab32(symtab_copy, sym_tab_size / sizeof(Elf32_Sym), sym_str_tab);
    if (print_file_name == 1)
        ft_printf("\n%s:\n", file_name);
    display_symbol_info32(symtab_copy, sym_tab_size, sym_str_tab, section_header_tab, section_shstrtab, ehdr->e_shnum);
    free(symtab_copy);
    munmap(mapped_file.mapped, mapped_file.size);
}