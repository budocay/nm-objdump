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
#include "../include/nm.h"

void                print_sec_and_sym(Elf64_Sym sym, void *data, Elf64_Shdr *shdr)
{
    if (sym.st_name != 0)
    {
        if (sym.st_value != 0)
            printf("%016x %s\n", (unsigned int) sym.st_value, (char *) (data + shdr->sh_offset + sym.st_name));
        else
            printf("%16s %s\n", " ", ((char *)(data + shdr->sh_offset + sym.st_name)));
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


void        my_nm_32(void *data, char *name_file)
{

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
      dprintf(STDERR_FILENO,"Usage: ./my_nm <binary>");
  return (0);
}
