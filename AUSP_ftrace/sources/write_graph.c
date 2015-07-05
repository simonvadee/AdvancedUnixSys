/*
** write_graph.c for ftrace in /home/voinne_c/rendu/AUSP_ftrace/sources
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Fri Jul  3 17:02:12 2015 Cédric Voinnet
** Last update Sat Jul  4 11:16:53 2015 Cédric Voinnet
*/

#include "strace.h"

int	begin_graph()
{
  int	fd;

  if ((fd = open("graph.dot", O_TRUNC | O_CREAT | O_WRONLY, 0666)) == -1)
    return (-1);
  dprintf(fd, "digraph g{\n");
  dprintf(fd, "node [style=filled];\n");
  return (fd);
}

void	write_graph(int fd, char *from, char *to, char *color)
{
  dprintf(fd, "\t\"%s\" [label=\"%s\" color=\"%s\"", to, to, color);
  if (!strcmp(color, SYSCALL))
    dprintf(fd, " shape=diamond");
  dprintf(fd, "];\n");
  dprintf(fd, "\t\"%s\" -> \"%s\";\n", from, to);
}

void	graph_end(int fd)
{
  dprintf(fd, "}\n");
  close(fd);
}
