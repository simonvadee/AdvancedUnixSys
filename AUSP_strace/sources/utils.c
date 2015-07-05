/*
** utils.c for strace in /home/vadee_s/rendu/AUSP_strace
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun May 17 19:10:02 2015 simon vadée
** Last update Sun May 17 19:10:02 2015 simon vadée
*/

#include "strace.h"

char		*parse_path(char *path, char *cmd)
{
  char		*tmp;
  char		*ret;

  while ((tmp = strtok(path, ":")))
    {
      ret = (char *)malloc(sizeof(char) * (strlen(tmp) + strlen(cmd) + 2));
      if (!ret)
	{
	  write(2, "malloc failed\n", strlen("malloc failed\n"));
	  return (NULL);
	}
      ret = strcpy(ret, tmp);
      ret = strcat(ret, "/");
      ret = strcat(ret, cmd);
      if (!access(ret, X_OK))
	return (ret);
      path = NULL;
    }
  return (NULL);
}

void			build_corres_regs(long long int *data,
					  struct user_regs_struct *regs)
{
  data[0] = regs->rdi;
  data[1] = regs->rsi;
  data[2] = regs->rdx;
  data[3] = regs->rcx;
  data[4] = regs->r8;
  data[5] = regs->r9;
}
