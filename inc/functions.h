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

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

typedef enum bool
{
  false,
  true
} bool;

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

#endif // _FUNCTIONS_H_
