/*
** irc_eval_cmd.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Thu Apr 16 16:18:41 2015 Florian SABOURIN
** Last update Thu Apr 16 16:18:41 2015 Florian SABOURIN
*/

#include "irc.h"
#include <stdlib.h>
#include <string.h>

int free_cmd(t_ircconnection* irc)
{
  free(irc->cmd.args);
  irc->cmd.args = 0;
  free(irc->cmd.dup);
  irc->cmd.dup = 0;
  free(irc->cmd.prefixnick);
  irc->cmd.prefixnick = 0;
  irc->cmd.prefix = 0;
  irc->cmd.cmd = 0;
  irc->cmd.argc = 0;
  return (0);
}

/* strtok that takes into account the ':' meaning the trailing parameter */
static char* olds;
static char* mstrtok(char* s, const char* delim)
{
  char* token;

  if (s == NULL)
    s = olds;
  s += strspn(s, delim);
  if (*s == '\0')
  {
    olds = s;
    return NULL;
  }
  if (*s == ':')
  {
    token = s + 1;
    olds = rawmemchr(token, '\0');
    return (token);
  }
  token = s;
  s = strpbrk(token, delim);
  if (s == NULL)
    olds = rawmemchr(token, '\0');
  else
  {
    *s = '\0';
    olds = s + 1;
  }
  return (token);
}

static int irc_eval_args(t_ircconnection* irc, char* str)
{
  size_t i;

  /* If there is no argument */
  if (!mstrtok(str, " "))
    return (0);

  /* Otherwise count them */
  irc->cmd.argc = 1;
  while (mstrtok(NULL, " "))
    ++irc->cmd.argc;

  /* Allocate a null-terminated array */
  irc->cmd.args = malloc(sizeof(char*) * (irc->cmd.argc + 1));
  if (!irc->cmd.args)
    return (free_cmd(irc) | 1);
  i = 0;

  /* Fill it */
  while (i < irc->cmd.argc - 1)
  {
    irc->cmd.args[i] = str;
    str = rawmemchr(str, '\0') + 1;
    ++i;
  }
  irc->cmd.args[i] = (*str == ':' ? str + 1 : str);
  irc->cmd.args[i + 1] = NULL;
  return (0);
}

int irc_eval_cmd(t_ircconnection* irc)
{
  char* now;
  char* unused;
  int ret;

  if (!irc->command)
    return (0);
  free_cmd(irc);
  if (!(irc->cmd.dup = strdup(irc->command)))
    return (1);
  now = strtok(irc->cmd.dup, " ");
  if (!now)
    return (0);
  if (*now == ':')
  {
    irc->cmd.prefix = now + 1;
    now = strtok(NULL, " ");
    if (!now)
      return (free_cmd(irc));
    irc->cmd.prefixnick = strdup(irc->cmd.prefix);
    if (!irc->cmd.prefixnick)
      return (free_cmd(irc) | 1);
    irc->cmd.prefixnick = strtok_r(irc->cmd.prefixnick, "@!", &unused);
  }
  irc->cmd.cmd = now;
  ret = irc_eval_args(irc, strtok(0, ""));
  return (ret);
}
