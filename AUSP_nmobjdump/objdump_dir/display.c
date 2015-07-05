/*
** display.c for objdump in /home/vadee_s/rendu/AUSP_nmobjdump/objdump_dir
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Apr 19 16:13:30 2015 simon vadée
** Last update Sun Apr 19 16:13:49 2015 simon vadée
*/

#include "objdump.h"

static char     *g_elf[3] =
  {
    "none",
    "elf32",
    "elf64"
  };

static void	print_hexa_format(int i, int size, char *content)
{
  int		j;

  j = 0;
  while (j < 16 && (i + j) < size)
    {
      if ((j % 4) == 0)
	printf(" %02x", content[i + j] & 0x0000000ff);
      else
	printf("%02x", content[i + j] & 0x0000000ff);
      ++j;
    }
  if (j < 16)
    {
      while (j < 17)
	{
	  if (j != 16 && j % 4 == 0)
	    printf(" ");
	  printf("  ");
	  ++j;
	}
    }
  else
    printf("  ");
}

static void	print_str_format(int i, int size, char *content)
{
  int		j;

  j = 0;
  while (j < 16 && (i + j) < size)
    {
      if (content[i + j] >= ' ' && content[i + j] <= '~')
	printf("%c", content[i + j]);
      else
	printf(".");
      ++j;
    }
  while (j++ < 16)
    printf(" ");
}

static void	display_content(Elf64_Ehdr *data, Elf64_Shdr *shdr,
				char *string_table)
{
  unsigned int	i;
  char		*content;
  unsigned int  addr;

  i = 0;
  content = (char *)((long unsigned int)data + shdr->sh_offset);
  printf("Contents of section %s:\n", string_table + shdr->sh_name);
  addr = shdr->sh_addr;
  while (i < (unsigned int)shdr->sh_size)
    {
      if (strcmp(".debug_str", string_table + shdr->sh_name) != 0
	  && (strcmp(".comment", string_table + shdr->sh_name) == 0
	      || strncmp(".debug", string_table + shdr->sh_name, 6) == 0))
	printf(" %04x", addr);
      else
	printf(" %05x", addr);
      print_hexa_format(i, shdr->sh_size, content);
      print_str_format(i, shdr->sh_size, content);
      addr += 16;
      i += 16;
      printf("\n");
    }
}

static void	display_each_section(Elf64_Ehdr *data, Elf64_Shdr *shdr)
{
  char		*string_table;
  unsigned int	i;

  i = 0;
  string_table = fill_string_table(data, shdr, data->e_shstrndx);
  while (i != data->e_shnum)
    {
      if (string_table[shdr[i].sh_name]
	  && strcmp(string_table + shdr[i].sh_name, ".symtab") != 0
	  && strcmp(string_table + shdr[i].sh_name, ".shstrtab") != 0
	  && strcmp(string_table + shdr[i].sh_name, ".strtab") != 0
	  && strcmp(string_table + shdr[i].sh_name, ".bss") != 0)
	display_content(data, &shdr[i], string_table);
      ++i;
    }
}

void		display_infos(Elf64_Ehdr *data, char *filename)
{
  Elf64_Shdr	*shdr;

  shdr = fill_section_header(data, data->e_shoff);
  printf("\n%s:     file format %s-x86-64\n",
	 filename,
	 g_elf[data->e_ident[EI_CLASS]]);
  display_flags(data, shdr);
  display_each_section(data, shdr);
}
