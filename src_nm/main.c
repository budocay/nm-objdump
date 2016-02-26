/*
** main.c for main in /home/lina_a/rendu/B4/PSU_2016_nmobjdump/src_nm
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Sun Feb 21 20:06:46 2016 lina_a
** Last update Sun Feb 21 20:06:46 2016 lina_a
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include "nm.h"

char                print_char_elf2(Elf64_Sym sym, Elf64_Shdr *shdr)
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

char                print_char_elf(Elf64_Sym sym, Elf64_Shdr *shdr)
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
   else if (print_char_elf2(sym, shdr) != '\0')
        c = print_char_elf2(sym, shdr);
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
        c += 32;
    return c;
}

void                print_sec_and_sym(Elf64_Sym sym, void *data,
				      Elf64_Shdr *shdr)
{
    if (sym.st_name != 0)
    {
        if (sym.st_value != 0 && sym.st_info != STT_FILE)
            printf("%016x %c %s\n", (unsigned int) sym.st_value,
                   print_char_elf(sym, shdr),
                   (char *) (data + shdr->sh_offset + sym.st_name));
        else if (sym.st_info != STT_FILE)
            printf("%16s %c %s\n", " ", print_char_elf(sym, shdr),
                   ((char *)(data + shdr->sh_offset + sym.st_name)));
    }
}

char                *my_nm(void *data, Elf64_Ehdr *elf)
{
    unsigned int             idx;
    Elf64_Shdr		*shdr;
    Elf64_Sym       sym;
    Elf64_Shdr		*pShdr;
    char            *str;

    idx = 0;
    shdr = (Elf64_Shdr*)(data + elf->e_shoff);
    str = (char*)(data + shdr[elf->e_shstrndx].sh_offset);
    if ((pShdr = set_sym_tab(&shdr, str, elf, shdr)) == NULL)
        return (NULL);
    while (idx < (pShdr->sh_size / pShdr->sh_entsize))
    {
        sym = ((Elf64_Sym*)(data + pShdr->sh_offset))[idx];
        print_sec_and_sym(sym, data, shdr);
        idx++;
    }
  return (0);
}

int   main(int ac, char **av)
{
  int i;
  int fd;

  i = 0;
  if (ac >= 2)
  {
    while (++i < ac)
    {
      if ((fd = open(av[i], O_RDONLY)) > 0)
          check_file(fd, av[i]);
      close(fd);
    }
  }
  else
      dprintf(STDERR_FILENO,"/usr/bin/nm 'a.out' : No such file\n");
  return (0);
}
