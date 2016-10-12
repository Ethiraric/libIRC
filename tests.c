/*
** tests.c for  in /home/sabour_f/rendu/libIRC
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Wed Apr 15 00:48:34 2015 Florian SABOURIN
** Last update Wed Apr 15 01:05:46 2015 Florian SABOURIN
*/

#include "t_string.h"
#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_t_string()
{
  t_string a, b;

  // Act
  str_new(&a);

  // Assert
  assert(!str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_safestr(&a), ""));
  assert(!str_size(&a));

  /* ----------------------------- */

  // Act
  if (str_newfromcstr(&a, "coucou"))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "coucou"));
  assert(str_size(&a) == 6);

  /* ----------------------------- */

  // Act
  if (str_newfromstr(&b, &a))
    err(1, NULL);

  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "coucou"));
  assert(str_size(&a) == 6);
  assert(str_str(&b));
  assert(str_safestr(&b));
  assert(!strcmp(str_str(&b), "coucou"));
  assert(str_size(&b) == 6);
  assert(str_str(&a) == str_str(&b));
  assert(str_safestr(&a) == str_safestr(&b));

  /* ----------------------------- */

  // Act
  if (str_detach(&a))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "coucou"));
  assert(str_size(&a) == 6);
  assert(str_str(&b));
  assert(str_safestr(&b));
  assert(!strcmp(str_str(&b), "coucou"));
  assert(str_size(&b) == 6);
  assert(str_str(&a) != str_str(&b));
  assert(str_safestr(&a) != str_safestr(&b));

  /* ----------------------------- */

  // Act
  str_delete(&a);

  // Assert
  assert(!str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_safestr(&a), ""));
  assert(!str_size(&a));

  /* ----------------------------- */

  // Act
  str_delete(&b);

  // Assert
  assert(!str_str(&b));
  assert(str_safestr(&b));
  assert(!strcmp(str_safestr(&b), ""));
  assert(!str_size(&a));

  /* ----------------------------- */

  // Act
  str_delete(&a);

  // Assert
  assert(!str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_safestr(&a), ""));
  assert(!str_size(&a));

  /* ----------------------------- */

  // Act
  if (str_new_withsize(&a, 50))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_safestr(&a), ""));
  assert(!str_size(&a));

  /* ----------------------------- */

  // Act
  str_delete(&a);

  // Assert
  assert(!str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_safestr(&a), ""));
  assert(!str_size(&a));

  /* ----------------------------- */

  // Act
  if (str_newfromcstr(&a, "lel") || str_newfromstr(&b, &a) || str_delete(&a) ||
      str_detach(&b) || str_delete(&b))
    err(1, NULL);

  // Assert
  assert(!str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_safestr(&a), ""));
  assert(!str_size(&a));
  assert(!str_str(&b));
  assert(str_safestr(&b));
  assert(!strcmp(str_safestr(&b), ""));
  assert(!str_size(&b));

  /* ----------------------------- */

  // Act
  if (str_newfromcstr(&a, "Hello"))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "Hello"));
  assert(str_size(&a) == 5);

  /* ----------------------------- */

  // Act
  if (str_appendcstr(&a, " World!"))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "Hello World!"));
  assert(str_size(&a) == 12);

  /* ----------------------------- */

  // Act
  if (str_resize(&a, 10))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "Hello Worl"));
  assert(str_size(&a) == 10);

  /* ----------------------------- */

  // Act
  if (str_resize(&a, 50))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "Hello Worl"));
  assert(str_size(&a) == 10);

  /* ----------------------------- */

  // Act
  if (str_appendcstr(&a, "d !"))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "Hello World !"));
  assert(str_size(&a) == 13);

  /* ----------------------------- */

  // Act
  if (str_copy(&b, &a))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "Hello World !"));
  assert(str_size(&a) == 13);
  assert(str_str(&b));
  assert(str_safestr(&b));
  assert(!strcmp(str_str(&b), "Hello World !"));
  assert(str_size(&b) == 13);
  assert(str_safestr(&a) == str_safestr(&b));
  assert(str_str(&a) == str_str(&b));

  /* ----------------------------- */

  // Act
  if (str_copy(&b, &a))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "Hello World !"));
  assert(str_size(&a) == 13);
  assert(str_str(&b));
  assert(str_safestr(&b));
  assert(!strcmp(str_str(&b), "Hello World !"));
  assert(str_size(&b) == 13);
  assert(str_safestr(&a) == str_safestr(&b));
  assert(str_str(&a) == str_str(&b));

  /* ----------------------------- */

  // Act
  if (str_appendcstr(&b, " =)"))
    err(1, NULL);

  // Assert
  assert(str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_str(&a), "Hello World !"));
  assert(str_size(&a) == 13);
  assert(str_str(&b));
  assert(str_safestr(&b));
  assert(!strcmp(str_str(&b), "Hello World ! =)"));
  assert(str_size(&b) == 16);
  assert(str_safestr(&a) != str_safestr(&b));
  assert(str_str(&a) != str_str(&b));

  /* ----------------------------- */

  // Act
  str_delete(&a);
  str_delete(&b);

  // Assert
  assert(!str_str(&a));
  assert(str_safestr(&a));
  assert(!strcmp(str_safestr(&a), ""));
  assert(!str_size(&a));
  assert(!str_str(&b));
  assert(str_safestr(&b));
  assert(!strcmp(str_safestr(&b), ""));
  assert(!str_size(&b));
}

int main()
{
  test_t_string();
  printf("All the tests passed\n");
  return (0);
}
