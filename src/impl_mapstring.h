/*
** impl_mapstring.h for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Tue Apr 14 18:40:52 2015 Florian SABOURIN
** Last update Tue Apr 14 18:40:53 2015 Florian SABOURIN
*/

#ifndef IMPL_MAPSTRING_H_
# define IMPL_MAPSTRING_H_

# include "t_string.h"
# include "impl_string.h"

typedef struct	s_mapstringpair
{
  t_string	key;
  void		*value;
}		t_mapstringpair;

typedef struct		s_mapstring
{
  t_mapstringpair	*tab;
  size_t		len;
  size_t		allocd;
  size_t		alloc_step;
}			t_mapstring;

#endif /* !IMPL_MAPSTRING_H_ */
