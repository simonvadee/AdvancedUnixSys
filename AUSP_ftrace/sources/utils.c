/*
** utils.c for strace in /home/vadee_s/rendu/AUSP_strace
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun May 17 19:10:02 2015 simon vadée
** Last update Sat Jul  4 11:01:59 2015 Cédric Voinnet
*/

#include "strace.h"

void            build_graph(int fd, t_graph *graph, char *dest)
{
  char        *func_addr;

  asprintf(&func_addr, "func_0x%s", dest);
  if (graph->size > 0)
    write_graph(fd, graph->head->name, func_addr, CALL_FCT);
  else
    {
      dprintf(fd, "\t\"?? _start__ ??\" [label=\"?? _start__ ??\"];\n");
      write_graph(fd, "?? _start_ ??", func_addr, CALL_FCT);
    }
  pile(graph, func_addr);
}

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
