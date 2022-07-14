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

#ifndef _LIST_H_
#define _LIST_H_

#include <node.h>

typedef struct list
{
  struct node *p_head;
  struct node *p_tail;
  unsigned int size;
} list_t;

list_t *create_list ();

int increment_node_position (list_t *p_list, node_t *p_node);

unsigned int get_len (list_t *p_list);

int insert_at_beginning (list_t *p_list, void *p_value,
                         unsigned int is_string);

int insert_at_end (list_t *p_list, void *p_value, unsigned int is_string);

node_t *remove_at_beginning (list_t *p_list);

node_t *remove_at_end (list_t *p_list);

node_t *pop (list_t *p_list, unsigned int index);

node_t *remove_at (list_t *p_list, unsigned int index);

int first_entry (list_t *p_list, node_t *p_node);

int destroy_list (list_t *p_list);

int destroy_each_node (list_t *p_list);

node_t *get_node_at (list_t *p_list, unsigned int index);

int unlink_node (list_t *p_list, node_t *p_node);

int insert_at (list_t *p_list, void *p_value, unsigned int index,
               unsigned int is_string);

#endif // _LIST_H_
