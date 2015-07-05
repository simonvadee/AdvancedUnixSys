/*
** string_operations.c for all in /home/vadee_s/rendu/AUSP_nmobjdump/utils
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Apr 19 16:17:48 2015 simon vadée
** Last update Sun Apr 19 16:17:49 2015 simon vadée
*/

#include "nm.h"

void		remove_underscore(char *s)
{
  char		*src;
  char		*dst;

  src = s;
  dst = s;
  while (*src)
    {
      *dst = *src;
      if (*dst != '_')
	dst++;
      ++src;
    }
  *dst = '\0';
}

int		custom_strcmp(char *s1, char *s2)
{
  char		*cp1;
  char		*cp2;
  int		ret;

  cp1 = strdup(s1);
  cp2 = strdup(s2);
  remove_underscore(cp1);
  remove_underscore(cp2);
  ret = strcasecmp(cp1, cp2);
  free(cp1);
  free(cp2);
  return (ret);
}
