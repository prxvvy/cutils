//
// Created by prxvvy on 05/07/2022
//

#ifndef __UTILS_H__
#define __UTILS_H__

typedef enum bool { false, true } bool;

/*
 * Concatenate strings just like sprintf but without passing a buffer.
 * Caller must free the return value.
 */

char *concat(char *, ...);

/*
 * Turn a number into a string.
 * If no based is specified then base will be 10. Bellow there's the categories.
 * Caller must free the return value.
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

char *itoa(int, int);

/*
 * Count digits in a number.
 * If no based is specified then base will be 10. Bellow there's the categories.
 *
 * Binary : if base is 2
 *
 * Octal : if base is 8
 *
 * Decimal: if base is 10
 *
 * Hex : base is 16
 */

unsigned int count_digits(int, int);

#endif	// __UTILS_H__
