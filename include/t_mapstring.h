/*
** t_mapstring.h for  in /home/sabour_f/rendu/libIRC/include
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Wed Apr 15 00:22:04 2015 Florian SABOURIN
** Last update Wed Apr 15 00:22:04 2015 Florian SABOURIN
*/

#ifndef T_MAPSTRING_H_
# define T_MAPSTRING_H_

typedef struct s_mapstring t_mapstring;

void		mapstring_new(t_mapstring *map);
void		mapstring_delete(t_mapstring *mapstr);
int		mapstring_realloc(t_mapstring *map, size_t size);
unsigned int	mapstring_findpos(const t_mapstring *map, const char *key);
void		*mapstring_findcstr(const t_mapstring *map, const char *key);
void		*mapstring_find(const t_mapstring *map, const t_string *key);
int		mapstring_erase(t_mapstring *map, const t_string *key);
int		mapstring_erasecstr(t_mapstring *map, const char *key);
int		mapstring_erase_idx(t_mapstring *map, unsigned int idx);
int		mapstring_insert(t_mapstring *map, const t_string *key,
				 void *value);
int		mapstring_insertcstr(t_mapstring *map, const char *ckey,
				     void *value);
int		mapstring_insertnew(t_mapstring *map, const t_string *key,
				    void *value);
int		mapstring_insertnewcstr(t_mapstring *map, const char *ckey,
					void *value);
#endif /* !T_MAPSTRING_H_ */
