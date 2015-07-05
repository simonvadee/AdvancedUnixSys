/*
** print_enum.c for strace in /home/vadee_s/rendu/AUSP_strace
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun May 17 19:09:55 2015 simon vadée
** Last update Sun May 17 19:09:55 2015 simon vadée
*/

#include <sys/stat.h>
#include "strace.h"

static const t_macro				g_eaccess[4] =
  {
    {R_OK, "R_OK"},
    {W_OK, "W_OK"},
    {X_OK, "X_OK"},
    {0, NULL}
  };

static const t_macro				g_eopen[15] =
  {
    {O_APPEND, "O_APPEND"},
    {O_ASYNC, "O_ASYNC"},
    {O_CLOEXEC, "O_CLOEXEC"},
    {O_CREAT, "O_CREAT"},
    {O_DIRECT, "O_DIRECT"},
    {O_DIRECTORY, "O_DIRECTORY"},
    {O_EXCL, "O_EXCL"},
    {O_LARGEFILE, "O_LARGEFILE"},
    {O_NOATIME, "O_NOATIME"},
    {O_NOCTTY, "O_NOCTTY"},
    {O_NOFOLLOW, "O_NOFOLLOW"},
    {O_NONBLOCK, "O_NONBLOCK"},
    {O_SYNC, "O_SYNC"},
    {O_TRUNC, "O_TRUNC"},
    {0, NULL}
  };

static const t_macro				g_emmap[14] =
  {
    {MAP_SHARED, "MAP_SHARED"},
    {MAP_PRIVATE, "MAP_PRIVATE"},
    {MAP_32BIT, "MAP_32BIT"},
    {MAP_ANONYMOUS, "MAP_ANONYMOUS"},
    {MAP_DENYWRITE, "MAP_DENYWRITE"},
    {MAP_FIXED, "MAP_FIXED"},
    {MAP_GROWSDOWN, "MAP_GROWSDOWN"},
    {MAP_HUGETLB, "MAP_HUGETLB"},
    {MAP_LOCKED, "MAP_LOCKED"},
    {MAP_NONBLOCK, "MAP_NONBLOCK"},
    {MAP_NORESERVE, "MAP_NORESERVE"},
    {MAP_POPULATE, "MAP_POPULATE"},
    {MAP_STACK, "MAP_STACK"},
    {0, NULL}
  };

static const t_macro				g_emmap_prot[4] =
  {
    {PROT_EXEC, "PROT_EXEC"},
    {PROT_READ, "PROT_READ"},
    {PROT_WRITE, "PROT_WRITE"},
    {0, NULL}
  };

void					enumaccess(long long data)
{
  char				flag;
  unsigned int			i;

  i = 0;
  flag = 0;
  if (data == F_OK)
    {
      fprintf(stderr, "F_OK");
      return ;
    }
  while (g_eaccess[i].str)
    {
     if (g_eaccess[i].code & data)
      {
	fprintf(stderr, (flag ? "|%s" : "%s"), g_eaccess[i].str);
	flag = 1;
      }
     ++i;
    }
}
void					enumopen(long long data)
{
  unsigned int			i;

  i = 0;
  if (data & O_RDWR)
      fprintf(stderr, "O_RDWR");
  else if (data & O_WRONLY)
      fprintf(stderr, "O_WRONLY");
  else
      fprintf(stderr, "O_RDONLY");
  while (g_eopen[i].str)
    {
      if (data & g_eopen[i].code)
	fprintf(stderr, "|%s", g_eopen[i].str);
      ++i;
    }
}

void					enummmap(long long data)
{
  char					flag;
  unsigned int				i;

  i = 0;
  flag = 0;
  while (g_emmap[i].str)
    {
      if (g_emmap[i].code & data)
      {
	fprintf(stderr, (flag ? "|%s" : "%s"), g_emmap[i].str);
	flag = 1;
      }
      ++i;
    }
}

void					eprotmap(long long data)
{
  char					flag = 0;
  unsigned int				i = 0;

  while (g_emmap_prot[i].str)
    {
      if (g_emmap_prot[i].code & data)
	{
	  fprintf(stderr, (flag ? "|%s" : "%s"), g_emmap_prot[i].str);
	  flag = 1;
	}
      ++i;
    }
  if (!flag)
    fprintf(stderr, "PROT_NONE");
}
