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

void		irc_modes_tosyms(t_ircconnection *irc, t_mode mode, char *dst)
{
  t_mode	mask;

  mask = 1 << (MODE_MAX - 1);
  while (mask)
    {
      if (mode & mask)
	{
	  *dst = irc_sym_fromchar(irc, irc_char_frommask(mask));
	  ++dst;
	}
      mask >>= 1;
    }
  *dst = 0;
}

char		irc_sym_fromchar(t_ircconnection *irc, char c)
{
  char		*tmp;

  tmp = strchr(irc->nfo.mode_letters, c);
  if (!tmp)
    return (0);
  return (irc->nfo.mode_prefix[tmp - irc->nfo.mode_letters]);
}

char		irc_char_frommask(t_mode mode)
{
  switch (mode)
    {
      case MODE_V_MASK:
	return ('v');
      case MODE_H_MASK:
	return ('h');
      case MODE_O_MASK:
	return ('o');
      case MODE_A_MASK:
	return ('a');
      case MODE_Q_MASK:
	return ('q');
      default:
	return (0);
    }
}

t_mode		irc_mode_fromchar(char c)
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

t_mode		irc_mode_fromsym(t_ircconnection *irc, char c)
{
  size_t	pos;
  char		*tmp;

  tmp = strchr(irc->nfo.mode_prefix, c);
  if (!tmp)
    return (MODE_MAX);
  pos = tmp - irc->nfo.mode_prefix;
  return (irc_mode_fromchar(irc->nfo.mode_letters[pos]));
}
