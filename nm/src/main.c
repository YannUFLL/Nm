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

typedef struct {
    Elf64_Word st_name;
    unsigned char st_info;
    unsigned char st_other;
    Elf64_Half st_shndx;
    Elf64_Addr st_value;
    Elf64_Xword st_size;
} Elf64_Sym;

char determine_symbol_type(unsigned char st_info)
{
    unsigned char type = st_info & 0xf;
    unsigned char bind = st_info >> 4;

    switch (type)
    {
        case 0: 
            return 'U';
        case 1: 
            return (bind == 0) ? 'b' : 'B';
        case 2: 
            return (bind == 0) ? 't' : 'T';
        case 3: 
            return 'S';
        case 4:   
            return 'f';
        case 5:
            return 'C';
        case 6: 
            return (bind == 0) ? 'l' : 'L';
        case 10: 
            return (bind == 0) ? 'o' : 'O';
        case 12: 
            return (bind == 0) ? 'e' : 'E';
        case 13: return 'P';
            return (bind == 0) ? 'p' : 'P';
        case 15: return 'P';
            return (bind == 0) ? 'p' : 'P';
        default: return 'U';
    }
}

void *findSectionHeader(void *section_headers_start_adress, void *shstrtab_section, char *section_name)
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

void sortSymTab(Elf64_Sym *symtab, u_int64_t symtab_size,char *sym_str)
{
    u_int64_t i = 1;
    u_int64_t j = 0;
    Elf64_Sym symb;

    while (i < symtab_size)
    {
        j = i;
        symb = symtab[i];
        while (j > 0 && ft_strcmp(sym_str + (symb.st_name),  sym_str + (symtab[j - 1].st_name)) <= 0)
        {
            symtab[j] = symtab[j - 1];
            j--;
        }
        symtab[j] = symb;
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
       (void)argc; 
    }

    int fd = open(argv[1], O_RDONLY);
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
    // ELF documentation : 0x28 e_shoff	Points to the start of the section header table.
    void *section_table_addr = *(void **)(mapped + 0x28);
    // ELF documentation : 0x3E e_shstrndx	Contains index of the section header table entry that contains the section names.
    short int index_header_tab_entry = *(short int *)(mapped + 0x3E);

    // a section header is 64 bytes long (0x40) and the position of the section in the file is indicate in the offset 0x18 in the section header  
    void *section_shstrtab = mapped + *(u_int64_t *)(mapped + (u_int64_t)section_table_addr + index_header_tab_entry * 0x40 + 0x18);

    void *sym_tab_section_header = findSectionHeader(mapped + (u_int64_t)section_table_addr, section_shstrtab, ".symtab");
    void *symb_tab_offset = *(u_int64_t **)(sym_tab_section_header + 0x18);
    printf(" symtab OFFSET %p \n", symb_tab_offset);
    Elf64_Sym *sym_tab = mapped + (u_int64_t)symb_tab_offset;
    void *sym_str_section_header = findSectionHeader(mapped + (u_int64_t)section_table_addr, section_shstrtab, ".strtab");
    void *symb_str_offset = *(u_int64_t **)(sym_str_section_header + 0x18);
    u_int64_t sym_tab_size = *(u_int64_t *)(sym_tab_section_header + 0x20);
    printf("SIZE : %ld \n", sym_tab_size);
    void *sym_str = mapped + (u_int64_t)symb_str_offset;
    long unsigned int i = 0; 
    printf("%ld \n", sym_tab_size / sizeof(Elf64_Sym));

    
    Elf64_Sym *symtab_copy = malloc(sym_tab_size);
    ft_memcpy(symtab_copy, sym_tab, sym_tab_size);
    ft_strlen((const char *)sym_tab);
    sortSymTab(symtab_copy, sym_tab_size / sizeof(Elf64_Sym), sym_str);




    
    u_int64_t addr; 
    short int zero_number = 16;
    while (i < sym_tab_size / sizeof(Elf64_Sym))
    {
        if (determine_symbol_type(symtab_copy[i].st_info) == 'f')
        {
            i++;
            continue;
        }
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
            ft_printf("                 ");
        ft_printf("%c ", determine_symbol_type(symtab_copy[i].st_info));
        if (symtab_copy[i].st_name != 0)
        {
            ft_printf("%s", (char *)(sym_str + (u_int64_t)symtab_copy[i].st_name));
        }
        ft_printf("\n");
        i++;
    }
}