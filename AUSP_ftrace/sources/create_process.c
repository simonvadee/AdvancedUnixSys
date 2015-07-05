/*
** create_process.c for strace in /home/vadee_s/rendu/AUSP_strace
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun May 17 19:10:41 2015 simon vadée
** Last update Sun May 17 19:10:42 2015 simon vadée
*/

#include "strace.h"

void		trace_child(char *cmd, char **arg)
{
  if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
    {
      perror("ptrace <PTRACE_TRACEME> failed :");
      return ;
    }
  kill(getpid(), SIGSTOP);
  if (execvp(cmd, arg) == -1)
    perror("execvp failed : ");
}
