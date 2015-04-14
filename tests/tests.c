/*
** tests.c for  in /home/sabour_f/rendu/libIRC
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Wed Apr 15 00:48:34 2015 Florian SABOURIN
** Last update Wed Apr 15 01:05:46 2015 Florian SABOURIN
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "t_mapstring.h"
#include "t_string.h"

#define nb_strings (sizeof(test_strings) / sizeof(const char *))

#define TEST_CHAIN1	"coucou"
#define TEST_CHAIN2	"toto"
#define TEST_CHAIN3	"yolo"
#define TEST_PTR1	((void *)(42))
#define TEST_PTR2	((void *)(69))
#define TEST_PTR3	((void *)(1337))
#define TEST_NOTKEY	"wefhiqponfujopwifunhjoffheif"

const char *test_strings[] =
{
  TEST_CHAIN1, TEST_CHAIN2, TEST_CHAIN3, "abc", "aab", "zzz", "titi", "tutu"
};

void *test_ptrs[] =
{
  TEST_PTR1, TEST_PTR2, TEST_PTR3,
  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL
};

const char *ordered_strings[nb_strings] = {0};

void		print_tstring(t_string str)
{
  printf("===== %p =====\n", str.m);
  if (str.m)
    {
      printf("\tstr addr     : %p\n", (void *)(str.m->str));
      printf("\tstr parents  : %u\n", str.m->parents);
      printf("\tstr len      : %u\n", (unsigned int)(str.m->len));
      printf("\tstr          : %s\n", str.m->str);
    }
  printf("===== %p =====\n", str.m);
}

int		test_tstring()
{
  char		*duplicate;
  t_string	a;
  t_string	b;
  t_string	c;

  if (!(duplicate = malloc(2*strlen(test_strings[0]) + 1)))
    {
      fprintf(stderr, "Cannot allocate duplicate.\n");
      return (1);
    }
  *duplicate = 0;
  strcat(duplicate, test_strings[0]);
  strcat(duplicate, test_strings[0]);

  /* ---------------------------------------------- */

  // Act
  if (str_newfromcstr(&a, test_strings[0]))
    {
      fprintf(stderr, "Failed to create a\n");
      return (1);
    }

  // Assert
  assert(a.m != NULL);
  assert(a.m->len == strlen(test_strings[0]));
  assert(!strcmp(a.m->str, test_strings[0]));
  assert(a.m->parents == 1);

  /* ---------------------------------------------- */

  // Act
  str_new(&b);
  if (str_copy(&b, &a))
    {
      fprintf(stderr, "Failed to create b\n");
      return (1);
    }

  // Assert
  assert(a.m != NULL);
  assert(a.m->len == strlen(test_strings[0]));
  assert(!strcmp(a.m->str, test_strings[0]));
  assert(a.m->parents == 2);
  assert(b.m == a.m);

  /* ---------------------------------------------- */

  // Act
  str_new(&c);
  if (str_copy(&c, &b))
    {
      fprintf(stderr, "Failed to create c\n");
      return (1);
    }

  // Assert
  assert(a.m != NULL);
  assert(a.m->len == strlen(test_strings[0]));
  assert(!strcmp(a.m->str, test_strings[0]));
  assert(a.m->parents == 3);
  assert(b.m == a.m);
  assert(c.m == a.m);

  /* ---------------------------------------------- */

  // Act
  if (str_append(&c, &b))
    {
      fprintf(stderr, "Failed to append b to c\n");
      return (1);
    }

  // Assert
  assert(a.m != NULL);
  assert(a.m->len == strlen(test_strings[0]));
  assert(!strcmp(a.m->str, test_strings[0]));
  assert(a.m->parents == 2);
  assert(b.m == a.m);
  assert(c.m != NULL);
  assert(c.m->len == 2 * strlen(test_strings[0]));
  assert(!strcmp(c.m->str, duplicate));
  assert(c.m->parents == 1);

  /* ---------------------------------------------- */

  // Act
  str_delete(&a);

  // Assert
  assert(a.m == NULL);
  assert(b.m->len == strlen(test_strings[0]));
  assert(!strcmp(b.m->str, test_strings[0]));
  assert(b.m->parents == 1);
  assert(c.m != NULL);
  assert(c.m->len == 2 * strlen(test_strings[0]));
  assert(!strcmp(c.m->str, duplicate));
  assert(c.m->parents == 1);

  /* ---------------------------------------------- */

  // Act
  str_delete(&b);

  // Assert
  assert(a.m == NULL);
  assert(b.m == NULL);
  assert(c.m != NULL);
  assert(c.m->len == 2 * strlen(test_strings[0]));
  assert(!strcmp(c.m->str, duplicate));
  assert(c.m->parents == 1);

  /* ---------------------------------------------- */

  // Act
  str_delete(&c);

  // Assert
  assert(a.m == NULL);
  assert(b.m == NULL);
  assert(c.m == NULL);

  /* ---------------------------------------------- */

  // Act
  if (str_newfromcstr(&a, test_strings[0]) ||
      str_copy(&b, &a) ||
      str_detach(&b))
    {
      fprintf(stderr, "An allocation error occured\n");
      return (1);
    }

  // Assert
  assert(a.m != NULL);
  assert(b.m != NULL);
  assert(a.m != b.m);
  assert(a.m->str != b.m->str);
  assert(a.m->parents == 1);
  assert(b.m->allocd == strlen(test_strings[0]) + 1);
  assert(b.m->parents == 1);
  assert(b.m->len == strlen(test_strings[0]));

  /* ---------------------------------------------- */

  str_delete(&a);
  str_delete(&b);
  free(duplicate);
  return (0);
}

int		test_tmapstring()
{
  t_mapstringpair	*pair;
  t_mapstring		map;
  unsigned int		i, j;

  // Act
  mapstring_new(&map);

  // Assert
  assert(map.allocd == 0);
  assert(map.len == 0);
  assert(map.tab == (void *)0);

  /* ---------------------------------------------- */

  // Act
  if (mapstring_insertcstr(&map, test_strings[0],test_ptrs[0]))
    {
      fprintf(stderr, "Failed to insert string1 to map\n");
      return (1);
    }

  // Assert
  assert(map.tab != NULL);
  assert(map.len == 1);
  assert(map.allocd == map.alloc_step);
  assert(map.tab[0].key.m != NULL);
  assert(map.tab[0].key.m->str != NULL);
  assert(map.tab[0].key.m->parents == 1);
  assert(!strcmp(map.tab[0].key.m->str, test_strings[0]));
  assert(map.tab[0].value == test_ptrs[0]);

  /* ---------------------------------------------- */

  // Act
  if (mapstring_insertcstr(&map, test_strings[1], test_ptrs[1]))
    {
      fprintf(stderr, "Failed to insert string2 to map\n");
      return (1);
    }

  // Assert
  assert(map.tab != NULL);
  assert(map.len == 2);
  if (map.alloc_step > 1)
    assert(map.allocd == map.alloc_step);
  else
    assert(map.allocd == map.len);
  assert(map.tab[0].key.m != NULL);
  assert(map.tab[0].key.m->str != NULL);
  assert(map.tab[1].key.m != NULL);
  assert(map.tab[1].key.m->str != NULL);
  assert(strcmp(map.tab[0].key.m->str, map.tab[1].key.m->str) != 0);
  if (strcmp(test_strings[0], test_strings[1]) < 0)
    {
      assert(strcmp(map.tab[0].key.m->str, test_strings[0]) == 0);
      assert(map.tab[0].value == test_ptrs[0]);
      assert(map.tab[0].key.m->parents == 1);
      assert(strcmp(map.tab[1].key.m->str, test_strings[1]) == 0);
      assert(map.tab[1].value == test_ptrs[1]);
      assert(map.tab[1].key.m->parents == 1);
    }
  else
    {
      assert(strcmp(map.tab[0].key.m->str, test_strings[1]) == 0);
      assert(map.tab[0].value == test_ptrs[1]);
      assert(map.tab[0].key.m->parents == 1);
      assert(strcmp(map.tab[1].key.m->str, test_strings[0]) == 0);
      assert(map.tab[1].value == test_ptrs[0]);
      assert(map.tab[1].key.m->parents == 1);
    }

  /* ---------------------------------------------- */

  // Act
  for (i = 2 ; i < nb_strings ; ++i)
    if (mapstring_insertcstr(&map, test_strings[i], test_ptrs[i]))
      {
	fprintf(stderr, "Failed to insert string%d : \"%s\"\n", i, test_strings[i]);
	return (1);
      }

  // Assert
  assert(map.len == nb_strings);
  assert(map.allocd == ((nb_strings + (map.alloc_step - 1)) / map.alloc_step) * map.alloc_step);
  for (i = 0 ; i < nb_strings ; ++i)
    {
      assert(map.tab[i].key.m != NULL);
      assert(map.tab[i].key.m->allocd > strlen(ordered_strings[i]));
      assert(map.tab[i].key.m->len == strlen(ordered_strings[i]));
      assert(map.tab[i].key.m->str != NULL);
      assert(!strcmp(map.tab[i].key.m->str, ordered_strings[i]));
    }

  /* ---------------------------------------------- */

  for (i = 0 ; i < nb_strings ; ++i)
    {
      // Act
      pair = mapstring_findcstr(&map,  test_strings[i]);

      // Assert
      for (j = 0 ;j < nb_strings ; ++j)
	if (!strcmp(str_safestr(&map.tab[i].key), ordered_strings[j]))
	  assert(pair == test_ptrs[j]);
      assert(map.len == nb_strings);
    }

  /* ---------------------------------------------- */

  // Act
  pair = mapstring_findcstr(&map, TEST_NOTKEY);

  // Assert
  assert(pair == NULL);
  assert(map.len == nb_strings);

  /* ---------------------------------------------- */

  // Act
  if (mapstring_insertcstr(&map, test_strings[0], test_ptrs[1]))
    {
      fprintf(stderr, "Failed to modify value of string0\n");
      return (1);
    }

  // Assert
  pair = mapstring_findcstr(&map, test_strings[0]);
  assert(pair == test_ptrs[1]);
  assert(map.len == nb_strings);

  /* ---------------------------------------------- */

  // Act
  assert(!mapstring_erasecstr(&map, ordered_strings[0]));

  // Assert
  assert(map.len == nb_strings - 1);
  assert(!strcmp(map.tab[0].key.m->str, ordered_strings[1]));
  assert(mapstring_findcstr(&map, ordered_strings[0]) == NULL);

  /* ---------------------------------------------- */

  // Act
  mapstring_delete(&map);

  // Assert
  assert(map.allocd == 0);
  assert(map.len == 0);
  assert(map.tab == NULL);

  return (0);
}

void		reorder_strings()
{
  unsigned int	max;
  unsigned int	i, j;

  max = sizeof(test_strings) / sizeof(const char *);
  for (i = 0 ; i < max ; ++i)
    ordered_strings[i] = test_strings[i];
  for (i = 0 ; i < max ; ++i)
    for (j = 0 ; j < max - 1 ; ++j)
      if (strcmp(ordered_strings[j], ordered_strings[j+1]) > 0)
	{
	  const char *tmp = ordered_strings[j];
	  ordered_strings[j] = ordered_strings[j+1];
	  ordered_strings[j+1] = tmp;
	}
}

int		main(int argc, char **argv)
{
  int		ret;
  unsigned int	i;

  if (nb_strings < 2)
    {
      fprintf(stderr, "Not enough test strings.\n");
      return (1);
    }

  reorder_strings();
  printf("Strings ordered\n");
  if (argc == 2 && !strcmp(argv[1], "--print-strings"))
    {
      printf("=== Ordered strings ===\n");
      for (i = 0 ; i < sizeof(test_strings) / sizeof(const char *) ; ++i)
	printf("[%d] %s\n", i, ordered_strings[i]);
      printf("=== Ordered strings ===\n\n");
    }
  if ((ret = test_tstring()) ||
      (ret = test_tmapstring()))
    return (ret);
  printf("Everything is OK !\n");
  return (0);
}
