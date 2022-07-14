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
// Created by prxvvy on 10/04/2022
//

#include <list.h>
#include <node.h>
#include <stdlib.h>
#include <string.h>

node_t *
create_node (void *p_value, unsigned int is_string)
{
  node_t *p_self = calloc (1, sizeof (struct node));
  p_self->p_next = NULL;
  p_self->p_previous = NULL;
  if (is_string == 1)
    {
      p_self->p_value = calloc (strlen (p_value) + 1, sizeof (char));
      strcpy (p_self->p_value, p_value);
      p_self->is_containing_string = 1;
    }
  else
    {
      p_self->p_value = p_value;
      p_self->is_containing_string = 0;
    }
  return p_self;
}

int
destroy_node (node_t *p_node)
{
  if (p_node->is_containing_string == 1)
    free (p_node->p_value);
  free (p_node);
  return 1;
}
