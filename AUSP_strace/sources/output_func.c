/*
** output_func.c for strace in /home/vadee_s/rendu/AUSP_strace
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun May 17 19:11:02 2015 simon vadée
** Last update Sun May 17 19:11:05 2015 simon vadée
*/

#include "strace.h"

static const t_printtinfo	g_fprint[11] =
{
  {"char**", &print_strtab},
  {"char*", &print_string},
  {"*", &print_ptr},
  {"unsigned int", &print_uint},
  {"int", &print_int},
  {"size_t", &print_uint},
  {"pid_t", &print_uint},
  {"off_t", &print_int},
  {"unsigned long", &print_long},
  {"long", &print_long},
  {NULL, NULL}
};

void				print_strtab(pid_t pid, long long data,
					     __attribute__((unused)) char *name)
{
  long				addr;
  int				idx;

  fprintf(stderr, "[");
  idx = 0;
  while ((addr = ptrace(PTRACE_PEEKTEXT, pid, data + idx, NULL)) && idx <= 20)
    {
      fprintf(stderr, "\"");
      print_string(pid, addr, "");
      fprintf(stderr, "\"");
      idx += sizeof(long);
      if (ptrace(PTRACE_PEEKTEXT, pid, data + idx, NULL))
	fprintf(stderr, ", ");
    }
  if (idx >= 20)
    fprintf(stderr, "...");
  fprintf(stderr, "]");
}

void				print_string(pid_t pid, long long data,
					     __attribute__((unused)) char *name)
{
  char				c;
  int				idx;

  idx = 0;
  fprintf(stderr, "\"");
  while ((c = ptrace(PTRACE_PEEKTEXT, pid, data + idx, NULL)) && idx <= 30)
    {
      if (c == '\n')
	fprintf(stderr, "\\n");
      else if (c == '\t')
	fprintf(stderr, "\\t");
      else
	fprintf(stderr, "%c", c);
      ++idx;
    }
  fprintf(stderr, "\"");
  if (idx >= 30)
    fprintf(stderr, "...");
}

void				print_arg(pid_t pid, long long data,
					  char *type, char *name)
{
  unsigned int			i;

  i = 0;
  while (g_fprint[i].type)
    {
      if (!strcmp(type, "..."))
	{
	  fprintf(stderr, "...");
	  break ;
	}
      else if (strstr(type, g_fprint[i].type))
	{
	  g_fprint[i].ptrf(pid, data, name);
	  break ;
	}
      ++i;
    }
}

void				print_return_value(long long data, char *type)
{
  if (data < 0)
    fprintf(stderr, "\t = -1 (%s)\n", strerror(-data));
  else if (strchr(type, '*'))
    fprintf(stderr, "\t = 0x%llx\n", data);
  else
    fprintf(stderr, "\t = %lld\n", data);
}

void				print_params(pid_t pid, t_sysinfo *syscall,
				     struct user_regs_struct *regs)
{
  unsigned int			i;
  long long int			data[6];

  i = 0;
  build_corres_regs(data, regs);
  while (syscall->args[i])
    {
      if (!strcmp(syscall->call, "mmap")
	  && (i == 2))
	print_int(pid, data[i], "prot");
      else if (!strcmp(syscall->call, "mmap")
	  && (i == 4 || i == 5))
	print_int(pid, data[i], "");
      else if (!strcmp("openat", syscall->call) && i == 2)
	print_int(pid, data[i], "open");
      else
	print_arg(pid, data[i], syscall->args[i], syscall->call);
      ++i;
      if (syscall->args[i])
	fprintf(stderr, ", ");
    }
}
