/*
** check_set_tab.c for check_set_tab in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Fri Feb 26 13:55:12 2016 lina_a
** Last update Fri Feb 26 13:55:12 2016 lina_a
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "objdump.h"
#include "nm.h"

void        check_truncated_file(char *name_file, int fd)
{
    if (verification(name_file) == NULL)
    {
        dprintf(STDERR_FILENO, "/usr/bin/nm: %s: File truncated\n",
                name_file);
        close(fd);
	exit(EXIT_SUCCESS);
    }
}

Elf64_Shdr	*set_sym_tab(Elf64_Shdr **string_sec, char *str,
			     Elf64_Ehdr *elf,
			     Elf64_Shdr *shdr)
{
    int			i;
    Elf64_Shdr		*symsection;

    symsection = NULL;
    *string_sec = NULL;
    i = 0;
    while (i < elf->e_shnum)
    {
        if (shdr[i].sh_size)
        {
            if (!strcmp(&str[shdr[i].sh_name], ".symtab"))
                symsection = &shdr[i];
            if (!strcmp(&str[shdr[i].sh_name], ".strtab"))
                *string_sec = &shdr[i];
        }
        i++;
    }
    return (symsection);
}

void		which_header_correct_is(void *data, char *name_file, int fd)
{
    Elf64_Ehdr *elf;
    Elf32_Ehdr *elf32;

    if (check_header((Elf64_Ehdr *) data) != -1)
    {
        check_truncated_file(name_file, fd);
        elf = (Elf64_Ehdr *) data;
        if (elf->e_ident[EI_CLASS] == ELFCLASS64)
            my_nm(data, elf);
    }
    else if (check_header_elf_32(((Elf32_Ehdr *) data)) != -1)
    {
        check_truncated_file(name_file, fd);
        elf32 = (Elf32_Ehdr *) data;
        if (elf32->e_ident[EI_CLASS] == ELFCLASS32)
            my_nm_32(data, elf32);
    }
    else
    {
        dprintf(STDERR_FILENO, "/usr/bin/nm: %s: File format not "
                "recognized\n", name_file);
        close(fd);
        exit(EXIT_SUCCESS);
    }
}

void    check_file(int fd, char *av)
{
    struct stat file;
    void *data;

    if ((fstat(fd, &file)) == -1)
        return;
    if ((data = mmap(NULL, (size_t) file.st_size, PROT_READ,
                     MAP_SHARED | MAP_FILE, fd, 0)) == MAP_FAILED)
    {
        dprintf(STDERR_FILENO, "%m\n");
        return;
    }
    which_header_correct_is(data, av, fd);
    if ((munmap(data, (size_t) file.st_size)) == -1)
    {
        dprintf(STDERR_FILENO, "%m\n");
        close(fd);
        return;
    }
}

char        *my_nm_32(void *data, Elf32_Ehdr *elf)
{
    unsigned int             idx;
    Elf32_Shdr		*shdr;
    Elf32_Sym       sym;
    Elf32_Shdr		*pShdr;
    char            *str;

    idx = 0;
    shdr = (Elf32_Shdr*)(data + elf->e_shoff);
    str = (char*)(data + shdr[elf->e_shstrndx].sh_offset);
    if ((pShdr = set_sym_tab32bits(&shdr, str, elf, shdr)) == NULL)
        return (NULL);
    while (idx < (pShdr->sh_size / pShdr->sh_entsize))
    {
        sym = ((Elf32_Sym*)(data + pShdr->sh_offset))[idx];
        print_sec_and_sym32bits(sym, data, shdr);
        idx++;
    }
    return (0);
}
