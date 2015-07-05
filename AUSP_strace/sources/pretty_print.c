/*
** pretty_print.c for strace in /home/vadee_s/rendu/AUSP_strace
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun May 17 19:10:21 2015 simon vadée
** Last update Sun May 17 19:10:23 2015 simon vadée
*/

#include "strace.h"

static const t_printenum		g_prettyprint[6] =
{
  {"access", &enumaccess},
  {"open", &enumopen},
  {"mprotect", &eprotmap},
  {"prot", &eprotmap},
  {"mmap", &enummmap},
  {NULL, NULL}
};

void				print_long(__attribute__((unused)) pid_t pid,
				   long long data,
				   __attribute__((unused)) char *name)
{
  fprintf(stderr, "0x%lx", (long)data);
}

void				print_ptr(pid_t __attribute__((unused)) pid,
				  long long data,
				  __attribute__((unused)) char *name)
{
  if (data == 0)
    fprintf(stderr, "NULL");
  else if (!strcmp(name, "write"))
    return print_string(pid, data, name);
  else
    fprintf(stderr, "0x%llx", data);
}

void				print_int(pid_t __attribute__((unused)) pid,
				  long long data,
				    char *name)
{
  unsigned int		i;

  i = 0;
  while (g_prettyprint[i].type)
    {
      if (!strcmp(name, g_prettyprint[i].type))
	{
	  g_prettyprint[i].ptrf(data);
	  return ;
	}
      ++i;
    }
  fprintf(stderr, "%d", (int)data);
}

void				print_uint(pid_t __attribute__((unused)) pid,
				   long long data,
				   __attribute__((unused))char *name)
{
  fprintf(stderr, "%u", (unsigned int)data);
}
