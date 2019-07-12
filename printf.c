
#include <stdlib.h>
#include <stdio.h>
#include "nc_lib_buffer.h"
#include "nc_printf.h"

func    get_function(char *str)
{
    if (*str >= 'a' && *str <= 'z')
        return (table[(*str - 'a') + 1]);
    return error_function;
}

char *handle_flag_n_update_ptr(dynamic_buffer *buff, va_list args, char *str)
{
    func    function;
    str++;
    function = get_function(str);
    function(buff, args);

    return str;
}

int     nc_printf(const char * restrict format, ...)
{
    va_list         args;
    dynamic_buffer  *buff;
    char            *stepper;
    int             size;

    va_start(args, format);
    stepper = (char *)format;
    buff = create_dynamic_buffer();
    while(*stepper)
    {
        if (*stepper == '%')
            stepper = handle_flag_n_update_ptr(buff, args, stepper);
        else
            add_to_buffer(buff, stepper, 1);
        if (*stepper)
            stepper++;
    }
    delete_dynamic_buffer(buff);
    size = print_buffer(buff, 1);
    va_end(args);
    return size; 
}