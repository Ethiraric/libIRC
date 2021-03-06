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
#define T_STRING_H_

#include <sys/types.h>

typedef struct s_privstring
{
  unsigned int parents;
  char* str;
  size_t len;
  size_t allocd;
} t_privstring;

/*
** Holds just a "member" pointer to datas
** This is to allow copy-on-write
*/

typedef struct s_string
{
  t_privstring* m;
} t_string;

/*
** Library functions (all prefixed with "str_")
** All functions return zero on success, or a non zero integer on failure
*/

void str_new(t_string* str);
int str_newfromstr(t_string* dst, const t_string* src);
int str_newfromcstr(t_string* ret, const char* str);
int str_new_withsize(t_string* dst, size_t size);
int str_delete(t_string* ret);
int str_resize(t_string* str, size_t newsize);
int str_copy(t_string* dst, const t_string* src);
int str_assign(t_string* dst, const t_string* src);
int str_append(t_string* str, const t_string* app);
int str_appendcstr(t_string* str, const char* app);
int str_detach(t_string* str);
size_t str_size(const t_string* str);
char* str_str(const t_string* str);
const char* str_safestr(const t_string* str);

#endif /* !T_STRING_H_ */
