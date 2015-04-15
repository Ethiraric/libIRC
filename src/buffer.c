/*
** buffer.c for  in /home/sabour_f/rendu/libIRC
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Tue Apr 14 15:49:00 2015 Florian SABOURIN
** Last update Tue Apr 14 16:09:41 2015 Florian SABOURIN
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

/* Initializes @buff */
void		buffer_new(t_buffer *buff)
{
  buff->buff = NULL;
  buff->len = 0;
  buff->allocd = 0;
}

/* Resizes @buff so that it can hold at least @newsize bytes */
int		buffer_resize(t_buffer *buff, size_t newsize)
{
  void		*tmp;

  newsize += BUFFER_STEP - (newsize & BUFFER_MASK);
  tmp = realloc(buff->buff, newsize);
  if (!tmp)
    return (1);
  buff->buff = tmp;
  buff->allocd = newsize;
  if (buff->len > newsize)
    buff->len = newsize;
  return (0);
}

/* Appends @size bytes of @data to the buffer */
int		buffer_append(t_buffer *buff, const void *data, size_t size)
{
  if (buff->len + size + 1 > buff->allocd &&
      buffer_resize(buff, buff->len + size))
    return (1);
  memcpy(&(buff->buff[buff->len]), data, size);
  buff->len += size;
  buff->buff[buff->len] = 0;
  return (0);
}

/* Removes the first @shift bytes of @buff by shifing the buffer contents
 * left from @shift bytes
 * It may realloc datas to release memory */
int		buffer_rotate(t_buffer *buff, size_t shift)
{
  if (shift < buff->len)
    {
      memmove(buff->buff, &(buff->buff[shift]), buff->len - shift);
      buff->len -= shift;
    }
  else
    buff->len = 0;
  if (buff->allocd - buff->len > 2 * BUFFER_STEP)
    return (buffer_resize(buff, buff->len + BUFFER_STEP));
  return (0);
}

/* Deletes all ressources allocated by @buff */
void		buffer_delete(t_buffer *buff)
{
  free(buff->buff);
  buff->buff = NULL;
  buff->len = 0;
  buff->allocd = 0;
}

/* Get the datas pointed by @buff (may be null) */
void		*buffer_data(t_buffer *buff)
{
  return (buff->buff);
}

/* Get the size of @buff */
size_t		buffer_size(t_buffer *buff)
{
  return (buff->len);
}

/* Get the allocated size of @buff */
size_t		buffer_allocd_size(t_buffer *buff)
{
  return (buff->allocd);
}

/* Formatted print to @buff */
int		buffer_write(t_buffer *buff, const char *fmt, ...)
{
  va_list	va;
  char		*msg;
  int		ret;

  va_start(va, fmt);
  ret = vasprintf(&msg, fmt, va);
  va_end(va);
  if (ret == -1)
    return (ret);
  if (buffer_append(buff, msg, ret))
    {
      free(msg);
      return (-1);
    }
  free(msg);
  return (ret);
}
