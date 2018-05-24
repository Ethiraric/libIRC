/*
** irc_commands.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Thu Apr 16 13:36:56 2015 Florian SABOURIN
** Last update Thu Apr 16 13:36:56 2015 Florian SABOURIN
*/

#include "irc.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int irc_join(t_ircconnection* co, const char* chans)
{
  return (irc_send_formatted(co, "JOIN %s\r\n", chans));
}

int irc_part(t_ircconnection* co, const char* chans, char* reason)
{
  if (!reason)
    return (irc_send_formatted(co, "PART %s\r\n", chans));
  return (irc_send_formatted(co, "PART %s :%s\r\n", chans, reason));
}

int irc_quit(t_ircconnection* co, const char* reason)
{
  if (!reason)
    return (irc_send_formatted(co, "QUIT\r\n"));
  return (irc_send_formatted(co, "QUIT :%s\r\n", reason));
}

int irc_msgdata(t_ircconnection* co,
                const char* dst,
                const char* msg,
                size_t len)
{
  return (irc_send_formatted(co, "PRIVMSG %s :", dst) ||
          irc_send_raw(co, msg, len) || irc_send_raw(co, "\r\n", 2));
}

int irc_msg(t_ircconnection* co, const char* dst, const char* msg)
{
  return (irc_send_formatted(co, "PRIVMSG %s :%s\r\n", dst, msg));
}

int irc_msgf(t_ircconnection* co, const char* dst, const char* fmt, ...)
{
  va_list va;
  char* msg;
  int ret;

  va_start(va, fmt);
  ret = vasprintf(&msg, fmt, va);
  va_end(va);
  if (ret == -1)
    return (1);
  ret = irc_msg(co, dst, msg);
  free(msg);
  return (ret);
}

int irc_mode(t_ircconnection* co,
             const char* chan,
             const char* modes,
             const char* nicks)
{
  if (!chan)
    return (irc_send_formatted(co, "MODE %s\r\n", modes));
  if (!nicks)
    return (irc_send_formatted(co, "MODE %s %s\r\n", chan, modes));
  return (irc_send_formatted(co, "MODE %s %s %s\r\n", chan, modes, nicks));
}

int irc_voice(t_ircconnection* co, const char* chan, const char* nick)
{
  return (irc_send_formatted(co, "MODE %s +v %s\r\n", chan, nick));
}

int irc_devoice(t_ircconnection* co, const char* chan, const char* nick)
{
  return (irc_send_formatted(co, "MODE %s -v %s\r\n", chan, nick));
}

int irc_hop(t_ircconnection* co, const char* chan, const char* nick)
{
  return (irc_send_formatted(co, "MODE %s +h %s\r\n", chan, nick));
}

int irc_dehop(t_ircconnection* co, const char* chan, const char* nick)
{
  return (irc_send_formatted(co, "MODE %s -h %s\r\n", chan, nick));
}

int irc_op(t_ircconnection* co, const char* chan, const char* nick)
{
  return (irc_send_formatted(co, "MODE %s +o %s\r\n", chan, nick));
}

int irc_deop(t_ircconnection* co, const char* chan, const char* nick)
{
  return (irc_send_formatted(co, "MODE %s -o %s\r\n", chan, nick));
}

int irc_admin(t_ircconnection* co, const char* chan, const char* nick)
{
  return (irc_send_formatted(co, "MODE %s +a %s\r\n", chan, nick));
}

int irc_deadmin(t_ircconnection* co, const char* chan, const char* nick)
{
  return (irc_send_formatted(co, "MODE %s -a %s\r\n", chan, nick));
}

int irc_creator(t_ircconnection* co, const char* chan, const char* nick)
{
  return (irc_send_formatted(co, "MODE %s +q %s\r\n", chan, nick));
}

int irc_decreator(t_ircconnection* co, const char* chan, const char* nick)
{
  return (irc_send_formatted(co, "MODE %s -q %s\r\n", chan, nick));
}
