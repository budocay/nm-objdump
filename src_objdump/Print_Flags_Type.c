/*
** Print_Flags_Type.c for print_flags in /home/lina_a/rendu/B4/PSU_2016_nmobjdump/src_objdump
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Sun Feb 21 20:03:58 2016 lina_a
** Last update Sun Feb 21 20:03:58 2016 lina_a
*/

#include <elf.h>
#include <stdio.h>
#include <string.h>
#include "objdump.h"

void	    is_sym_tab(char *str, Elf64_Shdr *shdr, int i, int flag)
{
  if (strcmp(&str[shdr[i].sh_name], ".symtab") == 0 && flag == 0)
    printf("HAS_SYMS, ");
  else if (strcmp(&str[shdr[i].sh_name], ".symtab") == 0 && flag == 1)
    printf("HAS_SYMS");
}

void        print_flags64(Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *str)
{
    int     i;
    int     flag;

    i = -1;
    flag = 0;
    if (elf->e_type == ET_CORE)
        printf("CORE, ");
    if (elf->e_type == ET_EXEC)
        printf("EXEC_P, ");
    if (elf->e_type == ET_REL)
    {
        printf("HAS_RELOC, ");
        flag = 1;
    }
    while (++i < elf->e_shnum)
      is_sym_tab(str, shdr, i, flag);
    if (elf->e_type == ET_DYN)
        printf("DYNAMIC, ");
    if (elf->e_phnum != 0)
        printf("D_PAGED");
    putchar('\n');
}

void        print_flags32(Elf32_Ehdr *elf, Elf32_Shdr *shdr, char *str)
{
    int     i;

    i = -1;
    if (elf->e_type == ET_CORE)
        printf("CORE, ");
    if (elf->e_type == ET_EXEC)
        printf("EXEC_P, ");
    if (elf->e_type == ET_REL)
        printf("HAS_RELOC, ");
    while (++i < elf->e_shnum)
        if (strcmp(&str[shdr[i].sh_name], ".symtab") == 0)
            printf("HAS_SYMS, ");
    if (elf->e_type == ET_DYN)
        printf("DYNAMIC, ");
    if (elf->e_phnum != 0)
        printf("D_PAGED");
    putchar('\n');
}
