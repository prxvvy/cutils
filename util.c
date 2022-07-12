//
// Created by prxvvy on 05/07/2022
//

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>

unsigned int count_digits(int number, int base) {
   if (!base) base = 10;
   if (base < 2 || base > 36) {
      printf("count_digits(): Invalid base %d.\n", base);
      return false;
   }

   if (number == 0) return 1;

   int amount = 0;

   if (number < 0) amount += 1;

   while (number != 0) {
      number /= base;
      amount++;
   }

   return amount;
}

char *itoa(int number, int base) {
   if (!base) base = 10;
   if (base < 2 || base > 36) {
      printf("itoa(): Invalid base %d.\n", base);
      return NULL;
   }

   char *p_result = calloc(count_digits(number, base) + 1, sizeof(char));
   if (!p_result) return NULL;
   size_t p_result_len = strlen(p_result);

   if (number == 0) {
      p_result[p_result_len++] = '0';
      p_result[p_result_len] = '\0';
      return p_result;
   }

   char *ptr = p_result;
   char *ptr1 = p_result;
   char tmp_char;
   int tmp_number;

   do {
      tmp_number = number;
      number /= base;
      *ptr++ =
	  "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvw"
	  "xyz"[35 + (tmp_number - number * base)];
   } while (number);
   // Apply negative sign
   if (tmp_number < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while (ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr-- = *ptr1;
      *ptr1++ = tmp_char;
   }

   return p_result;
}

char *concat(char *p_format, ...) {
   char *p_concat_str = calloc(1, sizeof(char));
   if (!p_concat_str) return NULL;
   va_list args;
   va_start(args, p_format);
   size_t p_concat_str_len = strlen(p_concat_str);

   for (size_t i = 0; p_format[i] != '\0'; ++i) {
      if (p_format[i] == '%' &&
	  (p_format[i + 1] == 's' || p_format[i + 1] == 'S')) {
	 i++;
	 char *p_arg_str = va_arg(args, char *);
	 if (!p_arg_str) p_arg_str = "(null)";
	 size_t p_arg_str_len = strlen(p_arg_str);
	 p_concat_str_len += p_arg_str_len;
	 char *p_realloc_res = realloc(p_concat_str, p_concat_str_len + 1);
	 if (!p_realloc_res) {
	    free(p_concat_str);
	    p_concat_str = NULL;
	    break;
	 }
	 p_concat_str = p_realloc_res;
	 strcat(p_concat_str, p_arg_str);
	 continue;
      } else if (p_format[i] == '%' &&
		 (p_format[i + 1] == 'd' || p_format[i + 1] == 'D')) {
	 i++;
	 char *p_arg_int = itoa(va_arg(args, int), 10);
	 if (!p_arg_int) p_arg_int = 0;
	 size_t p_arg_int_len = strlen(p_arg_int);
	 p_concat_str_len += p_arg_int_len;
	 char *p_realloc_res = realloc(p_concat_str, p_concat_str_len + 1);
	 if (!p_realloc_res) {
	    free(p_concat_str);
	    p_concat_str = NULL;
	    break;
	 }
	 p_concat_str = p_realloc_res;
	 strcat(p_concat_str, p_arg_int);
	 free(p_arg_int);
	 continue;
      }
      char *p_realloc_res = realloc(p_concat_str, p_concat_str_len + 2);
      if (!p_realloc_res) {
	 free(p_concat_str);
	 p_concat_str = NULL;
	 break;
      }
      p_concat_str = p_realloc_res;
      p_concat_str[p_concat_str_len++] = p_format[i];
      p_concat_str[p_concat_str_len] = '\0';
   }

   va_end(args);

   return p_concat_str;
}