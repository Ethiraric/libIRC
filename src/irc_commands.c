/*
** irc_commands.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Thu Apr 16 13:36:56 2015 Florian SABOURIN
** Last update Thu Apr 16 13:36:56 2015 Florian SABOURIN
*/

#include <stdio.h>
#include <stdlib.h>
#include "irc.h"

int		irc_join(t_ircconnection *co, const char *chans)
{
  return (irc_send_formatted(co, "JOIN %s\r\n", chans));
}

int		irc_part(t_ircconnection *co, const char *chans)
{
  return (irc_send_formatted(co, "PART %s\r\n", chans));
}

int		irc_quit(t_ircconnection *co, const char *reason)
{
  return (irc_send_formatted(co, "QUIT %s\r\n", reason));
}
