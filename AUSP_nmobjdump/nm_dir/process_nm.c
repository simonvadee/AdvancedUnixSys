/*
** process_nm.c for nm in /home/vadee_s/rendu/AUSP_nmobjdump/nm_dir
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Apr 19 16:12:39 2015 simon vadée
** Last update Sun Apr 19 16:12:41 2015 simon vadée
*/

#include "nm.h"

static void		get_symbol_tables(t_elf *data)
{
  Elf64_Shdr		*tmp_sym_tab;
  Elf64_Shdr		*tmp_str_sym_tab;

  tmp_sym_tab = &data->section_header[data->symbol_table_idx];
  tmp_str_sym_tab = &data->section_header[data->string_symbol_table_idx];
  if (tmp_sym_tab)
    data->symbol_table = (void*)((long unsigned int)data->file_header
				 + tmp_sym_tab->sh_offset);
  else
    data->symbol_table = NULL;
  if (tmp_str_sym_tab)
    data->string_symbol_table = (char *)((long unsigned int)data->file_header
					 + tmp_str_sym_tab->sh_offset);
  else
    data->string_symbol_table = NULL;
}

static int		map_file(t_elf *data, int fd, char *filename)
{
  void			*tmp;

  tmp = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0);
  if (tmp == (void *)-1)
    {
      printf("syscall mmap failed, abort\n");
      return (0);
    }
  data->file_header = (Elf64_Ehdr *)tmp;
  if (data->file_header->e_ident[EI_MAG0] != ELFMAG0
      || data->file_header->e_ident[EI_MAG1] != ELFMAG1
      || data->file_header->e_ident[EI_MAG2] != ELFMAG2
      || data->file_header->e_ident[EI_MAG3] != ELFMAG3)
    {
      printf("File '%s' is not of type ELF\n", filename);
      return (0);
    }
  data->section_header = fill_section_header(data->file_header,
					     data->file_header->e_shoff);
  data->string_table =
    fill_string_table(tmp, data->section_header,
		      data->file_header->e_shstrndx);
  if (!find_str_symbol_table(data) || !find_symbol_tab(data))
    return (0);
  return (1);
}

int			process_nm(char *filename)
{
  int			fd;
  t_elf			data;

  if ((fd = open(filename, O_RDONLY)) == -1)
    {
      printf("Failed to open %s, abort the mission\n", filename);
      return (-1);
    }
  else if (!map_file(&data, fd, filename))
    return (-1);
  get_symbol_tables(&data);
  store_symbols(&data);
  munmap(&data, filesize(fd));
  close(fd);
  return (0);
}
