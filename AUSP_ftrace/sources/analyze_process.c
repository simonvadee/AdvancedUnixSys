/*
** analyze_process.c for strace in /home/vadee_s/rendu/AUSP_strace
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun May 17 19:09:16 2015 simon vadée
** Last update Sat Jul  4 09:51:25 2015 Cédric Voinnet
*/

#include "strace.h"
#include "syscalls.h"

void		get_return_value(struct user *usr, t_graph *graph, t_data *data)
{
  long		rsp;

  if ((data->peektext & 0xff) != 0xc3
      && (data->peektext & 0xff) != 0xc2
      && (data->peektext & 0xff) != 0xca
      && (data->peektext & 0xff) != 0xcb)
    return ;
  rsp = ptrace(PTRACE_PEEKTEXT, data->pid, usr->regs.rsp, 0);
  if (ptrace(PTRACE_PEEKTEXT, data->pid, rsp, 0) != 0 && graph->size > 0)
    depile(graph);
}

void		get_syscall_infos(struct user *usr, t_graph *graph, t_data *data)
{
  t_sysinfo	syscall;
  int		status;

  if ((data->peektext & 0xffff) != 0x50f || graph->size <= 0
      || usr->regs.rax > NB_SYSCALL)
    return ;
  syscall = g_syscalls[usr->regs.rax];
  if (ptrace(PTRACE_SINGLESTEP, data->pid, NULL, NULL) == -1)
    {
      graph_end(data->fd);
      exit(1);
    }
  wait4(data->pid, &status, 0, NULL);
  if (is_dead(data->pid, status))
    {
      graph_end(data->fd);
      exit(1);
    }
  write_graph(data->fd, graph->head->name, syscall.call, SYSCALL);
}

void		get_e8_call(struct user *usr, t_graph *graph, t_data *data)
{
  char		*dest;

  if ((data->peektext & 0xff) == 0xe8)
    {
      asprintf(&dest, "%llx", usr->regs.rip);
      build_graph(data->fd, graph, dest);
    }
}

void		get_ff_call(struct user *usr, t_graph *graph, t_data *data)
{
  char		*dest;

  if ((data->peektext & 0xffff) == 0xd0ff)
    {
      asprintf(&dest, "%llx", usr->regs.rax);
      build_graph(data->fd, graph, dest);
    }
  if ((data->peektext & 0xffff) == 0xd2ff)
    {
      asprintf(&dest, "%llx", usr->regs.rdx);
      build_graph(data->fd, graph, dest);
    }
}

int		get_infos_process(pid_t pid, int status, int fd, t_graph *graph)
{
  struct user	usr;
  t_data	data;

  if (ptrace(PTRACE_GETREGS, pid, NULL, &usr) == -1)
    {
      if (WIFEXITED(status))
	fprintf(stderr, "\t = ?\n+++ exited with %d +++\n", WEXITSTATUS(status));
      else
	perror("ptrace <PTRACE_GETREGS> failed : ");
      graph_end(fd);
      return 1;
    }
  data.peektext = ptrace(PTRACE_PEEKTEXT, pid, usr.regs.rip, 0);
  data.fd = fd;
  data.pid = pid;
  get_syscall_infos(&usr, graph, &data);
  get_return_value(&usr, graph, &data);
  get_e8_call(&usr, graph, &data);
  get_ff_call(&usr, graph, &data);
  return (0);
}
