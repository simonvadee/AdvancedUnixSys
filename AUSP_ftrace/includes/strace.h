/*
** strace.h for strace in /home/vadee_s/rendu/AUSP_strace
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun May 17 19:08:25 2015 simon vadée
** Last update Sat Jul  4 11:05:34 2015 Cédric Voinnet
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

# define NB_SYSCALL	301

# define SYSCALL	"red"
# define CALL_FCT	"lightblue2"

typedef struct			s_list
{
  char				*name;
  struct s_list			*next;
}				t_list;

typedef struct			s_graph
{
  t_list			*head;
  t_list			*tail;
  unsigned int			size;
}				t_graph;

typedef struct			s_data
{
  pid_t				pid;
  int				fd;
  long				peektext;
}				t_data;

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


void				set_fd(int fd);
int				manage_signal();
const char			*getsig(int sig);
void				signal_handler(int sig);
char				*find_cmd(char *cmd);
void				trace_child(char *cmd, char **arg);
void				trace_process(pid_t pid, char launch);
int				is_dead(pid_t pid, int status);
int				get_infos_process(pid_t pid, int status, int fd, t_graph *graph);
char				*parse_path(char *path, char *cmd);
void				depile(t_graph *graph);
t_graph				*init_graph();
void				build_graph(int fd, t_graph *graph, char *dest);
void				pile(t_graph *graph, char *name);
int				begin_graph();
void				write_graph(int, char *, char *, char *);
void				graph_end(int);
#endif /* !STRACE_H_ */
