#include "nc_lib_buffer.h"
#include "nc_printf.h"

func    table[] = {error_function,
error_function, //a
error_function, //b
char_function, //c
int_function,   //d
error_function, //e
error_function, //f
error_function, //g
error_function, //h
int_function,   //i
error_function, //j
error_function, //k
error_function, //l
error_function, //m
error_function, //n
octal_function, //o
ptr_function,   //p
error_function, //q
error_function, //r
str_function,   //s
error_function, //t
error_function, //u
error_function, //v
error_function, //w
hex_function,   //x
error_function, //y
error_function};//z

void    error_function(dynamic_buffer *buff, va_list args){};

void    hex_function(dynamic_buffer *buff, va_list args)
{
    char            *str_number;
    unsigned long   ul_number;

    ul_number = va_arg(args, unsigned long);
    str_number = nc_itoa_base(ul_number, 16);
    add_to_buffer(buff, str_number, nc_strlen(str_number));
    free(str_number);
}

void    ptr_function(dynamic_buffer *buff, va_list args)
{
    char            *str_number;
    unsigned long   ul_number;

    ul_number = va_arg(args, unsigned long);
    str_number = nc_itoa_base(ul_number, 16);
    add_to_buffer(buff, "0x", 2);
    add_to_buffer(buff, str_number, nc_strlen(str_number));
    free(str_number);
}

void    octal_function(dynamic_buffer *buff, va_list args)
{
    unsigned long   octal_number;
    char            *str_number;

    octal_number = va_arg(args, unsigned long);
    str_number = nc_itoa_base(octal_number, 8);
    add_to_buffer(buff, str_number, nc_strlen(str_number));
    free(str_number);
}

void    str_function(dynamic_buffer *buff, va_list args)
{
    char *ptr;

    ptr = va_arg(args, void *);
    add_to_buffer(buff, ptr, nc_strlen(ptr));
}

void    int_function(dynamic_buffer *buff, va_list args)
{
    int     int_number;
    char    *str_number;

    int_number = va_arg(args, int);
    str_number = nc_itoa(int_number);
    add_to_buffer(buff, str_number, nc_strlen(str_number));
    free(str_number);
}

void    char_function(dynamic_buffer *buff, va_list args)
{
    char     character;

    character = (char)va_arg(args, int);
    add_to_buffer(buff, &character, 1);
}
