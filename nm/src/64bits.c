/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   64bits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:48:40 by ydumaine          #+#    #+#             */
/*   Updated: 2024/12/16 14:47:03 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int ft_check_offset64(Elf64_Ehdr *ehdr, size_t size, int is_little_endian)
{
    if (read_uint64(ehdr->e_shoff, is_little_endian) >= size)
        return (1);
    if (read_uint64(ehdr->e_phoff, is_little_endian) >= size)
        return (1);
    if (read_uint16(ehdr->e_shstrndx, is_little_endian) >= read_uint16(ehdr->e_shnum, is_little_endian))
        return (1);
    return (0);
}

int ft_check_section_numbers64(Elf64_Ehdr *ehdr, size_t size, int is_little_endian)
{
    uint16_t shnum = read_uint16(ehdr->e_shnum, is_little_endian);
    uint16_t shentsize = read_uint16(ehdr->e_shentsize, is_little_endian);
    uint64_t shoff = read_uint64(ehdr->e_shoff, is_little_endian);
    uint16_t shstrndx = read_uint16(ehdr->e_shstrndx, is_little_endian);

    if (shnum == 0xFFFF)
        return (1);
    if (shnum == 0)
        return (1);
    size_t sh_table_size = shnum * shentsize;
    if (shoff + sh_table_size > size)
        return (1);
    if (shstrndx >= shnum)
        return (1);
    return (0);
}

int compare_symbols64(Elf64_Sym *sym1, Elf64_Sym* sym2, char *sym_str_tab, size_t sym_str_tab_size, int is_little_endian)
{
    uint32_t st_name1 = read_uint32(sym1->st_name, is_little_endian);
    uint32_t st_name2 = read_uint32(sym2->st_name, is_little_endian);
    char *name1 = sym_str_tab + st_name1;
    char *name2 = sym_str_tab + st_name2;

    // Handle non-null-terminated strings
    while (name1 < sym_str_tab + sym_str_tab_size && *name1 != '\0')
    {
        name1++;
    }
    while (name2 < sym_str_tab + sym_str_tab_size && *name2 != '\0')
    {
        name2++;
    }
    if (name1 == sym_str_tab + sym_str_tab_size && name2 != sym_str_tab + sym_str_tab_size)
        return (-1);
    if (name2 == sym_str_tab + sym_str_tab_size && name1 != sym_str_tab + sym_str_tab_size)
        return (1);
    if (name1 == sym_str_tab + sym_str_tab_size && name2 == sym_str_tab + sym_str_tab_size)
        return (0);
    name1 = sym_str_tab + st_name1;
    name2 = sym_str_tab + st_name2;
    // Step 1: Compare the names
    int cmp = ft_strcmp_custom((const unsigned char *)name1, (const unsigned char *)name2);
    if (cmp != 0)
        return (cmp);

    // Step 3: Compare the binding (weakness)
    // unsigned char bind1 = sym1->st_info >> 4;
    // unsigned char bind2 = sym2->st_info >> 4;
    // if (bind1 != STB_WEAK && bind2 == STB_WEAK)
    //     return (-1);
    // else if (bind1 == STB_WEAK && bind2 != STB_WEAK)
    //     return (1);
    // return (0);
    return (0);
}

// FUNCTION that find a symbol name in the symbol table
void print_sym(Elf64_Sym *symtab, Elf64_Off symtab_size, char *sym_str_tab, char *symb_name)
{
    Elf64_Off i = 0;

    while (i < symtab_size)
    {
        if (!strcmp(sym_str_tab +  symtab[i].st_name,symb_name)) 
        {
            
            ft_printf("%d[%s]\n", i, sym_str_tab + symtab[i - 1].st_name);
            ft_printf("%d[%s]\n", i, sym_str_tab + symtab[i].st_name);
            ft_printf("%d[%s]\n", i, sym_str_tab + symtab[i + 1].st_name);
        }
        i++;
    }
    ft_printf("\n");
    ft_printf("\n");
}
void print_sym_tab64(Elf64_Sym *symtab, Elf64_Off symtab_size, char *sym_str_tab)
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

const char *find_section_name64(Elf64_Shdr *section_header_tab, const char *shstrtab_section, uint16_t index, uint16_t shnum, int is_little_endian)
{
    if (index >= shnum)
        return (NULL);
    Elf64_Shdr section = section_header_tab[index];
    uint32_t sh_name = read_uint32(section.sh_name, is_little_endian);
    const char *section_name = (const char *)(shstrtab_section + sh_name);
    return (section_name);
}

void sort_sym_tab64(Elf64_Sym *symtab, Elf64_Off symtab_size, char *sym_str_tab, size_t sym_str_tab_size, int is_little_endian)
{
    Elf64_Off i = 1;
    Elf64_Off j = 0;
    Elf64_Sym symb;
    // print_sym(symtab, symtab_size, sym_str_tab, "archive/tar.headerFileInfo.IsDir");
    // print_sym(symtab, symtab_size, sym_str_tab, "archive/tar.(*headerFileInfo).IsDir");
    // print_sym(symtab, symtab_size, sym_str_tab, "compress/bzip2.huffmanCodes.Len");
    // print_sym(symtab, symtab_size, sym_str_tab, "compress/bzip2.(*huffmanCodes).Len");

    while (i < symtab_size)
    {
        j = i;
        symb = symtab[i];

        while (j > 0 && compare_symbols64(&symb,  &symtab[j - 1], sym_str_tab, sym_str_tab_size, is_little_endian) < 0)
        {
            symtab[j] = symtab[j - 1];
            j--;
        }
        symtab[j] = symb;
        i++;
    }
}

Elf64_Shdr *find_section_header_by_type64(uint32_t flag, Elf64_Shdr *section_header_tab, int section_count, int is_little_endian)
{
    for (int i = 0; i < section_count; i++)
    {
        uint32_t sh_type = read_uint32(section_header_tab[i].sh_type, is_little_endian);
        if (sh_type == flag)
        {
            return &section_header_tab[i];
        }
    }
    return NULL;
}

Elf64_Shdr *find_section_header_by_index64(uint16_t index, Elf64_Shdr *section_header_tab, uint16_t section_count)
{
    if (index >= section_count)
    {
        return NULL;
    }
    return &section_header_tab[index];
}



char determine_symbol_type64(const Elf64_Sym *sym, Elf64_Shdr *section_header_tab, const char *shstrtab_section, const char *symb_name, uint16_t shnum, int is_little_endian)
{
    unsigned char type = sym->st_info & 0xf;
    unsigned char bind = sym->st_info >> 4;
    (void)symb_name;


       char type_char = 'U';
    switch (type)
    {
        case STT_NOTYPE:
            type_char = 'U';
            break;
        case STT_OBJECT:
            type_char = 'D';
            break;
        case STT_FUNC:
            type_char = 'T';
            break;
        case STT_SECTION:
            type_char = 'S';
            break;
        case STT_FILE:
            type_char = 'f';
            break;
        case STT_COMMON:
            type_char = 'C';
            break;
        case STT_TLS:
            type_char = 'L';
            break;
        case 8:
            type_char = 'U';
            break;
        case 9:
            type_char = 'U';
            break;
        case STT_GNU_IFUNC:
            type_char = 'i';
            return type_char;
        case 11:
            type_char = 'U';
            break;
        case 12:
            type_char = 'E';
            break;
        case 13:
            type_char = 'P';
            break;
    }

    uint16_t st_shndx = read_uint16(sym->st_shndx, is_little_endian);

    if (st_shndx == SHN_UNDEF)
    {
        type_char = 'U';
    }
    if (st_shndx != SHN_ABS)
    {
        if (st_shndx > shnum)
            return 'U';
        const char *name = find_section_name64(section_header_tab, shstrtab_section, st_shndx, shnum, is_little_endian);
        if (!strcmp(".rodata", name))
            type_char = 'R';
        else if (!strcmp(".data", name))
            type_char = 'D';
        else if (!strcmp(".note.ABI-tag", name))
            type_char = 'R';
        else if (!strcmp(".bss", name))
            type_char = 'B';
        else
        {
            Elf64_Shdr *section = find_section_header_by_index64(st_shndx, section_header_tab, shnum);
            uint64_t flags = read_uint64(section->sh_flags, is_little_endian);
            uint32_t sh_type = read_uint32(section->sh_type, is_little_endian);

            if (flags & SHF_EXECINSTR)
            {
                type_char = 'T';
            }
            else if (flags & SHF_ALLOC)
            {
                if (flags & SHF_WRITE)
                    type_char = 'D';
                else
                    type_char = 'R';
            }
            if (section && sh_type == SHT_NOBITS)
                type_char = 'B';
        }
    }
    else
        type_char = 'A';

    if (type == STT_OBJECT)
    {
        const char *name = find_section_name64(section_header_tab, shstrtab_section, st_shndx, shnum, is_little_endian);
        if (name && !strcmp(".bss", name))
            type_char = 'B';
    }
    if (type == STT_GNU_IFUNC)
        type_char = 'I';
    if (bind == STB_WEAK)
    {
        if (type == STT_OBJECT)
            return 'V';
        if (st_shndx == SHN_UNDEF || st_shndx == SHN_ABS)
            return 'w';
        return 'W';
    }
    if (type_char == 'U') return 'U';

    return (bind == STB_LOCAL) ? ft_tolower(type_char) : ft_toupper(type_char);
}


void display_symbol_info64(const Elf64_Sym *symb_tab, size_t sym_tab_size, const char *sym_str_tab, Elf64_Shdr *section_header_tab, const char *shstrtab_section, uint16_t shnum, size_t sym_str_tab_size, int is_little_endian)
{
    Elf64_Off addr; 
    short int zero_number = 16;
    for (size_t i = 0; i < (sym_tab_size / sizeof(Elf64_Sym)); i++) 
    {
        uint32_t st_name = read_uint32(symb_tab[i].st_name, is_little_endian);
        if (st_name == 0)
            continue;
        char symbol_type = determine_symbol_type64(&symb_tab[i], section_header_tab, shstrtab_section, sym_str_tab+ (Elf64_Off)symb_tab[i].st_name, shnum, is_little_endian);
        // Skip file symbols
        if (symbol_type == 'f' || symbol_type == 'F')
            continue;
        // Skip absolute symbols with a value of 0
        if ((symbol_type == 'a' || symbol_type == 'A') && read_uint64(symb_tab[i].st_value, is_little_endian) == 0)
            continue;
        uint64_t st_value = read_uint64(symb_tab[i].st_value, is_little_endian);
        // Dont print address for undefined symbols
        if (st_value != 0 && symbol_type != 'U' && symbol_type != 'w')
        {
            addr =  st_value;
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
            ft_printf("%x ", st_value);
        }
        else
            ft_printf("                 ");
        ft_printf("%c ", symbol_type);
        if (st_name != 0)
        {
            const char *symb_addr = sym_str_tab + st_name;
            const char *end = sym_str_tab + sym_str_tab_size;
            while (symb_addr < end && *symb_addr != '\0')
            {
                symb_addr++;
            }
            if (symb_addr == end)
                ft_printf("%s", "(null)");
            else
                ft_printf("%s", (char *)(sym_str_tab + st_name));
        }
        ft_printf("\n");
    }

}

int ft_check_endianness64(Elf64_Ehdr *ehdr)
{
    if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
        return (1);
    else
        return (0);
}


void parse_64_bits(Elf64_Ehdr *ehdr, MappedFile mapped_file, char *file_name, int print_file_name)
{
    int is_little_endian = ft_check_endianness64(ehdr);

    if (ft_check_offset64(ehdr, mapped_file.size, is_little_endian))
    {
        ft_dprintf("ft_nm: %s: file format not recognized\n", file_name);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    if (ft_check_section_numbers64(ehdr, mapped_file.size, is_little_endian))
    {
        ft_dprintf("ft_nm: %s: file format not recognized\n", file_name);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }

    uint16_t index_section_header_sections_names = read_uint16(ehdr->e_shstrndx, is_little_endian);
    uint64_t section_header_tab_addr_offset = read_uint64(ehdr->e_shoff, is_little_endian);

    if (section_header_tab_addr_offset >= mapped_file.size) {
        ft_dprintf("Invalid section section_header_tab_addr_offset\n", NULL);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    Elf64_Shdr *section_header_tab = (Elf64_Shdr *)((char *)(ehdr) + section_header_tab_addr_offset);
    Elf64_Shdr *section_header_shstrtab = &section_header_tab[index_section_header_sections_names];
    uint64_t section_shstrtab_offset = read_uint64(section_header_shstrtab->sh_offset, is_little_endian);
    if (section_shstrtab_offset >= mapped_file.size) {
        ft_dprintf("Invalid section section_shstrtab_offset\n", NULL);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    char *section_shstrtab = (char *)ehdr + section_shstrtab_offset;

    // Find the symbol table section header
    uint16_t shnum = read_uint16(ehdr->e_shnum, is_little_endian);
    Elf64_Shdr *sym_tab_section_header = find_section_header_by_type64(SHT_SYMTAB, section_header_tab, shnum, is_little_endian);

    if (!sym_tab_section_header)
    {
        ft_dprintf("ft_nm: %s: no symbols\n", file_name);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    uint64_t symb_tab_offset = read_uint64(sym_tab_section_header->sh_offset, is_little_endian);
    if (symb_tab_offset >= mapped_file.size) {
        ft_dprintf("Invalid section symb tab offset\n", NULL);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    Elf64_Sym *sym_tab = (Elf64_Sym *)((char *)ehdr + symb_tab_offset);

    // Get the string table for the symbol names
    uint32_t sh_link = read_uint32(sym_tab_section_header->sh_link, is_little_endian);
    Elf64_Shdr *str_tab_header = &section_header_tab[sh_link];
    if (!str_tab_header)
    {
        ft_dprintf("ft_nm: %s: no symbols\n", file_name);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    uint64_t symb_str_offset = read_uint64(str_tab_header->sh_offset, is_little_endian);
    if (symb_str_offset >= mapped_file.size) {
        ft_dprintf("Invalid section symb str offset\n", NULL);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    uint64_t sym_tab_size = read_uint64(sym_tab_section_header->sh_size, is_little_endian);
    char *sym_str_tab = (char *)ehdr + symb_str_offset;

    // Copy and sort the symbol table
    Elf64_Sym *symtab_copy = malloc(sym_tab_size);
    if (!symtab_copy)
    {
        perror("malloc");
        munmap(mapped_file.mapped, mapped_file.size);
        exit(EXIT_FAILURE);
    }
    ft_memcpy(symtab_copy, sym_tab, sym_tab_size);
    sort_sym_tab64(symtab_copy, sym_tab_size / sizeof(Elf64_Sym), sym_str_tab, read_uint64(str_tab_header->sh_size, is_little_endian), is_little_endian);
    if (print_file_name == 1)
        ft_printf("\n%s:\n", file_name);
    display_symbol_info64(symtab_copy, sym_tab_size, sym_str_tab, section_header_tab, section_shstrtab, shnum, read_uint64(str_tab_header->sh_size, is_little_endian), is_little_endian);
    free(symtab_copy);
    munmap(mapped_file.mapped, mapped_file.size);
}