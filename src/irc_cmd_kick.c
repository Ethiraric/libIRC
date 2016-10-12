/*
** irc_cmd_kick.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Thu Sep  3 10:33:37 2015 Florian SABOURIN
** Last update Thu Sep  3 10:33:37 2015 Florian SABOURIN
*/

#include "irc.h"
#include <string.h>

static int we_got_kicked(t_ircconnection* irc, const char* channame)
{
  unsigned int pos;
  t_channel* chan;

  pos = mapstring_findpos(&irc->chanlist, channame);
  if (pos == (unsigned int)(-1))
    return (0);
  chan = mapstring_at(&irc->chanlist, pos);
  delete_chan(chan, true);
  mapstring_erase_idx(&irc->chanlist, pos);
  return (irc_join(irc, channame));
}

static int someone_got_kicked(t_ircconnection* irc,
                              const char* username,
                              const char* channame)
{
  unsigned int pos;
  t_channel* chan;
  t_user* user;

  pos = mapstring_findpos(&irc->chanlist, channame);
  if (pos == (unsigned int)(-1))
    return (0);
  chan = (t_channel*)mapstring_at(&irc->chanlist, pos);
  pos = mapstring_findpos(&chan->users, username);
  if (pos == (unsigned int)(-1))
    return (0);
  user = (t_user*)mapstring_at(&chan->users, pos);
  delete_user(user, true);
  mapstring_erase_idx(&chan->users, pos);
  return (0);
}

int irc_cmd_kick(t_ircconnection* irc)
{
  const char* chan;
  const char* user;

  if (irc->cmd.argc < 2)
    return (0);

  chan = irc->cmd.args[0];
  user = irc->cmd.args[1];
  if (!strcmp(irc->nick.m->str, user))
    return (we_got_kicked(irc, chan));
  return (someone_got_kicked(irc, user, chan));
}
