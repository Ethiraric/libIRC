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

static const char	*cmdtab[] =
{
  "JOIN", "PART", "QUIT", "MODE", "005", "353", NULL
};

static int (* const fcttab[])(t_ircconnection *irc) =
{
  &cmd_join, &cmd_part, &cmd_quit, &cmd_mode, &cmd_005, &cmd_353, NULL
};

int		irc_handle_cmd(t_ircconnection *irc, bool eval)
{
  unsigned int	i;

  if (eval && irc_eval_cmd(irc))
    return (1);
  i = 0;
  while (cmdtab[i])
    {
      if (!strcasecmp(irc->cmd.cmd, cmdtab[i]))
	return (fcttab[i](irc));
      ++i;
    }
  return (0);
}
