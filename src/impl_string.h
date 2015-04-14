/*
** impl_string.h for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Tue Apr 14 17:51:12 2015 Florian SABOURIN
** Last update Tue Apr 14 17:51:12 2015 Florian SABOURIN
*/

#ifndef IMPL_STRING_H_
# define IMPL_STRING_H_

# include <sys/types.h>
# include "t_string.h"

typedef struct	s_privstring
{
  unsigned int	parents;
  char		*str;
  size_t	len;
  size_t	allocd;
}		t_privstring;

/*
** Holds just a "member" pointer to datas
** This is to allow copy-on-write
*/

typedef struct	s_string
{
  t_privstring	*m;
}		t_string;

#endif /* !IMPL_STRING_H_ */
