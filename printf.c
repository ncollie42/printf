
#include <stdlib.h>
#include <stdio.h>
#include "nc_lib_buffer.h"
#include "nc_printf.h"

#define PTR_FUNC
#define OCTAL_FUNC(x,y) ul_function((x),(y),8)

void *table[] = {error_function,
error_function,
error_function,
error_function,
int_function,
error_function,
error_function,
error_function,
error_function,
int_function,
error_function,
error_function,
error_function,
error_function,
error_function,
octal_function,
ptr_function,
error_function,
error_function,
str_function};

// map d to int_function??

void    error_function(dynamic_buffer *buff, va_list args){};


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

func    get_function(char *str)
{
    if (*str >= 'a' && *str <= 'z')
        return (table[(*str - 'a') + 1]);
    return error_function;
}

char *handle_flag_n_update_ptr(dynamic_buffer *buff, va_list args, char *str)
{
    // func    function;
    void    *function;
    str++;
    function = get_function(str);
    ((func)function)(buff, args);

    return str;
}

void    init(char *format, char **stepper, dynamic_buffer **buff)
{
    *stepper = (char *)format;
    *buff = create_dynamic_buffer();
}

int     nc_printf(const char * restrict format, ...)
{
    va_list args;
    dynamic_buffer *buff;
    char *stepper;

    va_start(args, format);
    init((char *)format, &stepper, &buff);
    while(*stepper)
    {
        if (*stepper == '%')
            stepper = handle_flag_n_update_ptr(buff, args, stepper);
        else
            add_to_buffer(buff, stepper, 1);
        if (*stepper)
            stepper++;
    }
    debug_print_buffer(buff);
    delete_dynamic_buffer(buff);
    va_end(args);
    return 0; 
}