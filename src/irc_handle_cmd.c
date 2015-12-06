/*
** irc_handle_cmd.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Thu Apr 16 20:21:04 2015 Florian SABOURIN
** Last update Thu Apr 16 20:21:04 2015 Florian SABOURIN
*/

#include <stdlib.h>
#include <string.h>
#include "irc.h"

static unsigned int	stattab[] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

static const char	*cmdtab[] =
{
  "PING", "JOIN", "PART", "QUIT", "MODE", "005", "353",
  "NICK", "KICK",
  NULL
};

static int (* const fcttab[])(t_ircconnection *irc) =
{
  &irc_cmd_ping, &irc_cmd_join, &irc_cmd_part, &irc_cmd_quit, &irc_cmd_mode, &irc_cmd_005, &irc_cmd_353,
  &irc_cmd_nick, &irc_cmd_kick,
  NULL
};

int		irc_handle_cmd(t_ircconnection *irc, bool eval)
{
  unsigned int	i;

  if (eval && irc_eval_cmd(irc))
    return (1);
  if (!strcasecmp(irc->cmd.cmd, "PRIVMSG"))
    return (0);
  i = 0;
  while (cmdtab[i])
    {
      if (!strcasecmp(irc->cmd.cmd, cmdtab[i]))
	{
	  ++(stattab[i]);
	  return (fcttab[i](irc));
	}
      ++i;
    }
  return (0);
}

#include <stdio.h>
void		irc_dump_stats()
{
  unsigned int	i;

  i = 0;
  while (cmdtab[i])
    {
      if (stattab[i])
	printf("%s -> %u calls\n", cmdtab[i], stattab[i]);
      ++i;
    }
}
