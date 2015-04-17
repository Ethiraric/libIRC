/*
** user.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Fri Apr 17 00:29:14 2015 Florian SABOURIN
** Last update Fri Apr 17 00:29:14 2015 Florian SABOURIN
*/

#include <stdlib.h>
#include <string.h>
#include "irc.h"

int		new_user(t_user *user, char *prefix)
{
  char		*pos;
  char		tmp;

  memset(user, 0, sizeof(t_user));
  if (prefix)
    {
      pos = prefix + strcspn(prefix, "@!");
      tmp = *pos;
      *pos = '\0';
      if (str_newfromcstr(&user->nick, prefix))
	return (1);
      *pos = tmp;
      if (tmp == '!')
	{
	  prefix = pos + 1;
	  pos = strchrnul(prefix, '@');
	  tmp = *pos;
	  *pos = '\0';
	  if (str_newfromcstr(&user->user, prefix))
	    {
	      str_delete(&user->nick);
	      return (1);
	    }
	  *pos = tmp;
	}
      if (tmp == '@')
	{
	  if (str_newfromcstr(&user->host, pos + 1))
	    {
	      str_delete(&user->nick);
	      str_delete(&user->user);
	      return (1);
	    }
	}
    }
  return (0);
}

int		delete_user(t_user *user, bool free_struct)
{
  str_delete(&user->nick);
  str_delete(&user->user);
  str_delete(&user->host);
  str_delete(&user->realname);
  if (free_struct)
    free(user);
  return (0);
}
