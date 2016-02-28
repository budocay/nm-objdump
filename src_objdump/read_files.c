/*
** read_files.c for read_files in /home/lina_a/rendu/B4/PSU_2016_nmobjdump
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Mon Feb 22 16:41:16 2016 lina_a
** Last update Mon Feb 22 16:41:16 2016 lina_a
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "objdump.h"

int		verification(char *av)
{
    FILE*	file_elf;
    Elf64_Ehdr  elfHdr;
    Elf64_Shdr  sectHdr;

    if ((file_elf = fopen(av, "r")) == NULL)
        return (-1);
    if ((fread(&elfHdr, sizeof elfHdr, 1, file_elf)) < 1)
        return (-1);
    if ((fseek(file_elf, elfHdr.e_shoff + elfHdr.e_shstrndx * sizeof sectHdr,
               SEEK_SET)) == -1)
        return (-1);
    if ((fread(&sectHdr, sizeof sectHdr, 1, file_elf)) < 1)
    {
        fclose(file_elf);
        return (-1);
    }
    if ((verify_sect_name(file_elf, sectHdr, elfHdr)) == -1)
    {
        fclose(file_elf);
        return (-1);
    }
    fclose(file_elf);
    return (0);
}

int         verify_sect_name(FILE *file_elf, Elf64_Shdr sectHdr,
                              Elf64_Ehdr elfHdr)
{
    uint    idx;
    char    *SectName;

    idx = 0;
    if ((SectName = malloc((sectHdr.sh_size))) == NULL)
        return (-1);
    if ((fseek(file_elf, sectHdr.sh_offset, SEEK_SET)) == -1)
        return (-1);
    if ((fread(SectName, sectHdr.sh_size, 1, file_elf)) < 1)
        return (-1);
    if (SectName != NULL)
        free(SectName);
    while (idx < elfHdr.e_shnum)
    {
        if ((fseek(file_elf, elfHdr.e_shoff + idx * sizeof sectHdr,
                   SEEK_SET)) == -1)
            return (-1);
        if ((fread(&sectHdr, sizeof sectHdr, 1, file_elf)) < 1)
            return (-1);
        idx++;
    }
    return (0);
}
