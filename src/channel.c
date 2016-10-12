/*
** channel.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Fri Apr 17 00:29:16 2015 Florian SABOURIN
** Last update Fri Apr 17 00:29:16 2015 Florian SABOURIN
*/

#include "irc.h"
#include <stdlib.h>
#include <string.h>

void new_chan(t_channel* chan)
{
  memset(chan, 0, sizeof(t_channel));
  mapstring_new(&chan->users);
}

int delete_chan(t_channel* chan, bool free_struct)
{
  size_t it;

  it = 0;
  while (it < mapstring_size(&chan->users))
  {
    delete_user(mapstring_at(&chan->users, it), true);
    ++it;
  }
  mapstring_delete(&chan->users);
  str_delete(&chan->name);
  str_delete(&chan->topic);
  if (free_struct)
    free(chan);
  return (0);
}
