/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:04:33 by ydumaine          #+#    #+#             */
/*   Updated: 2024/12/19 19:05:06 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char *ignore_underscore(char *name)
{
    int i = 0; 
    while (name[i] == '_' && name[i])
        i++;
    return (&name[i]);
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

int ft_check_header(Elf_Generic_Ehdr *ehdr)
{
    if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr->e_ident[EI_MAG1] != ELFMAG1 || 
        ehdr->e_ident[EI_MAG2] != ELFMAG2 || 
        ehdr->e_ident[EI_MAG3] != ELFMAG3)
        {
            return (EXIT_FAILURE);
        }
    if (ehdr->e_ident[EI_CLASS] == ELFCLASSNONE)
    {
        return (EXIT_FAILURE);
    }
    if (ehdr->e_ident[EI_DATA] == ELFDATANONE)
    {
        return (EXIT_FAILURE);
    }    
    return (0);
}

void parse_elf_file(char *file_name, int print_file_name)
{
    MappedFile mapped_file = get_mapped_file_memory(file_name);
    Elf_Generic_Ehdr *ehdr = (Elf_Generic_Ehdr *)mapped_file.mapped;
    if (ft_check_header(ehdr))
    { 
        ft_printf("ft_nm: %s: File format not recognized\n", file_name);
        munmap(mapped_file.mapped, mapped_file.size);
        return;
    }
    if (ehdr->e_ident[EI_CLASS] == ELFCLASS32)
    {
        Elf32_Ehdr *ehdr32 = (Elf32_Ehdr *)mapped_file.mapped;
        parse_32_bits(ehdr32, mapped_file, file_name, print_file_name);
        return;
    }
    else if (ehdr->e_ident[EI_CLASS] == ELFCLASS64)
    {
        Elf64_Ehdr *ehdr64 = (Elf64_Ehdr *)mapped_file.mapped;
        parse_64_bits(ehdr64, mapped_file, file_name, print_file_name);
    }
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
