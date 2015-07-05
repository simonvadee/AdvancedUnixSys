/*
** manage_flags.c for objdump in /home/vadee_s/rendu/AUSP_nmobjdump/objdump_dir
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Apr 19 16:15:36 2015 simon vadée
** Last update Sun Apr 19 16:17:18 2015 simon vadée
*/

#include "objdump.h"
#include "flags.h"

static void		get_flags(Elf64_Ehdr *data, Elf64_Shdr *shdr, int *flags)
{
  unsigned int		i;
  char			*strtab;

  strtab = fill_string_table(data, shdr, data->e_shstrndx);
  i = 0;
  if (data->e_type == ET_EXEC)
    *flags |= EXEC_P;
  if (data->e_type == ET_DYN)
    *flags |= DYNAMIC;
  while (i < data->e_shnum)
    {
      if (!strncmp(strtab + shdr[i].sh_name, ".debug", 6))
	*flags |= HAS_DEBUG;
      if (shdr[i].sh_type == SHT_SYMTAB)
	*flags |= HAS_SYMS;
      if (shdr[i].sh_type == SHT_REL)
	*flags |= HAS_RELOC;
      *flags |= D_PAGED;
      ++i;
    }
}

void		display_flags(Elf64_Ehdr *data, Elf64_Shdr *shdr)
{
  int		flags;

  flags = 0;
  get_flags(data, shdr, &flags);
  printf("architecture: i386:x86-64, flags 0x%08x:\n", flags);
  if ((flags & EXEC_P) == EXEC_P)
    printf("EXEC_P, ");
  if ((flags & DYNAMIC) == DYNAMIC)
    printf("DYNAMIC, ");
  if ((flags & HAS_SYMS) == HAS_SYMS)
    printf("HAS_SYMS, ");
  if ((flags & HAS_DEBUG) == HAS_DEBUG)
    printf("HAS_DEBUG, ");
  if ((flags & D_PAGED) == D_PAGED)
    printf("D_PAGED");
  printf("\nstart address 0x%016x\n\n", (unsigned int)data->e_entry);
}
