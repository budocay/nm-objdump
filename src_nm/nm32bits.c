/*
** nm32bits.c for nm32 in /home/lina_a/rendu/B4/PSU_2015_nmobjdump/src_nm
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Fri Feb 26 13:51:14 2016 lina_a
** Last update Fri Feb 26 13:51:14 2016 lina_a
*/

#include <string.h>
#include <stdio.h>
#include "nm.h"

Elf32_Shdr	*set_sym_tab32bits(Elf32_Shdr **string_sec, char *str,
				   Elf32_Ehdr *elf,
				   Elf32_Shdr *shdr)
{
    int			i;
    Elf32_Shdr		*symsection;

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
void                print_sec_and_sym32bits(Elf32_Sym sym, void *data,
					    Elf32_Shdr *shdr)
{
    if (sym.st_name != 0)
    {
        if (sym.st_value != 0 && sym.st_info != STT_FILE)
            printf("%016x %c %s\n", (unsigned int) sym.st_value,
                   print_char_elf32bits(sym, shdr),
                   (char *) (data + shdr->sh_offset + sym.st_name));
        else if (sym.st_info != STT_FILE)
            printf("%16s %c %s\n", " ", print_char_elf32bits(sym, shdr),
                   ((char *)(data + shdr->sh_offset + sym.st_name)));
    }
}

char                print_char_elf32bits2(Elf32_Sym sym, Elf32_Shdr *shdr)
{
    char            c;

    c = '\0';
    if (sym.st_shndx == SHN_ABS)
        c = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        c = 'C';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        c = 'R';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        c = 'D';
    else
        c = '?';
    return c;
}

char                print_char_elf32bits(Elf32_Sym sym, Elf32_Shdr *shdr)
{
    char            c;

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
    {
        c ='W';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'w';
    }
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
             ELF64_ST_BIND(sym.st_info) == STT_OBJECT)
    {
        c = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'v';
    }
    else if (sym.st_shndx == SHN_UNDEF)
        c = 'U';
    else if (print_char_elf32bits2(sym, shdr) != '\0')
        c = print_char_elf32bits2(sym, shdr);
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
        c += 32;
    return c;
}
