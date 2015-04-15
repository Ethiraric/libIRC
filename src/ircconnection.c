/*
** ircconnection.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Wed Apr 15 13:37:14 2015 Florian SABOURIN
** Last update Wed Apr 15 13:37:14 2015 Florian SABOURIN
*/

#include <error.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "irc.h"

  /* New */

void		irc_co_new(t_ircconnection *co)
{
  memset(co, 0, sizeof(t_ircconnection));
}

  /* Delete */

void		irc_co_delete(t_ircconnection *co)
{
  mapstring_delete(&co->channels);
  buffer_delete(&co->buff_r);
  buffer_delete(&co->buff_w);
  str_delete(&co->nick);
  str_delete(&co->user);
  str_delete(&co->realname);
  str_delete(&co->servername);
}

  /* Connect */

int		irc_connect(t_ircconnection *co, const char *hostname,
			    unsigned short port)
{
  struct hostent	*hostinfo;

  hostinfo = gethostbyname(hostname);
  if (!hostinfo)
    return (1);
  if (str_newfromcstr(&co->servername, hostname))
    return (1);
  co->socket = socket(AF_INET, SOCK_STREAM, 0);
  if (co->socket < 0)
    return (1);
  co->sin.sin_addr = *((struct in_addr *)hostinfo->h_addr);
  co->sin.sin_port = htons(port);
  co->sin.sin_family = AF_INET;
  if (connect(co->socket, (struct sockaddr *)&co->sin, sizeof(co->sin)) == -1)
    {
      str_delete(&co->servername);
      close(co->socket);
      return (1);
    }
  return (0);
}

  /* Basic informations */

int		irc_set_infos(t_ircconnection *co, const char *nick,
			      const char *user, const char *realname,
			      const char *pass)
{
  if (str_newfromcstr(&co->nick, nick))
    return (1);
  if (str_newfromcstr(&co->user, user))
    {
      str_delete(&co->nick);
      return (1);
    }
  if (str_newfromcstr(&co->realname, realname))
    {
      str_delete(&co->nick);
      str_delete(&co->user);
      return (1);
    }
  if (pass)
    {
      if (str_newfromcstr(&co->pass, pass))
	{
	  str_delete(&co->nick);
	  str_delete(&co->user);
	  str_delete(&co->realname);
	  return (1);
	}
    }
  else
    str_new(&co->pass);
  return (0);
}

int		irc_send_infos(t_ircconnection *co)
{
  if (str_str(&co->pass))
    {
      if (buffer_write(&co->buff_w,
		       "PASS %s\r\nNICK %s\r\nUSER %s %s 127.0.0.1 :%s\r\n",
		       str_str(&co->pass), str_str(&co->nick),
		       str_str(&co->user), str_str(&co->user),
		       str_str(&co->realname)) == -1)
	return (1);
    }
  else
    {
      if (buffer_write(&co->buff_w,
		       "NICK %s\r\nUSER %s %s 127.0.0.1 :%s\r\n",
		       str_str(&co->nick),str_str(&co->user),
		       str_str(&co->user), str_str(&co->realname)) == -1)
	return (1);
    }
  return (0);
}

  /* Disconnect */

/* Note that disconnect does NOT release memory
 * Please use irc_co_delete before creating a new connection */
int		irc_disconnect(t_ircconnection *co)
{
  if (close(co->socket))
    return (1);
  return (0);
}

  /* Sending datas */

int		irc_send(t_ircconnection *co)
{
  int		ret;

  if (!buffer_size(&co->buff_w))
    return (0);
  ret = write(co->socket, buffer_data(&co->buff_w), buffer_size(&co->buff_w));
  if (ret == -1)
    return (1);
  if (buffer_rotate(&co->buff_w, (size_t)ret))
    return (1);
  return (0);
}

int		irc_send_raw(t_ircconnection *co, const void *dat, size_t len)
{
  if (buffer_append(&co->buff_w, dat, len))
    return (1);
  return (0);
}

  /* Recieving datas */

int		irc_recv(t_ircconnection *co)
{
  static char	buff[512];
  int		ret;

  ret = recv(co->socket, buff, 512, MSG_DONTWAIT);
  if (ret == -1)
    return (0);
  if (buffer_append(&co->buff_r, buff, ret))
    return (1);
  return(0);
}

  /* Parsing */

int		irc_parse_command(t_ircconnection *co)
{
  size_t	len;
  char		*pos;
  char		*end;

  free(co->command);
  co->command = 0;
  if ((pos = memchr(buffer_data(&co->buff_r), '\n', buffer_size(&co->buff_r))))
    {
      end = pos + 1;
      if ((void *)pos > buffer_data(&co->buff_r) && *(pos - 1) == '\r')
	--pos;
      len = (void *)pos - buffer_data(&co->buff_r);
      co->command = malloc(len + 1);
      if (!co->command)
	return (1);
      memcpy(co->command, buffer_data(&co->buff_r), len);
      co->command[len] = 0;
      buffer_rotate(&co->buff_r, (void *)end - buffer_data(&co->buff_r));
    }
  return (0);
}

const char	*irc_get_command(const t_ircconnection *co)
{
  return (co->command);
}