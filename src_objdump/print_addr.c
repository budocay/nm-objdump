/*
** print_addr.c for print in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Fri Feb 26 14:51:45 2016 lina_a
** Last update Fri Feb 26 14:51:45 2016 lina_a
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "objdump.h"

void	print_addr(int addr, unsigned int inc, unsigned char *to_print)
{
  if (inc % 16 == 0)
    printf(" %04x ", addr);
  printf("%02x", to_print[inc]);
}
