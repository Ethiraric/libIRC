/*
** mode_utils.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Tue Apr 21 13:05:23 2015 Florian SABOURIN
** Last update Tue Apr 21 13:05:24 2015 Florian SABOURIN
*/

#include <string.h>
#include "irc.h"

void		irc_modes_tosyms(t_mode mode, char *dst)
{

}

t_mode		irc_mode_fromchar(int c)
{
  switch (c)
    {
      case 'v':
	return (MODE_V);
      case 'h':
	return (MODE_H);
      case 'o':
	return (MODE_O);
      case 'a':
	return (MODE_A);
      case 'q':
	return (MODE_Q);
      default:
	return (MODE_MAX);
    }
}

t_mode		irc_mode_mask(t_mode in)
{
  if (in < MODE_MAX)
    return (1 << in);
  return (0);
}

t_mode		irc_mode_fromsym(t_ircconnection *irc, int c)
{
  size_t	pos;
  char		*tmp;

  tmp = strchr(irc->nfo.mode_prefix, c);
  if (!tmp)
    return (MODE_MAX);
  pos = tmp - irc->nfo.mode_prefix;
  return (irc_mode_fromchar(irc->nfo.mode_letters[pos]));
}
