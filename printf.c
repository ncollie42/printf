#include <stdarg.h>
#include "nc_lib_buffer.h"
#include <stdlib.h>
#include <stdio.h>
// map d to int_function??
typedef void (*func)(dynamic_buffer *buff, va_list args);
#define ERROR 0;
void    error_function(dynamic_buffer *buff, va_list args){};

void    int_function(dynamic_buffer *buff, va_list args)
{
    int value;
    char *number2;

    value = va_arg(args, int);
    number2 = nc_itoa(value);
    add_to_buffer(buff, number2, nc_strlen(number2));
    free(number2);
}

func table[] = {error_function,
int_function};

int     get_index(char *str)
{
    if (*str >= 'a' && *str <= 'z')
        return ((*str - 'a') + 1);
    return ERROR;
}


char *handle_flag_n_update_ptr(dynamic_buffer *buff, va_list args, char *str)
{
    int index;

    str++;
    index = get_index(str);
    table[index](buff, args);

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