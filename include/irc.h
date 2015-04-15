/*
** irc.h for  in /home/sabour_f/rendu/libIRC/include
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Wed Apr 15 13:28:18 2015 Florian SABOURIN
** Last update Wed Apr 15 13:28:18 2015 Florian SABOURIN
*/

#ifndef IRC_H_
# define IRC_H_

#include <arpa/inet.h>
#include "t_mapstring.h"
#include "t_string.h"
#include "buffer.h"

typedef struct		s_ircconnection
{
  struct sockaddr_in	sin;
  t_mapstring		channels;
  t_buffer		buff_w;
  t_buffer		buff_r;
  t_string		nick;
  t_string		user;
  t_string		pass;
  t_string		realname;
  t_string		servername;
  char			*command;
  int			socket;
}			t_ircconnection;

void		irc_co_new(t_ircconnection *co);
void		irc_co_delete(t_ircconnection *co);
int		irc_connect(t_ircconnection *co, const char *hostname,
			    unsigned short port);
int		irc_set_infos(t_ircconnection *co, const char *nick,
			      const char *user,
			      const char *realname, const char *pass);
int		irc_send_infos(t_ircconnection *co);
int		irc_disconnect(t_ircconnection *co);
int		irc_send(t_ircconnection *co);
int		irc_send_raw(t_ircconnection *co, const void *dat, size_t len);
int		irc_recv(t_ircconnection *co);
int		irc_parse_command(t_ircconnection *co);
const char	*irc_get_command(const t_ircconnection *co);

#endif /* !IRC_H_ */
