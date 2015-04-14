/*
** t_string.h for  in /home/sabour_f/rendu/libIRC/include
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Tue Apr 14 18:05:36 2015 Florian SABOURIN
** Last update Tue Apr 14 18:05:58 2015 Florian SABOURIN
*/

#ifndef T_STRING_H_
# define T_STRING_H_

# include <sys/types.h>

typedef struct s_string t_string;

/*
** Library functions (all prefixed with "str_")
** All functions return zero on success, or a non zero integer on failure
*/

t_string	str_new();
int		str_newfromstr(t_string *dst, const t_string *src);
int		str_newfromcstr(t_string *ret, const char *str);
int		str_delete(t_string *ret);
size_t		str_size(t_string *str);
int		str_resize(t_string *str, size_t newsize);
int		str_copy(t_string *dst, const t_string *src);
int		str_append(t_string *str, t_string *app);
int		str_appendcstr(t_string *str, const char *app);
int		str_detach(t_string *str);
size_t		str_size(t_string *str);
char		*str_str(t_string *str);
char		*str_sagestr(t_string *str);

#endif /* !T_STRING_H_ */
