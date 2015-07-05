/*
** manage_signal.c for strace in /home/vadee_s/rendu/AUSP_strace
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun May 17 19:10:36 2015 simon vadée
** Last update Sun May 17 19:10:37 2015 simon vadée
*/

#include "strace.h"

static const t_sig		g_sig[4] =
{
  {SIGINT, "SIGINT"},
  {SIGTERM, "SIGTERM"},
  {SIGQUIT, "SIGQUIT"},
  {0, NULL}
};

int			is_dead(pid_t pid, int status)
{
  siginfo_t		signal;

  if (WIFSIGNALED(status))
    {
      bzero(&signal, sizeof(signal));
      if ((ptrace(PTRACE_GETSIGINFO, pid, NULL, &signal)) == -1)
	{
	  write(2, "ptrace failed while trying to getsiginfo\n",
		strlen("ptrace failed while trying to getsiginfo\n"));
	  return (1);
	}
      printf("process killed by signal %s\n", strerror(signal.si_errno));
      return (1);
    }
  if (WIFEXITED(status))
    {
      printf("+++ exited with %d +++\n", status);
      return (1);
    }
  return (0);
}

const char		*getsig(int sig)
{
  unsigned int			i;

  i = 0;
  while (g_sig[i].sig)
    {
      if (g_sig[i].sig == sig)
	return (g_sig[i].code);
      ++i;
    }
  return (NULL);
}

int			manage_signal()
{
  if (signal(SIGINT, &signal_handler) == SIG_ERR
      || signal(SIGTERM, &signal_handler) == SIG_ERR
      || signal(SIGQUIT, &signal_handler) == SIG_ERR)
    {
      write(2, "signal failed, abort\n", strlen("signal failed, abort\n"));
      return (1);
    }
  return (0);
}
