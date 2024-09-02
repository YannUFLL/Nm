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


typedef u_int32_t Elf64_Word; 
typedef u_int64_t Elf64_Addr; 
typedef u_int16_t Elf64_Half; 
typedef u_int64_t Elf64_Xword;

#define SH_OFFSET 0x18

typedef struct {
    Elf64_Word st_name;
    unsigned char st_info;
    unsigned char st_other;
    Elf64_Half st_shndx;
    Elf64_Addr st_value;
    Elf64_Xword st_size;
} Elf64_Sym;

// char* find_associated_section(st_shndx, )
// {

// }

char determine_symbol_type(const Elf64_Sym *sym)
{
    if (sym->st_shndx == 0)
        return 'U';

    unsigned char type = sym->st_info & 0xf;
    unsigned char bind = sym->st_info >> 4;

    static const char type_chars[] = {'U', 'D', 'T', 'S', 'f', 'C', 'L', 'o', 'U', 'U', 'O', 'U', 'E', 'P'};
    char type_char = (type < sizeof(type_chars) / sizeof(type_chars[0])) ? type_chars[type] : 'U';

    if (type_char == 'U') return 'U';
    return (bind == 0) ? ft_tolower(type_char) : ft_toupper(type_char);
}


void *findSectionHeader(void *section_headers_start_adress, void *shstrtab_section, const char *section_name)
{
    void *section = section_headers_start_adress;
    // write(1, shstrtab_section, 100);
    while (strcmp(shstrtab_section + *(u_int32_t *)section , section_name) != 0)
    {
        section = section + 0x40;
    }
    return (section);
}

 int ft_strcmp(const char *str1, const char *str2 )
{
    int i = 0;

    while (str1[i] && str2[i])
    {
        if (str1[i] != str2[i])
        {
            return ((unsigned char)str1[i] - (unsigned char)str2[i]);
        }
        i++;
    }
    return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

void sortSymTab(Elf64_Sym *symtab, u_int64_t symtab_size,char *sym_str_tab)
{
    u_int64_t i = 1;
    u_int64_t j = 0;
    Elf64_Sym symb;

    while (i < symtab_size)
    {
        j = i;
        symb = symtab[i];
        while (j > 0 && ft_strcmp(sym_str_tab+ (symb.st_name),  sym_str_tab+ (symtab[j - 1].st_name)) <= 0)
        {
            symtab[j] = symtab[j - 1];
            j--;
        }
        symtab[j] = symb;
        i++;
    }
}

void display_symbol_info(const Elf64_Sym *symtab_copy, size_t sym_tab_size, const char *sym_str_tab)
{
    u_int64_t addr; 
    short int zero_number = 16;
    for (size_t i = 0; i < sym_tab_size; i++) 
    {
        char symbol_type = determine_symbol_type(&symtab_copy[i]);
        if (symbol_type == 'f')
            continue;
        if (symtab_copy[i].st_value != 0)
        {
            addr =  symtab_copy[i].st_value;
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
            ft_printf("%x ", (char *)(u_int64_t)symtab_copy[i].st_value);
        }
        else
        {
            ft_printf("                 ");
            ft_printf("%c ", symbol_type);
        }
        if (symtab_copy[i].st_name != 0)
        {
            ft_printf("%s", (char *)(sym_str_tab+ (u_int64_t)symtab_copy[i].st_name));
        }
        ft_printf("\n");
    }

}

u_int64_t *get_section_offset(u_int64_t *section_shstrtab, void *section_header_tab_addr, const char *session_name)
{
    void *sym_tab_section_header = findSectionHeader(section_header_tab_addr, section_shstrtab, session_name);
    return(*(u_int64_t **)(sym_tab_section_header + SH_OFFSET));
}

void *get_mapped_file_memory(const char * file_name)
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
    return (mapped);
}


int main(int argc, char **argv)
{
    if (argc == 1)
    {
       (void)argc; 
    }

    void * mapped = get_mapped_file_memory(argv[1]);
    // ELF documentation : 0x28 e_shoff	Points to the start of the section header table. We retrieve the adress of the section header table here.
    void *section_header_tab_addr = *(void **)(mapped + 0x28);
    // ELF documentation : 0x3E e_shstrndx	Contains index of the section header table entry that point to the section section names.
    short int section_header_sections_names = *(short int *)(mapped + 0x3E);

    // a section header is 64 bytes long (0x40) and the position of the section in the file is indicate in the offset SH_OFFSET in the section header  
    void *section_shstrtab = mapped + *(u_int64_t *)(mapped + (u_int64_t)section_header_tab_addr + section_header_sections_names * 0x40 + SH_OFFSET);

    void *sym_tab_section_header = findSectionHeader(mapped + (u_int64_t)section_header_tab_addr, section_shstrtab, ".symtab");
    void *symb_tab_offset = *(u_int64_t **)(sym_tab_section_header + SH_OFFSET);
    Elf64_Sym *sym_tab = mapped + (u_int64_t)symb_tab_offset;
    u_int64_t *symb_str_offset  = get_section_offset(section_shstrtab, mapped + (u_int64_t)section_header_tab_addr, ".strtab");
    u_int64_t sym_tab_size = *(u_int64_t *)(sym_tab_section_header + 0x20);
    void *sym_str_tab= mapped + (u_int64_t)symb_str_offset;

    
    Elf64_Sym *symtab_copy = malloc(sym_tab_size);
    ft_memcpy(symtab_copy, sym_tab, sym_tab_size);
    ft_strlen((const char *)sym_tab);
    sortSymTab(symtab_copy, sym_tab_size / sizeof(Elf64_Sym), sym_str_tab);
    display_symbol_info(symtab_copy, sym_tab_size, sym_str_tab);
}