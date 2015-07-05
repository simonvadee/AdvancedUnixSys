/*
** main.c for objdump in /home/vadee_s/rendu/AUSP_nmobjdump/objdump_dir
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Apr 19 16:14:04 2015 simon vadée
** Last update Sun Apr 19 16:14:05 2015 simon vadée
*/

#include "objdump.h"

int		main(int ac, char **av)
{
  unsigned int	i;

  i = 1;
  if (ac == 1)
    return (process_objdump("a.out"));
  while (av[i])
    {
      process_objdump(av[i]);
      ++i;
    }
  return (0);
}
