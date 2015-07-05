/*
** main.c for strace in /home/vadee_s/rendu/AUSP_strace
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun May 17 19:10:55 2015 simon vadée
** Last update Sun May 17 19:10:56 2015 simon vadée
*/

#include "strace.h"

static pid_t g_pid;

void			signal_handler(int sig)
{
  const char				*ret;

  printf("exiting process after receiving %s\n",
	 (ret = getsig(sig)) == NULL ? "unknown signal" : ret);
  ptrace(PTRACE_DETACH, g_pid, NULL, NULL);
  signal(sig, NULL);
  kill(getpid(), sig);
  kill(g_pid, sig);
}

static int			pid_mode(char **arg)
{
  if ((g_pid = atoi(arg[2])) <= 0 || g_pid > USHRT_MAX)
    {
      write(2, "Please enter a valid pid",
	    strlen("Please enter a valid pid\n"));
      return (1);
    }
  trace_process(g_pid, 0);
  ptrace(PTRACE_DETACH, g_pid, NULL, NULL);
  return 0;
}

static int			start_prog(char **arg)
{
  char			*cmd;
  pid_t			pid;

  if (!(cmd = find_cmd(strtok(arg[1], ""))))
    {
      printf("'%s' : executable not found\n", arg[1]);
      return (1);
    }
  if ((pid = fork()) == -1)
    {
      write(2, "Error : fork failed, abort\n",
  	    strlen("Error : fork failed, abort\n"));
      return (1);
    }
  if (!pid)
     trace_child(cmd, ++arg);
  else
    {
      g_pid = pid;
      trace_process(pid, 1);
    }
  return 0;
}

int			main(int ac, char **av)
{
  if (manage_signal())
    return (1);
  if (ac == 3 && !strcmp(av[1], "-p"))
    return (pid_mode(av));
  else if (ac >= 2)
    return (start_prog(av));
  else
    {
      write(2, "Usage  : ./strace -p <pid>\n\t ./strace <command>\n", 50);
      return (1);
    }
  return (0);
}
