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
#include <stdbool.h>
#include "t_mapstring.h"
#include "t_string.h"
#include "buffer.h"

typedef unsigned int	t_mode;

  /* A user on a channel */
typedef struct	s_user
{
  t_string	nick;
  t_string	user;
  t_string	host;
  t_string	realname;
  t_mode	chanmode;
  t_mode	netmode;
}		t_user;

int		new_user(t_user *user, char *prefix);
int		delete_user(t_user *user, bool free_struct);

  /* A channel */
typedef struct	s_channel
{
  t_mapstring	users;
  t_string	topic;
  t_string	name;
  t_mode	mode;
}		t_channel;

void		new_chan(t_channel *chan);
int		delete_chan(t_channel *chan, bool free_struct);

typedef struct	s_command
{
  unsigned int	argc;
  char		*prefix;
  char		*cmd;
  char		**args;
  char		*dup;
}		t_command;

  /* Connection */
typedef struct		s_ircconnection
{
  struct sockaddr_in	sin;
  t_mapstring		chanlist;
  t_command		cmd;
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
			      const char *user, const char *realname,
			      const char *pass);
int		irc_send_infos(t_ircconnection *co);
int		irc_disconnect(t_ircconnection *co);
int		irc_send(t_ircconnection *co);
int		irc_send_raw(t_ircconnection *co, const void *dat, size_t len);
int		irc_recv(t_ircconnection *co);
int		irc_parse_command(t_ircconnection *co);
const char	*irc_get_command(const t_ircconnection *co);
int		irc_send_formatted(t_ircconnection *co, const char *fmt, ...);
int		irc_eval_cmd(t_ircconnection *irc);
int		irc_handle_cmd(t_ircconnection *irc, bool eval);
int		free_cmd(t_ircconnection *irc);

  /* Commands */
int		irc_join(t_ircconnection *co, const char *chans);
int		irc_part(t_ircconnection *co, const char *chans);
int		irc_quit(t_ircconnection *co, const char *reason);

  /* IRC commands */
int		cmd_join(t_ircconnection *irc);

#endif /* !IRC_H_ */
