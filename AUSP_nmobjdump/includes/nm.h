/*
** nm.h for nm in /home/vadee_s/rendu/AUSP_nmobjdump/includes
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Apr 19 16:11:24 2015 simon vadée
** Last update Sun Apr 19 16:11:25 2015 simon vadée
*/

#ifndef NM_H_
# define NM_H_

# include <elf.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <sys/mman.h>

typedef struct  s_elf
{
  Elf64_Ehdr    *file_header;
  Elf64_Shdr    *section_header;

  char          *string_table;

  Elf64_Sym     *symbol_table;
  char          *string_symbol_table;

  unsigned int	string_symbol_table_idx;
  unsigned int	symbol_table_idx;
}               t_elf;

typedef struct	s_disp
{
  Elf64_Sym	*symbol;
  char		*symbol_name;
  struct s_disp	*next;
}		t_disp;

#define SIZE 22

int		process_nm(char *filename);
void		store_symbols(t_elf *data);
int		custom_strcmp(char *s1, char *s2);
void		remove_underscore(char *s);
int		find_symbol_tab(t_elf *data);
int		find_str_symbol_table(t_elf *data);
char		*fill_string_table(Elf64_Ehdr *fhdr, Elf64_Shdr *section_header,
				   unsigned int shstrndx);
void		*fill_section_header(Elf64_Ehdr *fhdr, unsigned int offset);
int		filesize(int fd);

#endif /* !NM_H_ */
