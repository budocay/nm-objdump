/*
** main.c for main.c in /home/lina_a/rendu/B4/PSU_2016_nmobjdump/src_objdump
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Sun Feb 21 20:09:19 2016 lina_a
** Last update Sun Feb 21 20:09:19 2016 lina_a
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/objdump.h"

int        found_flag(char *str, Elf64_Shdr *shdr, Elf64_Ehdr *elf)
{
 return (flags_to_found64(elf, shdr, str));
}

void			print_val(unsigned int j, unsigned int *z,
				    unsigned char *to_print, char *print)
{
    unsigned    int    	x;

    x = j;
    while (x % 16 != 0)
      {
        if (x % 4 == 0 && x % 16)
	  putchar(' ');
        printf("  ");
        ++x;
      }
    printf("  ");
    while (*z < j)
      {
        if (isprint(to_print[*z]))
	  putchar(print[*z]);
        else
	  printf(".");
        (*z)++;
      }
    while ((*z)++ % 16 != 0)
      putchar(' ');
    *z = j;
    putchar('\n');
}

void				section_to_print(char *data, Elf64_Ehdr *elf,
						 Elf64_Shdr *shdr, int cmpt)
{
    unsigned char		*to_print;
    unsigned int		inc;
    int			        addr;
    unsigned int		z;

    addr = (int) shdr[cmpt].sh_addr;
    if (section_not_printable(data, shdr, cmpt) == true);
    else
    {
        printf("Contents of section %s:\n", &data[shdr[cmpt].sh_name]);
        to_print = (unsigned char *) ((char *) elf + shdr[cmpt].sh_offset);
        inc = 0;
        z = 0;
        while (inc < shdr[cmpt].sh_size)
        {
            if (inc % 16 == 0)
                printf(" %04x ", addr);
            printf("%02x", to_print[inc]);
            inc++;
            if (inc % 4 == 0 && inc % 16 != 0 && inc < shdr[cmpt].sh_size)
                printf(" ");
            if (inc % 16 == 0)
                addr += 16;
            if (inc % 16 == 0 || inc >= shdr[cmpt].sh_size)
                print_val(inc, &z, to_print, (char *) to_print);
        }
    }
}

void        objdump_flag_s(char *str, Elf64_Ehdr *elf, Elf64_Shdr *shdr)
{
    int     cmpt;

    cmpt = 0;
    while (cmpt < elf->e_shnum)
    {
      if (shdr[cmpt].sh_size
	  && strcmp(&str[shdr[cmpt].sh_name], ".strtab")
	  && strcmp(&str[shdr[cmpt].sh_name], ".symtab")
	  && strcmp(&str[shdr[cmpt].sh_name], ".shstrtab")
	  && strcmp(&str[shdr[cmpt].sh_name], ".bss"))
	section_to_print(str, elf, shdr, cmpt);
      cmpt++;
    }
}

int         main(int ac, char **av)
{
    int     fd;
    int     i;

    if (ac > 1)
      {
        i = 0;
        while (++i < ac)
	    {
            if ((fd = open(av[i], O_RDONLY)) > 0)
	            check_data(fd, av[i]);
            close(fd);
	    }
      }
    else
      dprintf(STDERR_FILENO, "Usage: ./my_objdump <binary file>\n");
    return (0);
}
