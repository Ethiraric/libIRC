/*
** irc_cmd_ping.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Thu Apr 23 16:26:18 2015 Florian SABOURIN
** Last update Thu Apr 23 16:26:18 2015 Florian SABOURIN
*/

#include "irc.h"

int		irc_cmd_ping(t_ircconnection *irc)
{
  if (!irc->cmd.argc)
    return (irc_send_formatted(irc, "PONG\r\n"));
  return (irc_send_formatted(irc, "PONG :%s\r\n",
			     irc->cmd.args[irc->cmd.argc - 1]));
}
