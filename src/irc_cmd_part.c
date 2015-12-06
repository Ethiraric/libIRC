/*
** irc_cmd_part.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Sat Apr 18 07:33:22 2015 Florian SABOURIN
** Last update Sat Apr 18 07:33:22 2015 Florian SABOURIN
*/

#include <string.h>
#include "irc.h"

  /* Make him part one chan at a time */
static int	left_one_chan(t_ircconnection *irc, const char *channame,
			      const char *nick)
{
  unsigned int	pos;
  t_channel	*chan;
  t_user	*user;

  pos = mapstring_findpos(&irc->chanlist, channame);
  if (pos == (unsigned int)-1)
    return (0);
  chan = mapstring_at(&irc->chanlist, pos);
  pos = mapstring_findpos(&chan->users, nick);
  if (pos == (unsigned int)-1)
    return (0);
  user = mapstring_at(&chan->users, pos);
  delete_user(user, true);
  mapstring_erasecstr(&chan->users, nick);
  return (0);
}

  /* Someone left a chan */
static int	someone_left_chan(t_ircconnection *irc)
{
  char		*begin;
  char		*end;
  char		tmp;
  int		ret;

  begin = irc->cmd.args[0];
  ret = 0;
  end = strpbrk(irc->cmd.prefix, "!@");
  if (end)
    {
      tmp = *end;
      *end = '\0';
    }
  else
    tmp = 0;
  while (*begin)
    {
      end = strchr(begin, ',');
      if (end)
	{
	  *end = 0;
	  ret |= left_one_chan(irc, begin, irc->cmd.prefix);
	  if (ret & 1)
	    {
	      *((char *)rawmemchr(irc->cmd.prefix, '\0')) = tmp;
	      return (1);
	    }
	  *end = ',';
	  begin = end + 1;
	}
      else
	{
	  ret |= left_one_chan(irc, begin, irc->cmd.prefix);
	  if (ret & 1)
	    {
	      *((char *)rawmemchr(irc->cmd.prefix, '\0')) = tmp;
	      return (1);
	    }
	  begin = rawmemchr(begin, '\0');
	}
    }
  *((char *)rawmemchr(irc->cmd.prefix, '\0')) = tmp;
  return (0);
}

  /* Parting one chan at a time */
static int	part_chan(t_ircconnection *irc, const char *channame)
{
  unsigned int	pos;
  t_channel	*chan;

  pos = mapstring_findpos(&irc->chanlist, channame);
  if (pos == (unsigned int)-1)
    return (2);
  chan = mapstring_at(&irc->chanlist, pos);
  delete_chan(chan, true);
  mapstring_erase_idx(&irc->chanlist, pos);
  return (0);
}

  /* If we parted a chan */
static int	user_part_chan(t_ircconnection *irc)
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
	  ret |= part_chan(irc, begin);
	  if (ret & 1)
	    return (1);
	  *end = ',';
	  begin = end + 1;
	}
      else
	{
	  ret |= part_chan(irc, begin);
	  if (ret & 1)
	    return (1);
	  begin = rawmemchr(begin, '\0');
	}
    }
  return (0);
}

int		irc_cmd_part(t_ircconnection *irc)
{
  if (irc->cmd.argc == 0 || !irc->cmd.prefix)
    return (0);

  /* Scan prefix to know if we parted a chan */
  if (!strncmp(str_str(&irc->nick), irc->cmd.prefix, str_size(&irc->nick)) &&
      strchr("!@", irc->cmd.prefix[str_size(&irc->nick)]))
    return (user_part_chan(irc));

  /* Or if someone else parted a chan we are in */
  return (someone_left_chan(irc));
}
