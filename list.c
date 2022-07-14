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

list_t *
create_list ()
{
  list_t *p_self = calloc (1, sizeof (struct list));
  p_self->p_head = NULL;
  p_self->p_tail = NULL;
  p_self->size = 0;
  return p_self;
}

unsigned int
get_len (list_t *p_list)
{
  return p_list->size;
}

int
insert_at_beginning (list_t *p_list, void *p_value, unsigned int is_string)
{
  node_t *p_new_node
      = create_node (p_value, is_string); /* Create a new node. */

  if (get_len (p_list) == 0)
    return first_entry (p_list, p_new_node);

  p_new_node->p_next = p_list->p_head; /* Next pointer of new node points to
                                         the current head of the list. */
  p_list->p_head->p_previous = p_new_node;
  p_list->p_head = p_new_node; /* Update the head of the list. */
  p_list->p_tail->p_next
      = p_list->p_head; /* The tail of the list is still pointing to the old
                           head so update the next pointer of the tail to new
                           the head. */
  p_list->p_head->p_previous = p_list->p_tail;

  p_list->size++; /* Increment size */

  return 1;
}

int
insert_at_end (list_t *p_list, void *p_value, unsigned int is_string)
{
  node_t *p_new_node
      = create_node (p_value, is_string); /* Create a new node. */

  if (get_len (p_list) == 0)
    return first_entry (p_list, p_new_node);

  p_list->p_tail->p_next = p_new_node;
  p_new_node->p_previous = p_list->p_tail;
  p_list->p_tail = p_new_node;
  p_list->p_head->p_previous = p_list->p_tail;
  p_list->p_tail->p_next = p_list->p_head;

  p_list->size++;

  return 1;
}

node_t *
remove_at_beginning (list_t *p_list)
{
  if (get_len (p_list) == 0)
    return 0;
  if (get_len (p_list) == 1)
    {
      node_t *p_node_to_destroy = p_list->p_head;
      p_list->p_head = NULL;
      p_list->p_tail = NULL;
      p_node_to_destroy->p_next = NULL;
      p_node_to_destroy->p_previous = NULL;
      p_list--;
      return p_node_to_destroy;
    }

  node_t *p_node_to_destroy = p_list->p_head;
  p_list->p_head = p_list->p_head->p_next;
  p_list->p_head->p_previous = p_list->p_tail;
  p_list->p_tail->p_next = p_list->p_head;
  p_node_to_destroy->p_next = NULL;
  p_node_to_destroy->p_previous = NULL;
  p_list->size--;
  return p_node_to_destroy;
}

node_t *
remove_at_end (list_t *p_list)
{
  if (get_len (p_list) == 0)
    return 0;
  if (get_len (p_list) == 1)
    {
      node_t *p_node_to_destroy = p_list->p_head;
      p_list->p_head = NULL;
      p_list->p_tail = NULL;
      p_list->size--;
      return p_node_to_destroy;
    }

  node_t *p_node_to_destroy = p_list->p_tail;
  p_list->p_tail = p_list->p_tail->p_previous;
  p_list->p_tail->p_next = p_list->p_head;
  p_list->p_head->p_previous = p_list->p_tail;
  p_node_to_destroy->p_previous = NULL;
  p_node_to_destroy->p_next = NULL;
  p_list->size--;
  return p_node_to_destroy;
}

node_t *pop (list_t *p_list, unsigned int index);

node_t *
remove_at (list_t *p_list, unsigned int index)
{
  if (get_len (p_list) == 0)
    return 0;
  if (get_len (p_list) != 0 && index > get_len (p_list))
    return 0;
  // if (index == NULL) return remove_at_end(p_list);
  if (index == 0)
    return remove_at_beginning (p_list);

  unsigned int i = 0;

  node_t *p_node_ptr = p_list->p_head;

  while (i != index)
    {
      p_node_ptr = p_node_ptr->p_next;
      i++;
      if (i != index && p_node_ptr == p_list->p_head)
        return 0;
    }

  if (p_node_ptr == p_list->p_tail)
    return remove_at_end (p_list);
  else if (p_node_ptr == p_list->p_head)
    return remove_at_beginning (p_list);
  else
    {
      node_t *p_node_to_destroy = p_node_ptr;
      p_node_to_destroy->p_previous->p_next = p_node_to_destroy->p_next;
      p_node_to_destroy->p_next->p_previous = p_node_to_destroy->p_previous;
      p_node_to_destroy->p_previous = NULL;
      p_node_to_destroy->p_next = NULL;
      p_list->size--;
      return p_node_to_destroy;
    }
}

int
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
  return 1;
}

int
destroy_list (list_t *p_list)
{
  free (p_list);
  return 1;
}

int
destroy_each_node (list_t *p_list)
{
  if (get_len (p_list) == 0)
    return 0;
  node_t *p_node = p_list->p_head;

  for (unsigned int i = 0; i < get_len (p_list); ++i)
    {
      node_t *p_tmp = p_node;
      p_node = p_node->p_next;
      destroy_node (p_tmp);
    }

  return 1;
}

node_t *
get_node_at (list_t *p_list, unsigned int index)
{
  if (get_len (p_list) == 0)
    return NULL;

  if (index > get_len (p_list))
    return 0;

  node_t *p_node = p_list->p_head;

  for (unsigned int i = 0; i < get_len (p_list); ++i)
    {
      if (i == index)
        return p_node;
      p_node = p_node->p_next;
    }

  exit (0);
}

int
unlink_node (list_t *p_list, node_t *p_node)
{
  if (get_len (p_list) == 0)
    return 0;

  if (p_node == p_list->p_head)
    {
      node_t *p_toDestroy = p_list->p_head;

      p_list->p_tail->p_next = p_list->p_head->p_next;
      p_list->p_head = p_list->p_head->p_next;
      p_list->p_head->p_previous = p_list->p_tail;

      p_list->size--;
      destroy_node (p_toDestroy);
      return 1;
    }
  else if (p_node == p_list->p_tail)
    {
      node_t *p_toDestroy = p_list->p_tail;

      p_list->p_head->p_previous = p_list->p_tail->p_previous;
      p_list->p_tail = p_list->p_tail->p_previous;
      p_list->p_tail->p_next = p_list->p_head;

      p_list->size--;

      destroy_node (p_toDestroy);
      return 1;
    }
  else
    {
      p_node->p_previous->p_next = p_node->p_next;
      p_node->p_next->p_previous = p_node->p_previous;

      p_list->size--;

      destroy_node (p_node);

      return 1;
    }
}

int
insert_at (list_t *p_list, void *p_value, unsigned int index,
           unsigned int is_string)
{
  node_t *p_new_node = create_node (p_value, is_string);

  if (index == 0 && get_len (p_list) == 0)
    return first_entry (p_list, p_new_node);

  else if (index == 0 && get_len (p_list) != 0)
    return insert_at_beginning (p_list, p_value, is_string);

  node_t *p_node = p_list->p_head;

  index -= 1;

  for (unsigned int i = 0; i < get_len (p_list); ++i)
    {
      if (i == index)
        break;
      p_node = p_node->p_next;
    }

  if (p_node == p_list->p_tail)
    return insert_at_end (p_list, p_value, is_string);
  else if (p_node == p_list->p_head)
    return insert_at_beginning (p_list, p_value, is_string);
  else
    {
      p_node->p_next->p_previous = p_new_node;
      p_new_node->p_next = p_node->p_next;
      p_node->p_next = p_new_node;
      p_new_node->p_previous = p_node;
      p_list->size++;
    }

  return 1;
}
