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

#include "bool.h"
#include "node.h"

typedef struct list
{
  struct node *p_head;
  struct node *p_tail;
  unsigned int size;
  unsigned int (*get_len) (struct list *);
  bool (*destroy_list) (struct list *);
  bool (*destroy_each_node) (struct list *);
  node_t *(*insert_at_beginning) (struct list *, void *, type);
  node_t *(*insert_at_end) (struct list *, void *, type);
  node_t *(*insert_at) (struct list *, void *, unsigned int, type);
  node_t *(*remove_at_beginning) (struct list *);
  node_t *(*remove_at_end) (struct list *);
  node_t *(*remove_at) (struct list *, unsigned int);
  node_t *(*first_entry) (struct list *, node_t *);
  node_t *(*get_node_at) (struct list *, unsigned int);
  node_t *(*unlink_node) (struct list *, node_t *);
} list_t;

list_t *create_list ();

unsigned int get_len (list_t *);

node_t *insert_at_beginning (list_t *, void *, type);

node_t *insert_at_end (list_t *, void *, type);

node_t *remove_at_beginning (list_t *);

node_t *remove_at_end (list_t *);

node_t *remove_at (list_t *, unsigned int);

node_t *first_entry (list_t *, node_t *);

bool destroy_list (list_t *);

bool destroy_each_node (list_t *);

node_t *get_node_at (list_t *, unsigned int);

node_t *unlink_node (list_t *, node_t *);

node_t *insert_at (list_t *, void *, unsigned int, type);

#endif // _LIST_H_
