//
// Created by lina_a on 25/02/16.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <elf.h>
#include <bits/string2.h>
#include "../include/objdump.h"
#include "../include/nm.h"

Elf64_Shdr	*set_sym_tab(Elf64_Shdr **string_sec, char *str, Elf64_Ehdr *elf,
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
    Elf64_Ehdr  *elf;
    Elf32_Ehdr  *elf32;

    if (check_header(((Elf64_Ehdr*)data)) != -1)
    {
        elf = (Elf64_Ehdr*)data;
        if (elf->e_ident[EI_CLASS] == ELFCLASS64)
            my_nm(data, elf);
    }
    else if (check_header_elf_32(((Elf32_Ehdr*)data)) != -1)
    {
        elf32 = (Elf32_Ehdr*)data;
        if (elf32->e_ident[EI_CLASS] == ELFCLASS32)
            my_nm_32(data, name_file);
    }
    else
    {
        dprintf(STDERR_FILENO, "Unsuported ELFCLASS\n");
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
    if (verification(av) == NULL)
    {
        dprintf(STDERR_FILENO,"nm: %s: File truncated\n", av);
        close(fd);
        return;
    }
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