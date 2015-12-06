/*
** irc_cmd_join.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Fri Apr 17 00:29:19 2015 Florian SABOURIN
** Last update Fri Apr 17 00:29:19 2015 Florian SABOURIN
*/

#include <stdlib.h>
#include <string.h>
#include "irc.h"

  /* Add a user in a chan */
static int	user_join_chan(t_ircconnection *irc, const char *channame)
{
  t_channel	*chan;
  t_user	*user;
  int		ret;

  chan = mapstring_findcstr(&irc->chanlist, channame);
  if (!chan)
    return (0);
  user = malloc(sizeof(t_channel));
  if (!user)
    return (1);
  new_user(user, irc->cmd.prefix);
  ret = mapstring_insertnew(&chan->users, &user->nick, user);
  if (ret)
    {
      str_delete(&user->nick);
      free(user);
      return (ret);
    }
  return (0);
}

  /* If someone joined a chan we are in */
static int	new_user_in_chan(t_ircconnection *irc)
{
  char		*begin;
  char		*end;
  int		ret;

  begin = irc->cmd.args[0];
  ret = 0;
  while (*begin)
    {
      end = strchr(begin, ',');
      if (end)
	{
	  *end = 0;
	  ret |= user_join_chan(irc, begin);
	  if (ret & 1)
	    return (1);
	  *end = ',';
	  begin = end + 1;
	}
      else
	{
	  ret |= user_join_chan(irc, begin);
	  if (ret & 1)
	    return (1);
	  begin = rawmemchr(begin, '\0');
	}
    }
  return (0);
}

  /* Joining one chan at a time */
static int	join_chan(t_ircconnection *irc, const char *channame)
{
  t_channel	*chan;
  int		ret;

  chan = malloc(sizeof(t_channel));
  if (!chan)
    return (1);
  new_chan(chan);;
  if (str_newfromcstr(&chan->name, channame))
    return (delete_chan(chan, 1) | 1);
  ret = mapstring_insertnew(&irc->chanlist, &chan->name, chan);
  if (ret)
    {
      str_delete(&chan->name);
      free(chan);
      return (ret);
    }
  return (0);
}

  /* If we joined a new chan */
static int	user_join_new_chan(t_ircconnection *irc)
{
  char		*begin;
  char		*end;
  int		ret;

  begin = irc->cmd.args[0];
  ret = 0;
  while (*begin)
    {
      end = strchr(begin, ',');
      if (end)
	{
	  *end = 0;
	  ret |= join_chan(irc, begin);
	  if (ret & 1)
	    return (1);
	  *end = ',';
	  begin = end + 1;
	}
      else
	{
	  ret |= join_chan(irc, begin);
	  if (ret & 1)
	    return (1);
	  begin = rawmemchr(begin, '\0');
	}
    }
  return (0);
}

int		irc_cmd_join(t_ircconnection *irc)
{
  if (irc->cmd.argc == 0 || !irc->cmd.prefix)
    return (0);

  /* Scan prefix to know if we joined a chan */
  if (!strncmp(str_str(&irc->nick), irc->cmd.prefix, str_size(&irc->nick)) &&
      strchr("!@", irc->cmd.prefix[str_size(&irc->nick)]))
    return (user_join_new_chan(irc));

  /* Or if someone else joined a chan we are in */
  return (new_user_in_chan(irc));
}
