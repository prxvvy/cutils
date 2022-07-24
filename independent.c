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

#include "inc/independent.h"
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

bool
compare_str (char *p_str_1, char *p_str_2)
{
  if (!p_str_1)
    p_str_1 = "(null)";
  if (!p_str_2)
    p_str_2 = "(null)";

  if (strlen (p_str_1) != strlen (p_str_2))
    return false;

  unsigned int index = 0;
  while (p_str_1[index] != '\0' && p_str_2[index] != '\0')
    {
      if (p_str_1[index] != p_str_2[index])
        return false;
      index++;
    }
  return true;
}

bool
str_includes (char *p_str, char char_to_find, char *p_str_to_find)
{
  if (!p_str)
    return false;
  if (char_to_find != 00 && !p_str_to_find)
    {
      for (int i = 0; p_str[i] != '\0'; ++i)
        if (p_str[i] == char_to_find)
          return true;
      return false;
    }
  else if (char_to_find == 00 && p_str_to_find)
    {
      size_t p_str_to_find_len = strlen (p_str_to_find);
      size_t p_str_len = strlen (p_str);
      int times_found = 0;
      if (p_str_to_find_len > p_str_len)
        return false;
      for (unsigned int i = 0, j = 0; i < p_str_len; ++i)
        {
          do
            {
              if (p_str[i] == p_str_to_find[j])
                { /* If stars with same char */
                  if (++times_found == p_str_to_find_len)
                    return true; /* If got same len */
                  i++;
                  j++;
                }
              else
                {
                  i -= times_found;
                  times_found = 0;
                  j = 0;
                }
            }
          while (times_found);
        }
      return false;
    }
  return false;
}

char *
reverse_str (char *p_str)
{
  if (!p_str)
    p_str = "(null)";
  if (strlen (p_str) < 2)
    return NULL;
  char *p_reversed_str = calloc (1, sizeof (char));
  if (!p_reversed_str)
    return NULL;
  size_t p_reversed_str_len = strlen (p_reversed_str);

  for (int i = strlen (p_str) - 1; i >= 0; --i)
    {
      char *p_realloc_res = realloc (p_reversed_str, p_reversed_str_len + 2);
      if (!p_realloc_res)
        {
          free (p_reversed_str);
          p_reversed_str = NULL;
          break;
        }
      p_reversed_str = p_realloc_res;
      p_reversed_str[p_reversed_str_len++] = p_str[i];
      p_reversed_str[p_reversed_str_len] = 00;
    }
  return p_reversed_str;
}

char *
str_all_lines_from_file (FILE *p_file)
{
  char *p_line = calloc (1, sizeof (char));
  size_t p_line_len = strlen (p_line);

  char current_char;

  for (size_t i = 0; (current_char = fgetc (p_file)) != EOF; ++i)
    {
      char *p_realloc_res = realloc (p_line, p_line_len + 2);
      if (!p_realloc_res)
        {
          free (p_line);
          p_line = NULL;
          break;
        }
      p_line = p_realloc_res;
      p_line[p_line_len++] = current_char;
      p_line[p_line_len] = 00;
    }

  return p_line;
}

char *
str_line_from_file (FILE *p_file)
{
  char *p_line = calloc (1, sizeof (char));
  size_t p_line_len = strlen (p_line);

  char current_char;

  for (size_t i = 0;
       (current_char = fgetc (p_file)) != '\n' && current_char != EOF; ++i)
    {
      char *p_realloc_res = realloc (p_line, p_line_len + 2);
      if (!p_realloc_res)
        {
          free (p_line);
          p_line = NULL;
          break;
        }
      p_line = p_realloc_res;
      p_line[p_line_len++] = current_char;
      p_line[p_line_len] = 00;
    }
  if (current_char == EOF)
    {
      free (p_line);
      p_line = NULL;
    }
  return p_line;
}

char *
get_line_by_pattern (char *p_file_name, char *p_pattern)
{
  if (!p_file_name || !p_pattern)
    return NULL;
  FILE *p_file = fopen (p_file_name, "r");
  if (!p_file)
    return NULL;
  char *p_line = NULL;
  while ((p_line = str_line_from_file (p_file)))
    {
      if (str_includes (p_line, 00, p_pattern) == true)
        break;
      free (p_line);
    }
  fclose (p_file);
  return p_line;
}

list_t *
list_all_lines_from_file (char *p_file_name)
{
  list_t *p_list = create_list ();
  if (!p_list)
    return NULL;
  FILE *p_file = fopen (p_file_name, "r");
  if (!p_file)
    return NULL;

  char *p_line = NULL;

  while ((p_line = str_line_from_file (p_file)))
    {
      p_list->insert_at_end (p_list, p_line, STRING);
      free (p_line);
    }

  fclose (p_file);
  return p_list;
}

list_t *
split (char *p_str, char sep)
{
  list_t *p_main_list = create_list ();
  if (!p_main_list)
    return NULL;
  if (!sep)
    sep = ' ';
  char *p_text_element = calloc (1, sizeof (char));
  size_t p_text_element_len = strlen (p_text_element);
  for (size_t i = 0; p_str[i] != '\0'; ++i)
    {
      if (p_str[i] == sep)
        {
          if (strlen (p_text_element) != 0)
            {
              p_main_list->insert_at_end (p_main_list, p_text_element, STRING);
              free (p_text_element);
              p_text_element = NULL;
              p_text_element_len = 0;
            }
          continue;
        }
      char *p_realloc_res = realloc (p_text_element, p_text_element_len + 2);
      if (!p_realloc_res)
        {
          free (p_text_element);
          p_text_element = NULL;
          break;
        }
      p_text_element = p_realloc_res;
      p_text_element[p_text_element_len++] = p_str[i];
      p_text_element[p_text_element_len] = 00;
    }
  if (p_text_element)
    if (strlen (p_text_element) != 0)
      p_main_list->insert_at_end (p_main_list, p_text_element, STRING);

  free (p_text_element);
  return p_main_list;
}

char *
cut_str (char *p_str, unsigned int delimiter)
{
  if (!p_str)
    return NULL;
  if (delimiter > strlen (p_str) || delimiter < 0)
    return NULL;
  char *p_new_str = calloc (1, sizeof (char));
  if (!p_new_str)
    return NULL;
  size_t p_new_str_len = strlen (p_new_str);
  for (int i = 0; i != delimiter; ++i)
    {
      if (p_str[i] == 00 && i != delimiter)
        return NULL;
      char *p_realloc_res = realloc (p_new_str, p_new_str_len + 2);
      if (!p_realloc_res)
        {
          free (p_new_str);
          p_new_str = NULL;
          break;
        };
      p_new_str = p_realloc_res;
      p_new_str[p_new_str_len++] = p_str[i];
      p_new_str[p_new_str_len] = 00;
    }
  return p_new_str;
}

bool
strip (char *p_buffer, const char *p_str, const char *p_garbage)
{
  if (!p_buffer || !p_str || !p_garbage || !strlen (p_str))
    return false;

  size_t p_str_end = strlen (p_str) - 1;
  int p_str_start = 0;
  int writer = 0;

  for (int idx = (int)p_str_end; idx >= 0 && p_str[idx] == ' '; --idx)
    p_str_end--;

  for (int idx = (int)p_str_start; p_str[idx] != 00 && p_str[idx] == ' ';
       ++idx)
    p_str_start++;

  for (int idx = p_str_start; idx < (int)p_str_end + 1; ++idx)
    {

      for (int sbindx = 0; p_garbage[sbindx] != 00; ++sbindx)
        while (p_str[idx] == p_garbage[sbindx])
          p_buffer[writer] = p_str[idx++];

      p_buffer[writer++] = p_str[idx];
      p_buffer[writer] = 00;
    }

  return true;
}
