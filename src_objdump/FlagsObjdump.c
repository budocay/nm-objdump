/*
** FlagsObjdump.c for flagsobjdump in /home/lina_a/rendu/B4/PSU_2016_nmobjdump/src_objdump
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Sun Feb 21 20:03:47 2016 lina_a
** Last update Sun Feb 21 20:03:47 2016 lina_a
*/

#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/objdump.h"

int     flags_to_found32(Elf32_Ehdr *elf, Elf32_Shdr *shdr, char *str)
{
    int res;
    int i;

    i = -1;
    res = 0;
    if (elf->e_type == ET_EXEC)
        res += 0x02;
    if (elf->e_type == ET_REL)
        res += 0x01;
    while (++i < elf->e_shnum)
        if (strcmp(&str[shdr[i].sh_name], ".symtab") == 0)
            res += 0x10;
    if (elf->e_type == ET_DYN)
        res += 0x40;
    if (elf->e_phnum != 0)
        res += 0x100;
    return (res);
}

int     flags_to_found64(Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *str)
{
    int res;
    int i;

    i = -1;
    res = 0;
    if (elf->e_type == ET_EXEC)
        res += 0x02;
    if (elf->e_type == ET_REL)
        res += 0x01;
    while (++i < elf->e_shnum)
        if (strcmp(&str[shdr[i].sh_name], ".symtab") == 0)
            res += 0x10;
    if (elf->e_type == ET_DYN)
        res += 0x40;
    if (elf->e_phnum != 0)
        res += 0x100;
    return (res);
}