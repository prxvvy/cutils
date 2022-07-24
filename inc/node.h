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

#ifndef _NODE_H_
#define _NODE_H_

#include "bool.h"

typedef enum TYPE
{
  STRING,
  NUMBER,
  UNKNOWN,
} type;

typedef struct node
{
  void *p_value;
  struct node *p_next;
  struct node *p_previous;
  type type;
  bool (*destroy_node) (struct node *);
} node_t;

node_t *create_node (void *, type);

bool destroy_node (node_t *);

#endif // _NODE_H_
