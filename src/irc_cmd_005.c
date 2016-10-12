/*
** irc_cmd_005.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Tue Apr 21 11:47:57 2015 Florian SABOURIN
** Last update Tue Apr 21 11:47:57 2015 Florian SABOURIN
*/

#include "irc.h"
#include <stdlib.h>
#include <string.h>

static int cmd_005_prefix(t_ircconnection* irc, char* str)
{
  char* pos;
  char* tmp;
  size_t size;

  /* Remove previous values, if any */
  if (irc->nfo.mode_letters)
  {
    free(irc->nfo.mode_letters);
    irc->nfo.mode_letters = 0;
  }
  if (irc->nfo.mode_prefix)
  {
    free(irc->nfo.mode_prefix);
    irc->nfo.mode_letters = 0;
  }

  /* Find position of letters and symbols
   * strlen("PREFIX=(") == 8 */
  pos = str + 8;
  tmp = strchr(pos, ')');
  if (!tmp)
    return (0);
  size = tmp - pos;
  /* If we have no mode or
   * we don't have the same number of letters and symbols */
  if (!size || strlen(tmp + 1) != size)
    return (0);

  /* Assign them to their respective variable, clean up if any problem */
  irc->nfo.mode_letters = strndup(pos, size);
  irc->nfo.mode_prefix = strdup(tmp + 1);
  if (!irc->nfo.mode_letters || !irc->nfo.mode_prefix)
  {
    free(irc->nfo.mode_letters);
    irc->nfo.mode_letters = 0;
    return (1);
  }
  return (0);
}

int irc_cmd_005(t_ircconnection* irc)
{
  unsigned int i;

  i = 0;
  while (i < irc->cmd.argc)
  {
    if (!strcmp("NAMESX", irc->cmd.args[i]) &&
        irc_send_raw(irc, "PROTOCTL NAMESX\r\n", 17))
      return (1);
    else if (!strncmp("PREFIX=", irc->cmd.args[i], 7) &&
             cmd_005_prefix(irc, irc->cmd.args[i]))
      return (1);

    ++i;
  }
  return (0);
}
