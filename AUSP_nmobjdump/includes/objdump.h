/*
** objdump.h for objdump in /home/vadee_s/rendu/AUSP_nmobjdump/includes
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Apr 19 16:11:35 2015 simon vadée
** Last update Sun Apr 19 16:11:39 2015 simon vadée
*/

#ifndef OBJDUMP_H_
# define OBJDUMP_H_

# include <fcntl.h>
# include <elf.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/mman.h>

void		display_flags(Elf64_Ehdr *data, Elf64_Shdr *shdr);
void		display_infos(Elf64_Ehdr *data, char *filename);
int		process_objdump(char *filename);
char		*fill_string_table(Elf64_Ehdr *fhdr, Elf64_Shdr *section_header,
				   unsigned int shstrndx);
void		*fill_section_header(Elf64_Ehdr *fhdr, unsigned int offset);
int		filesize(int fd);

#endif /* !OBJDUMP_H_ */
