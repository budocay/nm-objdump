/*
** nm.h for nm in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Fri Feb 26 14:44:01 2016 lina_a
** Last update Fri Feb 26 14:44:01 2016 lina_a
*/

#ifndef _NM_H
#define _NM_H


#include <elf.h>
char                *my_nm_32(void *data, Elf32_Ehdr *elf);
char                *my_nm(void *data, Elf64_Ehdr *elf);
void                print_sec_and_sym(Elf64_Sym sym, void *data,
				      Elf64_Shdr *shdr);
Elf64_Shdr	        *set_sym_tab(Elf64_Shdr **string_sec, char *str,
                                   Elf64_Ehdr *elf, Elf64_Shdr *shdr);
void                check_file(int fd, char *av);
Elf32_Shdr	*set_sym_tab32bits(Elf32_Shdr **string_sec, char *str,
				   Elf32_Ehdr *elf,
                                 Elf32_Shdr *shdr);
char                print_char_elf32bits(Elf32_Sym sym, Elf32_Shdr *shdr);
char                print_char_elf32bits2(Elf32_Sym sym, Elf32_Shdr *shdr);
void                print_sec_and_sym32bits(Elf32_Sym sym, void *data,
					    Elf32_Shdr *shdr);

#endif
