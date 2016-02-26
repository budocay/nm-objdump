/*
** verify_header.c for verify header in /home/lina_a/rendu/B4/PSU_2016_nmobjdump/src_objdump
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Sat Feb 20 12:20:16 2016 lina_a
** Last update Sat Feb 20 12:20:16 2016 lina_a
*/

#include <stdio.h>
#include <unistd.h>
#include <elf.h>
#include <stdlib.h>
#include "../include/objdump.h"

int         check_header_elf_32(Elf32_Ehdr *data)
{
    if (data->e_ident[EI_MAG0] != ELFMAG0 ||
        data->e_ident[EI_MAG1] != ELFMAG1 ||
        data->e_ident[EI_MAG2] != ELFMAG2 ||
        data->e_ident[EI_MAG3] != ELFMAG3 ||
        (data->e_type != ET_EXEC && data->e_type != ET_REL
        && data->e_type != ET_DYN && data->e_type != ET_CORE))
        return (-1);
    if (data->e_ident[EI_CLASS] != ELFCLASS32)
        return (-1);
    if (data->e_type == ET_NONE)
        exit(EXIT_SUCCESS);
    return (0);
}

int        check_header(Elf64_Ehdr *data)
{
    if (data->e_ident[EI_MAG0] != ELFMAG0 ||
        data->e_ident[EI_MAG1] != ELFMAG1 ||
        data->e_ident[EI_MAG2] != ELFMAG2 ||
        data->e_ident[EI_MAG3] != ELFMAG3 ||
        (data->e_type != ET_EXEC && data->e_type != ET_REL
        && data->e_type != ET_DYN && data->e_type != ET_CORE))
        return (-1);
    if (data->e_ident[EI_CLASS] != ELFCLASS64)
        return (-1);
    if (data->e_type == ET_NONE)
        exit(EXIT_SUCCESS);
    return (0);
}