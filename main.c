/*
** main.c for  in /home/sabour_f/rendu/libIRC
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Wed Apr 15 16:55:44 2015 Florian SABOURIN
** Last update Wed Apr 15 16:55:45 2015 Florian SABOURIN
*/

#include <errno.h>
#include <error.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "irc.h"

int	handle_input(t_ircconnection *irc, char *cmd)
{
  int	ret;
  char	*msg;

  if (*cmd != '/')
    {
      ret = asprintf(&msg, "%s\r\n", cmd);
      if (ret == -1)
	error(1, errno, "asprintf");
      if (irc_send_raw(irc, msg, ret))
	error(1, errno, "malloc");
      free(msg);
      return (0);
    }
  else
    {
      ++cmd;
      if (!strncasecmp(cmd, "join", 4))
	{
	  msg = strtok(cmd + 4, " ");
	  if (msg)
	    return (irc_join(irc, msg));
	  fprintf(stderr, "Missing args for join\n");
	  return (0);
	}
      if (!strncasecmp(cmd, "part", 4))
	{
	  msg = strtok(cmd + 4, " ");
	  if (msg)
	    return (irc_join(irc, msg));
	  fprintf(stderr, "Missing args for part\n");
	  return (0);
	}
      if (!strncasecmp(cmd, "dump", 4))
	{
	  size_t i;

	  for (i = 0 ; i < irc->chanlist.len ; ++i)
	    {
	      t_channel *chan;
	      size_t j;

	      printf("== Chan : `%s`\n", str_str(&irc->chanlist.tab[i].key));
	      chan = irc->chanlist.tab[i].value;
	      for (j = 0 ; j < chan->users.len ; ++j)
		{
		  char syms[12];

		  irc_modes_tosyms(irc, ((t_user *)chan->users.tab[j].value)->chanmode, syms);
		  printf("\tUser : `%s` (%s)\n", str_str(&chan->users.tab[j].key),
			 syms);
		}
	    }
	}
    }
  return (0);
}

int	loop(t_ircconnection *irc)
{
  char	*cmd;
  char	*end;
  size_t	l;

  (void)irc;
  cmd = NULL;
  end = NULL;
  l = 0;
  errno = 0;
  printf(">> ");
  while (getline(&cmd, &l, stdin) && *cmd)
    {
      end = strchr(cmd, 0);
      *(--end) = 0;
      if (*cmd && handle_input(irc, cmd))
	error(1, errno, "malloc");
      if (irc_send(irc))
	error(1, errno, "irc_send");
      if (irc_recv(irc) == 1)
	error(1, errno, "irc_recv");
      if (irc_parse_command(irc))
	error(1, errno, "malloc");
      if (irc_get_command(irc))
	{
	  if (irc_eval_cmd(irc))
	    {
	      perror("irc_eval_cmd");
	      return (1);
	    }
	  printf("<< %s\n", irc_get_command(irc));
	  if (irc_handle_cmd(irc, false))
	    {
	      perror("irc_handle_cmd");
	      return (1);
	    }
	}
      free(cmd);
      cmd = NULL;
      printf(">> ");
    }
  free(cmd);
  return (0);
}

int	main(int argc, char **argv)
{
  unsigned int	port = 0;
  const char	*hostname = 0;
  const char	*user = 0;
  const char	*nick = 0;
  const char	*realname = 0;
  const char	*pass = 0;
  int		c;

  setbuf(stdout, NULL);
  if (argc == 2 && !strcmp("--help", argv[1]))
    {
      fprintf(stderr,
	      "Usage : %s [OPTIONS]\n"
	      "\t-p port - The port on which to connect (mandatory)\n"
	      "\t-h host - The host on which to connect (mandatory)\n"
	      "\t-u user - Your username (mandatory)\n"
	      "\t-n nick - Your nickname (mandatory)\n"
	      "\t-r real - Your real name (mandatory)\n"
	      "\t-P pass - Password to connect (optionnal)\n",
	      argv[1]);
      return (1);
    }
  while ((c = getopt(argc, argv, "p:h:u:n:r:P:")) != -1)
    {
      if (c == 'p')
	{
	  port = atoi(optarg);
	  if (port > USHRT_MAX || !port)
	    {
	      fprintf(stderr, "Invalid port : %u\n", port);
	      return (1);
	    }
	}
      else if (c == 'h')
	hostname = optarg;
      else if (c == 'u')
	user = optarg;
      else if (c == 'n')
	nick = optarg;
      else if (c == 'r')
	realname = optarg;
      else if (c == 'P')
	pass = optarg;
      else
	  return (1);
    }
  if (!port)
    fprintf(stderr, "Missing port\n");
  else if (!hostname)
    fprintf(stderr, "Missing hostname\n");
  else if (!hostname)
    fprintf(stderr, "Missing hostname\n");
  else if (!user)
    fprintf(stderr, "Missing user\n");
  else if (!nick)
    fprintf(stderr, "Missing nick\n");
  else if (!realname)
    fprintf(stderr, "Missing realname\n");
  else
    {
      t_ircconnection	irc;

      irc_co_new(&irc);
      if (irc_connect(&irc, hostname, port))
	{
	  perror("irc_connect");
	  return (1);
	}
      if (irc_set_infos(&irc, nick, user, realname, pass) ||
	  irc_send_infos(&irc))
	{
	  perror("malloc");
	  return (1);
	}
      printf("Now connected to %s\n", hostname);
      loop(&irc);
      irc_disconnect(&irc);
      irc_co_delete(&irc);
      irc_dump_stats();
      return (0);
    }
  return (1);
}
