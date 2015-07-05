/*
** main.c for nm in /home/vadee_s/rendu/AUSP_nmobjdump/nm_dir
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Apr 19 16:12:03 2015 simon vadée
** Last update Sun Apr 19 16:12:04 2015 simon vadée
*/

#include "nm.h"

int		main(int ac, char **av)
{
  unsigned int	i;

  i = 1;
  if (ac == 1)
    return (process_nm("./a.out"));
  while (av[i])
    {
      process_nm(av[i]);
      ++i;
    }
  return (0);
}
