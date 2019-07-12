#include <stdlib.h>
#include <stdio.h>
#include "nc_lib_buffer.h"
#include "nc_printf.h"

func table[] = {};

void    error_function(dynamic_buffer *buff, va_list args){};

void    int_function(dynamic_buffer *buff, va_list args)
{
    int     int_num;
    char    *str_num;

    int_num = va_arg(args, int);
    str_num = nc_itoa(int_num);
    add_to_buffer(buff, str_num, nc_strlen(str_num));
    free(str_num);
}


func    get_function(char *str)
{
    if (*str >= 'a' && *str <= 'z')
        return (table[*str - 'a']);
    return error_function;
}


char    *handle_flag_n_update(dynamic_buffer *buff, va_list args, char *str)
{
    func function;
    
    str++;
    function = get_function(str);
    function(buff, args);
    return str;
}

int     nc_printf(const char * restrict format, ...)
{
    va_list args;
    dynamic_buffer *buff;
    char    *stepper;

    stepper = (char *)stepper;
    va_start(format, args);
    buff = create_dynamic_buffer();
    while(*stepper)
    {
        if (*stepper == '%')
            stepper = handle_flag_n_update(buff, args, stepper);
        else
            add_to_buffer(buff, stepper, 1);
        if (*stepper)
            stepper++;
    }
    size = print_buffer(buff);
    va_end(args)
    delete_dynamic_buffer(buff);
    return (size);
}