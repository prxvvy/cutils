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

#include "inc/list.h"
#include "inc/node.h"
#include <stdlib.h>

list_t *
create_list ()
{
  list_t *p_self = calloc (1, sizeof (struct list));
  if (!p_self)
    return ((void *)0);
  p_self->p_head = ((void *)0);
  p_self->p_tail = ((void *)0);
  p_self->size = 0;
  p_self->get_len = get_len;
  p_self->destroy_list = destroy_list;
  p_self->destroy_each_node = destroy_each_node;
  p_self->insert_at_beginning = insert_at_beginning;
  p_self->insert_at_end = insert_at_end;
  p_self->insert_at = insert_at;
  p_self->remove_at_beginning = remove_at_beginning;
  p_self->remove_at_end = remove_at_end;
  p_self->first_entry = first_entry;
  p_self->get_node_at = get_node_at;
  p_self->unlink_node = unlink_node;
  return p_self;
}

unsigned int
get_len (list_t *p_list)
{
  return p_list->size;
}

node_t *
insert_at_beginning (list_t *p_list, void *p_value, type type)
{
  node_t *p_new_node = create_node (p_value, type);

  if ((!p_new_node))
    return ((void *)0);

  if (p_list->get_len (p_list) == 0)
    return p_list->first_entry (p_list, p_new_node);

  p_new_node->p_next = p_list->p_head;
  p_list->p_head->p_previous = p_new_node;
  p_list->p_head = p_new_node;
  p_list->p_tail->p_next = p_list->p_head;
  p_list->p_head->p_previous = p_list->p_tail;

  p_list->size++;

  return p_new_node;
}

node_t *
insert_at_end (list_t *p_list, void *p_value, type type)
{
  node_t *p_new_node = create_node (p_value, type);

  if (!p_new_node)
    return ((void *)0);

  if (p_list->get_len (p_list) == 0)
    return first_entry (p_list, p_new_node);

  p_list->p_tail->p_next = p_new_node;
  p_new_node->p_previous = p_list->p_tail;
  p_list->p_tail = p_new_node;
  p_list->p_head->p_previous = p_list->p_tail;
  p_list->p_tail->p_next = p_list->p_head;

  p_list->size++;

  return p_new_node;
}

node_t *
remove_at_beginning (list_t *p_list)
{
  if (p_list->get_len (p_list) == 0)
    return ((void *)0);
  if (p_list->get_len (p_list) == 1)
    {
      node_t *p_node_to_destroy = p_list->p_head;
      p_list->p_head = ((void *)0);
      p_list->p_tail = ((void *)0);
      p_node_to_destroy->p_next = ((void *)0);
      p_node_to_destroy->p_previous = ((void *)0);
      p_list--;
      return p_node_to_destroy;
    }

  node_t *p_node_to_destroy = p_list->p_head;
  p_list->p_head = p_list->p_head->p_next;
  p_list->p_head->p_previous = p_list->p_tail;
  p_list->p_tail->p_next = p_list->p_head;
  p_node_to_destroy->p_next = ((void *)0);
  p_node_to_destroy->p_previous = ((void *)0);
  p_list->size--;
  return p_node_to_destroy;
}

node_t *
remove_at_end (list_t *p_list)
{
  if (p_list->get_len (p_list) == 0)
    return ((void *)0);
  if (p_list->get_len (p_list) == 1)
    {
      node_t *p_node_to_destroy = p_list->p_head;
      p_list->p_head = ((void *)0);
      p_list->p_tail = ((void *)0);
      p_list->size--;
      return p_node_to_destroy;
    }

  node_t *p_node_to_destroy = p_list->p_tail;
  p_list->p_tail = p_list->p_tail->p_previous;
  p_list->p_tail->p_next = p_list->p_head;
  p_list->p_head->p_previous = p_list->p_tail;
  p_node_to_destroy->p_previous = ((void *)0);
  p_node_to_destroy->p_next = ((void *)0);
  p_list->size--;
  return p_node_to_destroy;
}

node_t *
remove_at (list_t *p_list, unsigned int index)
{
  if (p_list->get_len (p_list) == 0)
    return ((void *)0);
  if (p_list->get_len (p_list) != 0 && index > p_list->get_len (p_list))
    return ((void *)0);
  if (!index)
    return remove_at_end (p_list);
  if (index == 0)
    return p_list->remove_at_beginning (p_list);

  unsigned int i = 0;

  node_t *p_node_ptr = p_list->p_head;

  while (i != index)
    {
      p_node_ptr = p_node_ptr->p_next;
      i++;
      if (i != index && p_node_ptr == p_list->p_head)
        return ((void *)0);
    }

  if (p_node_ptr == p_list->p_tail)
    return p_list->remove_at_end (p_list);
  else if (p_node_ptr == p_list->p_head)
    return p_list->remove_at_beginning (p_list);
  else
    {
      node_t *p_node_to_destroy = p_node_ptr;
      p_node_to_destroy->p_previous->p_next = p_node_to_destroy->p_next;
      p_node_to_destroy->p_next->p_previous = p_node_to_destroy->p_previous;
      p_node_to_destroy->p_previous = ((void *)0);
      p_node_to_destroy->p_next = ((void *)0);
      p_list->size--;
      return p_node_to_destroy;
    }
}

node_t *
first_entry (list_t *p_list, node_t *p_node)
{
  /* Have the new node be the new head and tail of the list because it's
   * empty. */
  p_list->p_head = p_node;
  p_list->p_tail = p_node;

  /* We know as for now, it's the only node in the list, so we do this. */
  p_list->p_head->p_previous
      = p_list->p_tail; /* Have it point itself as, currently, it's the only
                           node therefore, head and tail should point each
                           other */
  p_list->p_tail->p_next = p_list->p_head;

  p_list->size++; /* Increment size of the list. */
  return p_node;
}

bool
destroy_list (list_t *p_list)
{
  free (p_list);
  return true;
}

bool
destroy_each_node (list_t *p_list)
{
  if (p_list->get_len (p_list) == 0)
    return false;
  node_t *p_node = p_list->p_head;

  for (unsigned int i = 0; i < p_list->get_len (p_list); ++i)
    {
      node_t *p_tmp = p_node;
      p_node = p_node->p_next;
      p_tmp->destroy_node (p_tmp);
    }

  return true;
}

node_t *
get_node_at (list_t *p_list, unsigned int index)
{
  if (p_list->get_len (p_list) == 0)
    return ((void *)0);

  if (index > p_list->get_len (p_list))
    return ((void *)0);

  node_t *p_node = p_list->p_head;

  for (unsigned int i = 0; i < p_list->get_len (p_list); ++i)
    {
      if (i == index)
        return p_node;
      p_node = p_node->p_next;
    }

  return ((void *)0);
}

node_t *
unlink_node (list_t *p_list, node_t *p_node)
{
  if (p_list->get_len (p_list) == 0)
    return ((void *)0);

  if (p_node == p_list->p_head)
    {
      node_t *p_toDestroy = p_list->p_head;

      p_list->p_tail->p_next = p_list->p_head->p_next;
      p_list->p_head = p_list->p_head->p_next;
      p_list->p_head->p_previous = p_list->p_tail;

      p_list->size--;
      return p_toDestroy;
    }
  else if (p_node == p_list->p_tail)
    {
      node_t *p_toDestroy = p_list->p_tail;

      p_list->p_head->p_previous = p_list->p_tail->p_previous;
      p_list->p_tail = p_list->p_tail->p_previous;
      p_list->p_tail->p_next = p_list->p_head;

      p_list->size--;

      return p_toDestroy;
    }
  else
    {
      p_node->p_previous->p_next = p_node->p_next;
      p_node->p_next->p_previous = p_node->p_previous;

      p_list->size--;

      return p_node;
    }
}

node_t *
insert_at (list_t *p_list, void *p_value, unsigned int index, type type)
{
  node_t *p_new_node = create_node (p_value, type);

  if (!p_new_node)
    return ((void *)0);

  if (index == 0 && p_list->get_len (p_list) == 0)
    return p_list->first_entry (p_list, p_new_node);

  else if (index == 0 && p_list->get_len (p_list) != 0)
    return p_list->insert_at_beginning (p_list, p_value, type);

  node_t *p_node = p_list->p_head;

  index -= 1;

  for (unsigned int i = 0; i < p_list->get_len (p_list); ++i)
    {
      if (i == index)
        break;
      p_node = p_node->p_next;
    }

  if (p_node == p_list->p_tail)
    return p_list->insert_at_end (p_list, p_value, type);
  else
    {
      p_node->p_next->p_previous = p_new_node;
      p_new_node->p_next = p_node->p_next;
      p_node->p_next = p_new_node;
      p_new_node->p_previous = p_node;
      p_list->size++;
    }
  return p_new_node;
}
