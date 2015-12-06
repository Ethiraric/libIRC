/*
** irc_cmd_353.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Sat Apr 18 07:40:23 2015 Florian SABOURIN
** Last update Sat Apr 18 07:40:23 2015 Florian SABOURIN
*/

#include <stdlib.h>
#include <string.h>
#include "irc.h"

static int	join_one_user(t_ircconnection *irc, t_channel *chan, char *s)
{
  t_user	*user;
  t_mode	mode;
  int		ret;

  user = malloc(sizeof(t_user));
  if (!user)
    return (1);
  new_user(user, NULL);
  while ((mode = irc_mode_mask(irc_mode_fromsym(irc, *s))))
    {
      user->chanmode |= mode;
      ++s;
    }
  if (str_newfromcstr(&user->nick, s))
    return (delete_user(user, true) | 1);
  ret = mapstring_insertnew(&chan->users, &user->nick, user);
  if (ret == 1)
    return (delete_user(user, true) | 1);
  if (ret == 2)
    delete_user(user, true);
  return (0);
}

int		irc_cmd_353(t_ircconnection *irc)
{
  t_channel	*chan;
  char		*str;
  char		*tmp;

  if (irc->cmd.argc < 4 || strcmp(str_str(&irc->nick), irc->cmd.args[0]))
    return (0);
  chan = mapstring_findcstr(&irc->chanlist, irc->cmd.args[2]);
  if (!chan)
    return (0);
  str = strdup(irc->cmd.args[irc->cmd.argc - 1]);
  if (!str)
    return (1);
  tmp = strtok(str, " ");
  while (tmp)
    {
      if (join_one_user(irc, chan, tmp))
	{
	  free(str);
	  return (1);
	}
      tmp = strtok(NULL, " ");
    }
  free(str);
  return (0);
}
