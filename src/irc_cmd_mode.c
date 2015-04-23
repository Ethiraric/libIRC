/*
** irc_cmd_mode.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Wed Apr 22 18:11:23 2015 Florian SABOURIN
** Last update Wed Apr 22 18:11:23 2015 Florian SABOURIN
*/

#include "irc.h"

static int	apply_user_mode(t_user *user, bool add, char mode)
{
  t_mode	mask;

  mask = irc_mode_mask(irc_mode_fromchar(mode));
  if (add)
    user->chanmode |= mask;
  else
    user->chanmode &= ~mask;
  return (0);
}

static int	apply_modes(t_ircconnection *irc, t_channel *chan)
{
  unsigned int	it;
  t_user	*user;
  char		*modes;
  bool		add;

  modes = irc->cmd.args[1];
  if (*modes != '+' && *modes != '-')
    return (0);
  it = 2;
  while (*modes)
    {
      if (*modes == '+')
	add = true;
      else if (*modes == '-')
	add = false;
      else
	{
	  user = mapstring_findcstr(&chan->users, irc->cmd.args[it]);
	  if (user)
	    apply_user_mode(user, add, *modes);
	  ++it;
	  if (it >= irc->cmd.argc)
	    return (0);
	}
      ++modes;
    }
  return (0);
}

// TODO: handle chan modes
static int	apply_chanmodes(t_ircconnection *irc, t_channel *chan)
{
  (void)(irc);
  (void)(chan);
  return (0);
}

int		cmd_mode(t_ircconnection *irc)
{
  t_channel	*chan;

  if (irc->cmd.argc < 2)
    return (0);
  chan = mapstring_findcstr(&irc->chanlist, irc->cmd.args[0]);
  if (!chan)
    return (0);
  if (irc->cmd.argc == 2)
    return (apply_chanmodes(irc, chan));
  return (apply_modes(irc, chan));
}
