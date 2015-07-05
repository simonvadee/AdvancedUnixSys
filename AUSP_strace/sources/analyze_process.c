/*
** analyze_process.c for strace in /home/vadee_s/rendu/AUSP_strace
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun May 17 19:09:16 2015 simon vadée
** Last update Sun May 17 19:09:20 2015 simon vadée
*/

#include "strace.h"
#include "syscalls.h"

void			get_return_value(struct user *usr)
{
  t_sysinfo		syscall;

  if (usr->regs.orig_rax > NB_SYSCALL)
    return ;
  syscall = g_syscalls[usr->regs.orig_rax];
  print_return_value(usr->regs.rax, syscall.return_type);
}

void			get_syscall_infos(pid_t pid, struct user *usr, char *mode)
{
  long			code;
  t_sysinfo		syscall;

  if ((code = ptrace(PTRACE_PEEKTEXT, pid, usr->regs.rip, NULL)) == -1
    || (code & 0xFFFF) != 0x50f)
    return ;
  else if (usr->regs.rax > NB_SYSCALL)
    return ;
  *mode = 1;
  syscall = g_syscalls[usr->regs.rax];
  fprintf(stderr, "%s(", syscall.call);
  print_params(pid, &syscall, &(usr->regs));
  fprintf(stderr, ")");
}

int			get_infos_process(pid_t pid, int status)
{
  static char		mode = 0;
  struct user		usr;

  if (ptrace(PTRACE_GETREGS, pid, NULL, &usr) == -1)
    {
      if (WIFEXITED(status))
	fprintf(stderr, "\t = ?\n+++ exited with %d +++\n", WEXITSTATUS(status));
      else
	perror("ptrace <PTRACE_GETREGS> failed : ");
      return 1;
    }
  if (mode)
    {
      get_return_value(&usr);
      mode = 0;
    }
  else
    get_syscall_infos(pid, &usr, &mode);
  return 0;
}
