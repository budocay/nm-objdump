/*
** objdump.h for objdmp.h in /home/lina_a/rendu/B4/PSU_2016_nmobjdump/include
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Sat Feb 20 18:59:30 2016 lina_a
** Last update Sat Feb 20 18:59:30 2016 lina_a
*/

#ifndef OBJDUMP_H_
# define OBJDUMP_H_

#define INTEL_64 "i386:x86-64"
#define INTEL_32 "i386"
#define ELF_64 "elf64-x86-64"
#define ELF_32 "elf32-i386"

#include <stdbool.h>

void	    print_addr(int addr, unsigned int inc, unsigned char *to_print);
void	    is_sym_tab(char *str, Elf64_Shdr *shdr, int i, int flag);
void        print_flags64(Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *str);
void        print_flags32(Elf32_Ehdr *elf, Elf32_Shdr *shdr, char *str);
char        *verification(char *av);
char        *verify_sect_name(FILE *file_elf, Elf64_Shdr sectHdr,
                              Elf64_Ehdr elfHdr);
bool        section_not_printable(char *data, Elf64_Shdr *shdr, int cmpt);
void        check_truncated_file(char *name_file, int fd);
/*
** Prototype pour elf64 bits
*/

int         my_objdump(void *pVoid, char *file, Elf64_Ehdr *elf);

void        objdump_flag_s(char *str, Elf64_Ehdr *elf, Elf64_Shdr *shdr);
void        check_data(int fd, char *name_file);
void	    print_val(unsigned int j, unsigned int *z, unsigned char *w,
                        char *t);
int         found_flag(char *str, Elf64_Shdr *shdr, Elf64_Ehdr *elf);
void        section_to_print(char *data, Elf64_Ehdr *elf,
                            Elf64_Shdr *shdr, int cmpt);

void        section_to_print(char *data, Elf64_Ehdr *elf,
                             Elf64_Shdr *shdr, int cmpt);
int         check_header(Elf64_Ehdr *data);
int         flags_to_found64(Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *str);

/*
** Prototype pour elf32 bits
*/

int        found_flag_elf_32(char *str, Elf32_Shdr *shdr, Elf32_Ehdr *elf);
int        my_objdump_elf_32(void *data, char *file);
void        objdump_flag_s_elf_32(char *str, Elf32_Ehdr *elf,
                                  Elf32_Shdr *shdr);
void                    section_to_print_elf_32(char *data, Elf32_Ehdr *elf,
                                                Elf32_Shdr *shdr, int cmpt);
void		print_ascii_elf_32(unsigned int j, unsigned int *z,
                               unsigned char *w, char *t);
int         check_header_elf_32(Elf32_Ehdr *data);
int         flags_to_found32(Elf32_Ehdr *elf, Elf32_Shdr *shdr, char *str);

#endif /* OBJDUMP_H_! */
