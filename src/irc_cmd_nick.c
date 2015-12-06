/*
** irc_cmd_nick.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Tue Jul 21 03:23:48 2015 Florian SABOURIN
** Last update Tue Jul 21 03:23:48 2015 Florian SABOURIN
*/

#include "irc.h"

static int	change_one_chan(t_channel *chan, char *oldnick, char *newnick)
{
  t_string	nickstr;
  t_user	*user;

  user = (t_user *)mapstring_findcstr(&chan->users, oldnick);
  if (!user)
    return (0);
  if (str_newfromcstr(&nickstr, newnick))
    return (1);
  if (mapstring_insert(&chan->users, &nickstr, user))
    {
      str_delete(&nickstr);
      return (1);
    }
  mapstring_erasecstr(&chan->users, oldnick);
  str_delete(&user->nick);
  str_assign(&user->nick, &nickstr);
  return (0);
}

int		irc_cmd_nick(t_ircconnection *irc)
{
  unsigned int	i;
  t_channel	*chan;

  if (!irc->cmd.argc)
    return (0);
  for (i = 0 ; i < mapstring_size(&irc->chanlist) ; ++i)
    {
      chan = (t_channel *)mapstring_at(&irc->chanlist, i);
      if (change_one_chan(chan, irc->cmd.prefixnick, irc->cmd.args[0]))
	return (1);
    }
  return (0);
}
