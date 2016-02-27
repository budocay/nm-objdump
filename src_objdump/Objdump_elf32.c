/*
** main.c for main in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Mon Feb 15 19:40:48 2016 lina_a
** Last update Mon Feb 15 19:40:48 2016 lina_a
*/

#include <stdio.h>
#include <elf.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "objdump.h"

int        found_flag_elf_32(char *str, Elf32_Shdr *shdr, Elf32_Ehdr *elf)
{
    return (flags_to_found32(elf, shdr, str));
}

void			print_ascii_elf_32(unsigned int j, unsigned int *z,
					   unsigned char *w, char *t)
{
    int			x;

    x = j;
    while (x % 16 != 0)
      {
	if (x % 4 == 0 && x % 16)
	  printf(" ");
        printf("  ");
        ++x;
      }
    printf("  ");
    while (*z < j)
      {
        isprint(w[*z]) ? putchar(t[*z]) : putchar('.');
        (*z)++;
      }
    while ((*z)++ % 16 != 0)
      printf(" ");
    *z = j;
    printf("\n");
}

void				section_to_print_elf_32(char *data,
							Elf32_Ehdr *elf,
							Elf32_Shdr *shdr,
							int cmpt)
{
    unsigned char		*w;
    unsigned int		j;
    int			        addr;
    unsigned int		z;

    addr = (int) shdr[cmpt].sh_addr;
    printf("Contents of section %s:\n", &data[shdr[cmpt].sh_name]);
    w = (unsigned char*)((char*)elf + shdr[cmpt].sh_offset);
    j = 0;
    z = 0;
    while (j < shdr[cmpt].sh_size)
      {
        if (j % 16 == 0)
	  printf(" %04x ", addr);
        printf("%02x", w[j++]);
        if (j % 4 == 0 && j % 16 && j < shdr[cmpt].sh_size)
	  printf(" ");
        if (j % 16 == 0)
            addr += 16;
        if (j % 16 == 0 || j >= shdr[cmpt].sh_size)
	  print_ascii_elf_32(j, &z, w, (char*)w);
      }
}

void        objdump_flag_s_elf_32(char *str, Elf32_Ehdr *elf, Elf32_Shdr *shdr)
{
    int     cmpt;

    cmpt = 0;
    while (cmpt < elf->e_shnum)
      {
        if (shdr[cmpt].sh_size
            || strcmp(&str[shdr[cmpt].sh_name], ".strtab") == 0
            || strcmp(&str[shdr[cmpt].sh_name], ".symtab") == 0
            || strcmp(&str[shdr[cmpt].sh_name], ".shstrtab") == 0
            || strcmp(&str[shdr[cmpt].sh_name], ".bss") == 0)
	  section_to_print_elf_32(str, elf, shdr, cmpt);
        cmpt++;
      }
}

int		my_objdump_elf_32(void *data, char *file)
{
    Elf32_Ehdr  *elf;
    Elf32_Shdr  *shdr;
    char        *str;

    elf = (Elf32_Ehdr *)data;
    shdr = (Elf32_Shdr *)(data + elf->e_shoff);
    str = (char*)(data + shdr[elf->e_shstrndx].sh_offset);
    if (str == NULL)
      printf("tata");
    if (elf->e_machine == EM_386)
      {
        printf("\n%s:%5cfile format %s\n", file, ' ', ELF_32);
        printf("architecture: %s, flags 0x%08d:\n", INTEL_32,
               found_flag_elf_32(str, shdr, elf));
      }
    print_flags32(elf, shdr, str);
    printf("start address 0x%08x\n\n", (int)elf->e_entry);
    objdump_flag_s_elf_32(str, elf, shdr);
    return (0);
}
