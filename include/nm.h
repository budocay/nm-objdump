//
// Created by lina_a on 23/02/16.
//

#ifndef PSU_2016_NMOBJDUMP_NM_H
#define PSU_2016_NMOBJDUMP_NM_H


#include <elf.h>
void                my_nm_32();
char                *my_nm(void *data, Elf64_Ehdr *elf);
void                print_sec_and_sym(Elf64_Sym sym, void *data,
				      Elf64_Shdr *shdr);
Elf64_Shdr	    *set_sym_tab(Elf64_Shdr **string_sec, char *str,
                                 Elf64_Ehdr *elf, Elf64_Shdr *shdr);
void                check_file(int fd, char *av);

#endif //PSU_2016_NMOBJDUMP_NM_H
