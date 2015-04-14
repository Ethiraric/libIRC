/*
** mapstring.c for  in /home/sabour_f/rendu/libIRC/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Tue Apr 14 18:40:30 2015 Florian SABOURIN
** Last update Tue Apr 14 18:40:30 2015 Florian SABOURIN
*/

#include <stdlib.h>
#include <string.h>
#include "t_mapstring.h"

  /* New */

void				mapstring_new(t_mapstring *map)
{
  static const t_mapstring	model =
  {
    (void *)(0),
    0,
    0,
    10
  };

  *map = model;
}

  /* Delete */

void		mapstring_delete(t_mapstring *mapstr)
{
  unsigned int	i;

  i = 0;
  while (i < mapstr->len)
    {
      str_delete(&(mapstr->tab[i].key));
      ++i;
    }
  free(mapstr->tab);
  mapstr->tab = NULL;
  mapstr->len = 0;
  mapstr->allocd = 0;
}

  /* Realloc */

int		mapstring_realloc(t_mapstring *map, size_t size)
{
  void		*newptr;

  if (!(newptr = realloc(map->tab, sizeof(t_mapstringpair) * size)))
    return (1);
  map->tab = newptr;
  map->allocd = size;
  return (0);
}

  /* Find */

unsigned int	mapstring_findpos(const t_mapstring *map, const char *key)
{
  unsigned int	lbound;
  unsigned int	ubound;
  unsigned int	pos;
  int		cmp;

  if (!map->len)
    return ((unsigned int)(-1));
  lbound = 0;
  ubound = map->len;
  /* Using bisection method */
  while (ubound - lbound > 1)
    {
      pos = (lbound + ubound) / 2;
      cmp = strcmp(str_safestr(&map->tab[pos].key), key);
      if (cmp > 0)
	ubound = pos;
      else if (cmp < 0)
	lbound = pos;
      else
	return (pos);
    }
  /* From here, we have only two strings left to compare */
  if (!strcmp(str_safestr(&map->tab[lbound].key), key))
    return (lbound);
  if (ubound < map->len && !strcmp(str_safestr(&map->tab[ubound].key), key))
    return (ubound);
  return ((unsigned int)(-1));
}

void		*mapstring_findcstr(const t_mapstring *map, const char *key)
{
  unsigned int	pos;

  pos = mapstring_findpos(map, key);
  if (pos == (unsigned int)(-1))
    return (NULL);
  return (map->tab[pos].value);
}

void		*mapstring_find(const t_mapstring *map, const t_string *key)
{
  unsigned int	pos;

  pos = mapstring_findpos(map, str_safestr(key));
  if (pos == (unsigned int)(-1))
    return (NULL);
  return (&(map->tab[pos].value));
}

  /* Erase */

int		mapstring_erase(t_mapstring *map, const t_string *key)
{
  unsigned int	pos;

  pos = mapstring_findpos(map, str_safestr(key));
  if (pos == (unsigned int)(-1))
    return (1);
  str_delete(&(map->tab[pos].key));
  memmove(&(map->tab[pos]), &(map->tab[pos + 1]),
      (map->len - pos) * sizeof(t_mapstringpair));
  --(map->len);
  if (map->allocd - map->len > 2 * map->alloc_step)
    return (mapstring_realloc(map, map->allocd - map->alloc_step));
  return (0);
}

int		mapstring_erasecstr(t_mapstring *map, const char *key)
{
  unsigned int	pos;

  pos = mapstring_findpos(map, key);
  if (pos == (unsigned int)(-1))
    return (1);
  str_delete(&(map->tab[pos].key));
  memmove(&(map->tab[pos]), &(map->tab[pos + 1]),
      (map->len - pos) * sizeof(t_mapstringpair));
  --(map->len);
  if (map->allocd - map->len > 2 * map->alloc_step)
    return (mapstring_realloc(map, map->allocd - map->alloc_step));
  return (0);
}

int		mapstring_erase_idx(t_mapstring *map, unsigned int idx)
{
  if (idx == (unsigned int)(-1))
    return (0);
  if (idx > map->len)
    return (1);
  str_delete(&(map->tab[idx].key));
  memmove(&map->tab[idx], &map->tab[idx + 1],
      (map->len - idx) * sizeof(t_mapstringpair));
  --(map->len);
  if (map->allocd - map->len > 2 * map->alloc_step)
    return (mapstring_realloc(map, map->allocd - map->alloc_step));
  return (0);
}

  /* Insert */

static int	mapstring_insertat(t_mapstring *map, unsigned int idx,
				   const t_string *key, void *value)
{
  t_string	cpy;

  if (str_newfromstr(&cpy, key))
    return (1);
  memmove(&(map->tab[idx + 1]), &(map->tab[idx]),
      (map->len - idx) * sizeof(t_mapstringpair));
  map->tab[idx].key = cpy;
  map->tab[idx].value = value;
  ++(map->len);
  return (0);
}

static unsigned int	mapstring_insertfindpos(const t_mapstring *map,
						const t_string *key)
{
  unsigned int	lbound;
  unsigned int	ubound;
  unsigned int	pos;
  int		cmp;
  const char	*keystr;

  lbound = 0;
  ubound = map->len;
  pos = (ubound + lbound) / 2;
  /* Using bisection method */
  keystr = str_safestr(key);
  while (ubound - lbound > 1)
    {
      cmp = strcmp(str_safestr(&map->tab[pos].key), keystr);
      if (cmp > 0)
	ubound = pos;
      else if (cmp < 0)
	lbound = pos;
      else
	return (pos);
      pos = (ubound + lbound) / 2;
    }
  /* We now have two contiguous cells in our tab
   * The key can be one of it, or before / between / after the cells */
  cmp = strcmp(str_safestr(&map->tab[pos].key), keystr);
  /* Before / at the first cell */
  if (cmp >= 0)
    return (pos);
  /* If pos was the last cell */
  if (pos + 1 == map->len)
    return (pos + 1);
  ++pos;
  cmp = strcmp(str_safestr(&map->tab[pos].key), keystr);
  /* Between / at the second cell */
  if (cmp >= 0)
    return (pos);
  /* After the two cells */
  return (pos + 1);
}

int		mapstring_insert(t_mapstring *map, const t_string *key,
				 void *value)
{
  unsigned int	pos;

  if (map->allocd - map->len < 1 &&
      mapstring_realloc(map, map->allocd + map->alloc_step))
    return (1);
  if (!map->len)
    {
      if (str_newfromstr(&(map->tab[0].key), key))
	return (1);
      map->tab[0].value = value;
      ++map->len;
      return (0);
    }
  pos = mapstring_insertfindpos(map, key);
  if (pos < map->len)
    {
      if (!strcmp(str_safestr(&map->tab[pos].key), str_safestr(key)))
	{
	  map->tab[pos].value = value;
	  return (0);
	}
      return (mapstring_insertat(map, pos, key, value));
    }
  ++map->len;
  map->tab[pos].value = value;
  return (str_newfromstr(&map->tab[pos].key, key));
}

int		mapstring_insertcstr(t_mapstring *map, const char *ckey,
				     void *value)
{
  t_string	key;
  int		ret;

  if (str_newfromcstr(&key, ckey))
    return (1);
  ret = mapstring_insert(map, &key, value);
  str_delete(&key);
  return (ret);
}

int		mapstring_insertnew(t_mapstring *map, const t_string *key,
				    void *value)
{
  unsigned int	pos;

  if (map->allocd - map->len < 1 &&
      mapstring_realloc(map, map->allocd + map->alloc_step))
    return (1);
  if (!map->len)
    {
      if (str_newfromstr(&(map->tab[0].key), key))
	return (1);
      map->tab[0].value = value;
      ++map->len;
      return (0);
    }
  pos = mapstring_insertfindpos(map, key);
  if (pos < map->len)
    {
      if (!strcmp(str_safestr(&map->tab[pos].key), str_safestr(key)))
	return (2);
      return (mapstring_insertat(map, pos, key, value));
    }
  return (str_newfromstr(&map->tab[pos].key, key));
}

int		mapstring_insertnewcstr(t_mapstring *map, const char *ckey,
					void *value)
{
  t_string	key;
  int		ret;

  if (str_newfromcstr(&key, ckey))
    return (1);
  ret = mapstring_insertnew(map, &key, value);
  str_delete(&key);
  return (ret);
}
