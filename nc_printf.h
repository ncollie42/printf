#ifndef NC_PRINTF_H
#define NC_PRINTF_H
#define ERROR 0;
#include "nc_lib_buffer.h"
#include <stdarg.h>

typedef void (*func)(dynamic_buffer *buff, va_list args);

int     nc_printf(const char * restrict format, ...);
void    error_function(dynamic_buffer *buff, va_list args);
void    int_function(dynamic_buffer *buff, va_list args);
void    str_function(dynamic_buffer *buff, va_list args);
void    ul_function(dynamic_buffer *buff, va_list args, int base);
void    octal_function(dynamic_buffer *buff, va_list args);
void    ptr_function(dynamic_buffer *buff, va_list args);
#endif