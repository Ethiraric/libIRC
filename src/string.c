/*
** string.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Tue Apr 14 17:50:05 2015 Florian SABOURIN
** Last update Tue Apr 14 17:50:05 2015 Florian SABOURIN
*/

#include <stdlib.h>
#include <string.h>
#include "t_string.h"

  /* New functions*/

void		str_new(t_string *str)
{
  static const t_string	model =
  {
    (void *)(0)
  };

  *str = model;
}

int		str_newfromstr(t_string *dst, const t_string *src)
{
  dst->m = src->m;
  ++(dst->m->parents);
  return (0);
}

int		str_newfromcstr(t_string *ret, const char *str)
{
  ret->m = malloc(sizeof(t_privstring));
  if (!ret->m)
    return (1);
  ret->m->str = strdup(str);
  if (!ret->m->str)
    {
      free(ret->m);
      return (1);
    }
  ret->m->len = strlen(str);
  ret->m->parents = 1;
  ret->m->allocd = ret->m->len + 1;
  return (0);
}

int		str_new_withsize(t_string *dst, size_t size)
{
  dst->m = malloc(sizeof(t_privstring));
  if (!dst->m)
    return (1);
  dst->m->str = malloc(size);
  if (!dst->m->str)
    {
      free(dst->m);
      return (1);
    }
  dst->m->allocd = size;
  dst->m->len = 0;
  *(dst->m->str) = '\0';
  dst->m->parents = 1;
  return (0);
}

  /* Delete */

int		str_delete(t_string *ret)
{
  if (!ret->m)
    return (0);
  if (ret->m->parents == 1)
    {
      free(ret->m->str);
      free(ret->m);
    }
  else
    ret->m->parents--;
  ret->m = NULL;
  return (0);
}

  /* Detach */
int		str_detach(t_string *str)
{
  char		*newstr;
  t_privstring	*mem;

  if (!str->m || str->m->parents == 1)
    return (0);
  if (!(newstr = strdup(str->m->str)))
    return (1);
  if (!(mem = malloc(sizeof(t_privstring))))
    {
      free(newstr);
      return (1);
    }
  --(str->m->parents);
  mem->allocd = str->m->len + 1;
  mem->len = str->m->len;
  mem->parents = 1;
  mem->str = newstr;
  str->m = mem;
  return (0);
}


  /* Copy */

int		str_copy(t_string *dst, const t_string *src)
{
  if (dst->m)
    str_delete(dst);
  dst->m = src->m;
  if (src->m)
    ++(src->m->parents);
  return (0);
}

  /* Assign */

int		str_assign(t_string *dst, const t_string *src)
{
  dst->m = src->m;
  return (0);
}

  /* Resize */

int		str_resize(t_string *str, size_t newsize)
{
  void		*tmp;

  if (!str->m)
    return (str_new_withsize(str, newsize));
  if (str_detach(str))
    return (1);
  if ((tmp = realloc(str->m->str, newsize + 1)) == NULL)
    return (1);
  str->m->str = (char *)(tmp);
  str->m->str[newsize] = '\0';
  str->m->allocd = newsize + 1;
  if (str->m->len >= str->m->allocd)
    str->m->len = newsize;
  return (0);
}

  /* Append */

static int	str_append_moreparents(t_string *str, const char *app)
{
  size_t	newsize;
  t_string	ret;

  newsize = str->m->len + strlen(app);
  if (str_new_withsize(&ret, newsize + 1))
    return (1);
  strcat(ret.m->str, str->m->str);
  strcat(ret.m->str, app);
  str_delete(str);
  str->m = ret.m;
  str->m->len = newsize;
  return (0);
}

static int	str_append_1parent(t_string *str, const char *app)
{
  size_t	newsize;
  char		*newstr;

  newsize = str->m->len + strlen(app);
  if (newsize + 1 < str->m->allocd)
    {
      strcat(str->m->str, app);
      str->m->len = newsize;
      return (0);
    }
  if (!(newstr = realloc(str->m->str, newsize + 1)))
    return (1);
  str->m->str = newstr;
  strcat(str->m->str, app);
  str->m->len = newsize;
  str->m->allocd = newsize + 1;
  return (0);
}

int		str_append(t_string *str, const t_string *app)
{
  if (str->m->parents == 1)
    return (str_append_1parent(str, app->m->str));
  return (str_append_moreparents(str, app->m->str));
}

int		str_appendcstr(t_string *str, const char *app)
{
  if (str->m->parents == 1)
    return (str_append_1parent(str, app));
  return (str_append_moreparents(str, app));
}

  /* Getters */

size_t		str_size(const t_string *str)
{
  if (str->m)
    return (str->m->len);
  return (0);
}

char		*str_str(const t_string *str)
{
  if (!str->m)
    return (NULL);
  return (str->m->str);
}

const char	*str_safestr(const t_string *str)
{
  if (!str->m)
    return ("");
  return (str->m->str);
}
