/*
** utils.c for all in /home/vadee_s/rendu/AUSP_nmobjdump/utils
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Apr 19 16:17:56 2015 simon vadée
** Last update Sun Apr 19 16:18:05 2015 simon vadée
*/

#include <nm.h>

int		filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

void		*fill_section_header(Elf64_Ehdr *fhdr, unsigned int offset)
{
  if (offset)
    return ((void*)((long unsigned int)fhdr + offset));
  else
    return (NULL);
}

char		*fill_string_table(Elf64_Ehdr *fhdr, Elf64_Shdr *section_header,
				   unsigned int shstrndx)
{
  if (section_header)
    return (char *)((long unsigned int)fhdr
	    + section_header[shstrndx].sh_offset);
  else
    return (NULL);
}

int		find_str_symbol_table(t_elf *data)
{
  unsigned int	i;

  i = 0;
  while (i != data->file_header->e_shnum)
    {
      if (!strcmp(&data->string_table[data->section_header[i].sh_name],
		  ".strtab"))
	{
	  data->string_symbol_table_idx = i;
	  return (1);
	}
      ++i;
    }
  printf("String symbol table not found, abort\n");
  return (0);
}

int		find_symbol_tab(t_elf *data)
{
  unsigned int	i;

  i = 0;
  while (i != data->file_header->e_shnum)
    {
      if (!strcmp(&data->string_table[data->section_header[i].sh_name],
		  ".symtab"))
	{
	 data->symbol_table_idx = i;
	 return (1);
	}
      ++i;
    }
  printf("Symbol table not found, abort\n");
  return (0);
}
