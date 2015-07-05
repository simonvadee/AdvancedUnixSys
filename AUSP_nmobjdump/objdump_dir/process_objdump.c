/*
** process_objdump.c for objdump in /home/vadee_s/rendu/AUSP_nmobjdump/objdump_dir
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Apr 19 16:16:21 2015 simon vadée
** Last update Sun Apr 19 16:16:29 2015 simon vadée
*/

#include "objdump.h"

static int		map_file(Elf64_Ehdr **data, int fd, char *filename)
{
  void			*tmp;

  tmp = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0);
  *data = (Elf64_Ehdr*)tmp;
  if ((*data)->e_ident[EI_MAG0] != ELFMAG0
      || (*data)->e_ident[EI_MAG1] != ELFMAG1
      || (*data)->e_ident[EI_MAG2] != ELFMAG2
      || (*data)->e_ident[EI_MAG3] != ELFMAG3)
    {
      printf("File '%s' is not of type ELF\n", filename);
      return (0);
    }
  return (1);
}

int			process_objdump(char *filename)
{
  int			fd;
  Elf64_Ehdr		*data;

  if ((fd = open(filename, O_RDONLY)) == -1)
    {
      printf("Failed to open %s, abort the mission\n", filename);
      return (-1);
    }
  else if (!map_file(&data, fd, filename))
    return (-1);
  display_infos(data, filename);
  munmap(data, filesize(fd));
  close(fd);
  return (0);
}
