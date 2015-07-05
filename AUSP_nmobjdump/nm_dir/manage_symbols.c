/*
** manage_symbols.c for nm in /home/vadee_s/rendu/AUSP_nmobjdump/nm_dir
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Apr 19 16:12:14 2015 simon vadée
** Last update Sun Apr 19 16:12:27 2015 simon vadée
*/

#include "nm.h"

static const char	*g_db[SIZE][3] =
  {
    {".bss", "B", "b"},
    {".data", "D", "d"},
    {".fini", "T", "t"},
    {".init", "T", "t"},
    {".note", "R", "r"},
    {".rodata", "R", "r"},
    {".text", "T", "t"},
    {".jcr", "D", "d"},
    {".eh_frame", "R", "r"},
    {".comment", "R", "r"},
    {".dynamic", "D", "d"},
    {".dynstr", "R", "r"},
    {".dynsym", "R", "r"},
    {".got", "D", "d"},
    {".hash", "U", "u"},
    {".interp", "G", "g"},
    {".line", "R", "r"},
    {".rel", "R", "r"},
    {".shstrtab", "R", "r"},
    {".symtab", "R", "r"},
    {".plt", "R", "r"},
    {"tors", "D", "d"}
  };

static int		store_in_list(t_disp **root, Elf64_Sym *symbol,
				      char *symbol_name)
{
  t_disp		*tmp;
  t_disp		*clist;
  t_disp		*elem;

  clist = *root;
  tmp = NULL;
  if (!(elem = malloc(sizeof(*elem))))
    {
      printf("syscall 'malloc' failed, abort\n");
      return (-1);
    }
  elem->symbol = symbol;
  elem->symbol_name = symbol_name;
  elem->next = NULL;
  while (clist != NULL && custom_strcmp(clist->symbol_name, symbol_name) <= 0)
    {
      tmp = clist;
      clist = clist->next;
    }
  elem->next = clist;
  if (tmp != NULL)
    tmp->next = elem;
  else
    *root = elem;
  return (0);
}

static char		get_symbol_type(Elf64_Sym *sym, t_elf *nm)
{
  unsigned int		i;
  Elf64_Shdr		*sec;
  char			*str;
  int			glob;

  i = 0;
  glob = (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL ? 1 : 2);
  if (strcmp(nm->string_symbol_table + sym->st_name, "data_start") == 0)
    return ('W');
  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    return (glob == 1 ? 'W' : 'w');
  sec = &(*nm).section_header[sym->st_shndx];
  str = nm->string_table + sec->sh_name;
  while (i < SIZE - 1)
    {
      if (strncmp(str, g_db[i][0], strlen(g_db[i][0])) == 0)
	return (g_db[i][glob][0]);
      ++i;
    }
  if (sym->st_shndx == SHN_UNDEF)
    return (glob == 1 ? 'U' : 'u');
  return ('?');
}

static void		display_symbols(t_elf *data, t_disp *root)
{
  t_disp		*tmp;

  tmp = root;
  while (tmp)
    {
      if (tmp->symbol->st_shndx != SHN_UNDEF)
	printf("%016x %c %3s\n", (unsigned int)tmp->symbol->st_value,
	       get_symbol_type(tmp->symbol, data), tmp->symbol_name);
      else
	printf("%18c %4s\n", get_symbol_type(tmp->symbol, data),
	       tmp->symbol_name);
      tmp = tmp->next;
    }
}

void			store_symbols(t_elf *data)
{
  unsigned int		size;
  unsigned int		i;
  t_disp		*root;

  i = 0;
  root = NULL;
  size = data->section_header[data->symbol_table_idx].sh_size
    / sizeof(Elf64_Sym);
  if (!data->symbol_table || !data->string_symbol_table)
    return ;
  while (i != size)
    {
      if (data->symbol_table[i].st_info != STT_FILE &&
	  data->string_symbol_table[data->symbol_table[i].st_name])
	store_in_list(&root, &data->symbol_table[i],
		      data->string_symbol_table
		      + data->symbol_table[i].st_name);
      ++i;
    }
  display_symbols(data, root);
}
