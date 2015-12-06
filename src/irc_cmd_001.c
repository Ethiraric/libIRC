/*
** irc_cmd_001.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Sun Dec 06 08:43:50 2015 Florian SABOURIN
** Last update Sun Dec 06 08:43:50 2015 Florian SABOURIN
*/

#include "irc.h"

/*
** When we receive 001 message
** This means that the server accepted our connection
*/
int		cmd_001(t_ircconnection *irc)
{
  irc->accepted = true;
  return (0);
}
