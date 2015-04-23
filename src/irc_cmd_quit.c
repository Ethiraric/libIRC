/*
** irc_cmd_quit.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Wed Apr 22 11:51:29 2015 Florian SABOURIN
** Last update Wed Apr 22 11:51:29 2015 Florian SABOURIN
*/

#include <string.h>
#include "irc.h"

static int	quit_one_chan(t_ircconnection *irc, t_channel *chan)
{
  size_t	pos;
  t_user	*user;

  pos = mapstring_findpos(&chan->users, irc->cmd.prefix);
  if (pos == (unsigned int)-1)
    return (0);
  user = mapstring_at(&chan->users, pos);
  delete_user(user, true);
  mapstring_erase_idx(&chan->users, pos);
  return (0);
}

int		cmd_quit(t_ircconnection *irc)
{
  size_t	it;
  char		*end;
  char		tmp;

  end = strpbrk(irc->cmd.prefix, "@!");
  if (end)
    {
      tmp = *end;
      *end = '\0';
    }
  else
    tmp = 0;
  it = 0;
  while (it < mapstring_size(&irc->chanlist))
    {
      quit_one_chan(irc, mapstring_at(&irc->chanlist, it));
      ++it;
    }
  *end = tmp;
  return (0);
}
