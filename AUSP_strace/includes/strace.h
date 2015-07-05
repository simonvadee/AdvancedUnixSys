/*
** strace.h for strace in /home/vadee_s/rendu/AUSP_strace
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun May 17 19:08:25 2015 simon vadée
** Last update Sun May 17 19:08:31 2015 simon vadée
*/

#ifndef STRACE_H_
# define STRACE_H_

# include <stdlib.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <string.h>
# include <sys/types.h>
# include <signal.h>
# include <limits.h>
# include <sys/user.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/ptrace.h>
# include <unistd.h>
# include <stdio.h>

# define NB_SYSCALL 301

typedef struct			s_signal
{
  int				sig;
  char				*code;
}				t_sig;

typedef struct			s_sysinfo
{
  char				*call;
  char				*return_type;
  char				*args[7];
}				t_sysinfo;

typedef struct			s_printtype
{
  char				*type;
  void				(*ptrf)(pid_t pid, long long data, char *name);
}				t_printtinfo;

typedef struct			s_printenum
{
  char				*type;
  void				(*ptrf)(long long data);
}				t_printenum;

typedef struct			s_macro
{
  int				code;
  char				*str;
}				t_macro;

void				trace_child(char *cmd, char **arg);
int				manage_signal();
const char			*getsig(int sig);
void				signal_handler(int sig);
char				*find_cmd(char *cmd);
void				trace_child(char *cmd, char **arg);
void				trace_process(pid_t pid, char launch);
int				is_dead(pid_t pid, int status);
int				get_infos_process(pid_t pid, int status);
void				print_params(pid_t pid, t_sysinfo *syscall,
					     struct user_regs_struct *regs);
void				build_corres_regs(long long int *data,
						  struct user_regs_struct
						  *regs);
void				print_return_value(long long data, char *type);
void		       		print_arg(pid_t pid, long long data,
					  char *type, char *name);
char				*parse_path(char *path, char *cmd);
void				print_string(pid_t pid, long long data,
					     char *name);
void				print_strtab(pid_t pid, long long data,
					     char *name);
void				print_ptr(pid_t __attribute__((unused)) pid,
					  long long data, char *name);
void				print_int(pid_t __attribute__((unused)) pid,
					  long long data, char *name);
void				print_uint(pid_t __attribute__((unused)) pid,
					   long long data, char *name);
void				print_long(pid_t __attribute__((unused)) pid,
					   long long data, char *name);
void				enumaccess(long long data);
void				enumopen(long long data);
void				enummmap(long long data);
void				eprotmap(long long data);

#endif /* !STRACE_H_ */
