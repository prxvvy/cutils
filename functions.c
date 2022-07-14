/* cutils - A C library that will save your time.
 * Copyright (C) 2022 prxvvy <qsk55464@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//
// Created by prxvvy on 05/07/2022
//

#include <functions.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
get_input_from_stdin (char *p_message)
{

  char *p_input = calloc (1, sizeof (char));
  if (!p_input)
    return NULL;

  if (p_message)
    printf ("%s", p_message);

  size_t p_input_len = strlen (p_input);
  int current_char;

  for (int i = 0; (current_char = getchar ()) != '\n' && current_char != EOF;
       ++i)
    {
      char *p_realloc_res = realloc (p_input, p_input_len + 2);
      if (!p_realloc_res)
        {
          free (p_input);
          p_input = NULL;
          break;
        }
      p_input = p_realloc_res;
      p_input[p_input_len++] = current_char;
      p_input[p_input_len] = '\0';
    }

  return p_input;
}

unsigned int
count_digits (int number, int base)
{
  if (!base)
    base = 10;
  if (base < 2 || base > 36)
    {
      printf ("count_digits(): Invalid base %d.\n", base);
      return false;
    }

  if (number == 0)
    return 1;

  int amount = 0;

  if (number < 0)
    amount += 1;

  while (number != 0)
    {
      number /= base;
      amount++;
    }

  return amount;
}

char *
itoa (int number, int base)
{
  if (!base)
    base = 10;
  if (base < 2 || base > 36)
    {
      printf ("itoa(): Invalid base %d.\n", base);
      return NULL;
    }

  char *p_result = calloc (count_digits (number, base) + 1, sizeof (char));
  if (!p_result)
    return NULL;
  size_t p_result_len = strlen (p_result);

  if (number == 0)
    {
      p_result[p_result_len++] = '0';
      p_result[p_result_len] = '\0';
      return p_result;
    }

  char *ptr = p_result;
  char *ptr1 = p_result;
  char tmp_char;
  int tmp_number;

  do
    {
      tmp_number = number;
      number /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopq"
               "rstuvw"
               "xyz"[35 + (tmp_number - number * base)];
    }
  while (number);
  // Apply negative sign
  if (tmp_number < 0)
    *ptr++ = '-';
  *ptr-- = '\0';
  while (ptr1 < ptr)
    {
      tmp_char = *ptr;
      *ptr-- = *ptr1;
      *ptr1++ = tmp_char;
    }

  return p_result;
}

char *
concat (char *p_format, ...)
{
  char *p_concat_str = calloc (1, sizeof (char));
  if (!p_concat_str)
    return NULL;
  va_list args;
  va_start (args, p_format);
  size_t p_concat_str_len = strlen (p_concat_str);

  for (size_t i = 0; p_format[i] != '\0'; ++i)
    {
      if (p_format[i] == '%'
          && (p_format[i + 1] == 's' || p_format[i + 1] == 'S'))
        {
          i++;
          char *p_arg_str = va_arg (args, char *);
          if (!p_arg_str)
            p_arg_str = "(null)";
          size_t p_arg_str_len = strlen (p_arg_str);
          p_concat_str_len += p_arg_str_len;
          char *p_realloc_res = realloc (p_concat_str, p_concat_str_len + 1);
          if (!p_realloc_res)
            {
              free (p_concat_str);
              p_concat_str = NULL;
              break;
            }
          p_concat_str = p_realloc_res;
          strcat (p_concat_str, p_arg_str);
          continue;
        }
      else if (p_format[i] == '%'
               && (p_format[i + 1] == 'd' || p_format[i + 1] == 'D'))
        {
          i++;
          char *p_arg_int = itoa (va_arg (args, int), 10);
          if (!p_arg_int)
            p_arg_int = 0;
          size_t p_arg_int_len = strlen (p_arg_int);
          p_concat_str_len += p_arg_int_len;
          char *p_realloc_res = realloc (p_concat_str, p_concat_str_len + 1);
          if (!p_realloc_res)
            {
              free (p_concat_str);
              p_concat_str = NULL;
              break;
            }
          p_concat_str = p_realloc_res;
          strcat (p_concat_str, p_arg_int);
          free (p_arg_int);
          continue;
        }
      char *p_realloc_res = realloc (p_concat_str, p_concat_str_len + 2);
      if (!p_realloc_res)
        {
          free (p_concat_str);
          p_concat_str = NULL;
          break;
        }
      p_concat_str = p_realloc_res;
      p_concat_str[p_concat_str_len++] = p_format[i];
      p_concat_str[p_concat_str_len] = '\0';
    }

  va_end (args);

  return p_concat_str;
}
