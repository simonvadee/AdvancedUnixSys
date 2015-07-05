/*
  vadee_s
*/

#include "strace.h"

t_graph		*init_graph()
{
  t_graph	*graph;

  graph = malloc(sizeof(t_graph));
  graph->size = 0;
  graph->head = NULL;
  graph->tail = NULL;
  return graph;
}

void		pile(t_graph *graph, char *name)
{
  t_list	*e;

  e = malloc(sizeof(t_list));
  e->name = name;
  if (graph->size == 0)
    {
      graph->size = 1;
      graph->head = e;
      graph->tail = e;
      e->next = NULL;
    }
  else
    {
      graph->size++;
      e->next = graph->head;
      graph->head = e;
    }
}

void		depile(t_graph *graph)
{
  t_list	*save;

  if (graph->size == 0)
    return;
  save = graph->head;
  if (graph->size == 1)
    {
      free(save);
      graph->head = NULL;
      graph->tail = NULL;
    }
  else
    {
      graph->head = graph->head->next;
      free(save);
    }
  graph->size--;
}
