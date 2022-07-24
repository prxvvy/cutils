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

#ifndef _INDEPENDENT_H_
#define _INDEPENDENT_H_

#include "bool.h"
#include "list.h"
#include <stdio.h>

/*
 * Concatenate strings just like sprintf but without passing a buffer.
 * Caller must free the return value.
 */

char *concat (char *, ...);

/*
 * Turn a number into a string.
 * If no based is specified then base will be 10. Bellow there's the
 * categories. Caller must free the return value.
 *
 * Binary : if base is 2
 *
 * Octal : if base is 8
 *
 * Decimal: if base is 10
 *
 * Hex : base is 16
 *
 */

char *itoa (int, int);

/*
 * Count digits in a number.
 * If no based is specified then base will be 10. Bellow there's the
 * categories.
 *
 * Binary : if base is 2
 *
 * Octal : if base is 8
 *
 * Decimal: if base is 10
 *
 * Hex : base is 16
 */

unsigned int count_digits (int, int);

/*
 * Get input from stdin with an optional message as an instruction.
 */

char *get_input_from_stdin (char *);

/*
 * Compare str 1 to str 2.
 */

bool compare_str (char *, char *);

/*
 * Reverse a string.
 * Caller must free the return value.
 *
 */

char *reverse_str (char *);

/*
 * Remove garbage characters from str.
 * Write output to buffer;
 */

bool strip (char *, const char *, const char *);

/*
 * Check if str includes a specified character of substring.
 */

bool str_includes (char *, char, char *);

/*
 * Cut str up to delimiter.
 * Caller must free the return value.
 */

char *cut_str (char *, unsigned int);

/*
 * Get a specified line froma  file by a given pattern.
 */

char *get_line_by_pattern (char *, char *);

/*
 * Get all lines from a file and make them a single string with their
 * respective new line char.
 * This function should not be conditioned in a loop
 * to read line by line, use str_line_from_file() function instead.
 * Caller must
 * free the return value.
 */

char *str_all_lines_from_file (FILE *);

/*
 * Get the first line from a file.
 * Can be conditioned in a loop to read line by line.
 * Caller must free the return value.
 */

char *str_line_from_file (FILE *);

/*
 * Get line by line from a file and push them to a linked list.
 * Caller must free the return list with destroy_each_node() and
 * destroy_list().
 */

list_t *list_all_lines_from_file (char *);

/*
 * Split a string into a linked list. Just like the split method in other
 * languages.
 */

list_t *split (char *, char);

#endif // _INDEPENDENT_H_
