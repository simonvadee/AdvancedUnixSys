/*
** trace_process.c for strace in /home/vadee_s/rendu/AUSP_strace
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun May 17 19:10:10 2015 simon vadée
** Last update Sat Jul  4 09:17:18 2015 Cédric Voinnet
*/

#include "strace.h"

char		*find_cmd(char *cmd)
{
  char		*path;

  if (!(path = getenv("PATH")))
    {
      write (2, "Could not get the environment, abort\n",
	     strlen("Could not get the environment, abort\n"));
      return (NULL);
    }
  if (!access(cmd, X_OK))
     return cmd;
  return (parse_path(path, cmd));
}

void		trace_graph(pid_t pid)
{
  t_graph			*graph;
  int				fd;
  int				status;

  if ((fd = begin_graph()) == -1)
    return;
  set_fd(fd);
  graph = init_graph();
  while (42)
    {
      if (is_dead(pid, status)
	  || get_infos_process(pid, status, fd, graph))
	{
	  graph_end(fd);
	  return ;
	}
      if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
	{
	  kill(pid, SIGQUIT);
	  perror("ptrace <PTRACE_SINGLESTEP> failed :  ");
	  graph_end(fd);
	}
      if (wait4(pid, &status, 0, NULL) == -1)
	{
	  perror("wait4 failed : ");
	  graph_end(fd);
	  return ;
       	}
    }
}

void		trace_process(pid_t pid, char launch)
{
  int		status;

  if (launch && ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
    {
      kill(pid, SIGQUIT);
      perror("ptrace <PTRACE_ATTACH> failed :  ");
      return ;
    }
  if (manage_signal())
    return ;
  wait4(pid, &status, WUNTRACED, NULL);
  if (!WIFSTOPPED(status))
    write(2, "exiting program after receiving signal\n", 40);
  trace_graph(pid);
}
