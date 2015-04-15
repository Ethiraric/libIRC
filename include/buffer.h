/*
** buffer.h for  in /home/sabour_f/rendu/libIRC
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Tue Apr 14 15:58:02 2015 Florian SABOURIN
** Last update Tue Apr 14 15:59:47 2015 Florian SABOURIN
*/

#ifndef BUFFER_H_
# define BUFFER_H_

# include <sys/types.h>

/*
** Circular buffer structure
*/

/*
** BUFFER_STEP
** The size of the buffer increases / decreases by a multiple of this
** Must be a power of two
*/

# define BUFFER_STEP	(4096)
# define BUFFER_MASK	(BUFFER_STEP - 1)

typedef struct	s_buffer
{
  char		*buff;
  size_t	len;
  size_t	allocd;
}		t_buffer;

/*
** Manipulating buffers
*/

void		buffer_new(t_buffer *buff);
int		buffer_resize(t_buffer *buff, size_t newsize);
int		buffer_append(t_buffer *buff, const void *data, size_t size);
int		buffer_rotate(t_buffer *buff, size_t shift);
void		buffer_delete(t_buffer *buff);
void		*buffer_data(t_buffer *buff);
size_t		buffer_size(t_buffer *buff);
size_t		buffer_allocd_size(t_buffer *buff);
int		buffer_write(t_buffer *buff, const char *fmt, ...);

#endif /* !BUFFER_H_ */
