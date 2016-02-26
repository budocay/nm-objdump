/*
** check_err.c for check_err in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Tue Feb 16 13:50:56 2016 lina_a
** Last update Tue Feb 16 13:50:56 2016 lina_a
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "objdump.h"

bool    section_not_printable(char *data, Elf64_Shdr *shdr, int cmpt)
{
    if (strcmp(&data[shdr[cmpt].sh_name], ".rela.text") == 0
        || strcmp(&data[shdr[cmpt].sh_name], ".rela.eh_frame") == 0
        || strcmp(&data[shdr[cmpt].sh_name], ".rela.debug_line") == 0
        || strcmp(&data[shdr[cmpt].sh_name], ".rela.debug_aranges") == 0
        || strcmp(&data[shdr[cmpt].sh_name], ".rela.debug_info") == 0
        || strcmp(&data[shdr[cmpt].sh_name], ".rela.preinit_array") == 0
        || strcmp(&data[shdr[cmpt].sh_name], ".rela.init_array") == 0
        || strcmp(&data[shdr[cmpt].sh_name], ".rela.debug_ranges") == 0
        || strcmp(&data[shdr[cmpt].sh_name], ".rela.debug_loc") == 0
        || strcmp(&data[shdr[cmpt].sh_name], ".rela.fini_array") == 0
        || strcmp(&data[shdr[cmpt].sh_name], ".rela.data.rel") == 0)
        return true;
    return false;
}


int		my_objdump(void *data, char *file, Elf64_Ehdr *elf)
{
    Elf64_Shdr  *shdr;
    char        *str;

    shdr = (Elf64_Shdr *)(data + elf->e_shoff);
    str = (char*)(data + shdr[elf->e_shstrndx].sh_offset);
    if (elf->e_machine == EM_X86_64)
      {
        printf("\n%s:%5cfile format %s\n", file, ' ', ELF_64);
        printf("architecture: %s, flags 0x%08x:\n", INTEL_64,
               found_flag(str, shdr, elf));
        print_flags64(elf, shdr, str);
        printf("start address 0x%016x\n\n", (int)elf->e_entry);
        objdump_flag_s(str, elf, shdr);
      }
    return (0);
}

void		which_header_correct_is(void *data, char *name_file, int fd)
{
    Elf64_Ehdr  *elf;
    Elf32_Ehdr  *elf32;

    if (check_header((Elf64_Ehdr*)data) != -1)
      {
          check_truncated_file(name_file, fd);
        elf = (Elf64_Ehdr*)data;
        if (elf->e_ident[EI_CLASS] == ELFCLASS64)
	  my_objdump(data, name_file, elf);
      }
    else if (check_header_elf_32(((Elf32_Ehdr*)data)) != -1)
      {
        elf32 = (Elf32_Ehdr*)data;
        if (elf32->e_ident[EI_CLASS] == ELFCLASS32)
	  my_objdump_elf_32(data, name_file);
      }
    else
      {
          dprintf(STDERR_FILENO, "/usr/bin/objdump: %s:"
                  " File format not recognized\n", name_file);
        close(fd);
        exit(EXIT_SUCCESS);
      }
}

void        check_truncated_file(char *name_file, int fd)
{
    if (verification(name_file) == NULL)
    {
        dprintf(STDERR_FILENO,"/usr/bin/objdump: %s: File truncated\n",
                name_file);
        close(fd);
        exit(EXIT_SUCCESS);
        return;
    }
}

void        check_data(int fd, char *name_file)
{
    void        *data;
    struct stat file;

    if ((fstat(fd, &file)) == -1)
      {
        dprintf(STDERR_FILENO, "%m\n");
        return;
      }
    if ((data = mmap(NULL, (size_t) file.st_size, PROT_READ,
                     MAP_SHARED | MAP_FILE, fd, 0)) == MAP_FAILED)
        return;
    which_header_correct_is(data, name_file, fd);
    if ((munmap(data, (size_t) file.st_size)) == -1)
      {
        dprintf(STDERR_FILENO, "%m\n");
        return;
      }
}
