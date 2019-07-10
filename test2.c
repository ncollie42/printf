#include <unistd.h>
#include "nc_lib_buffer.h"

typedef void (*func)(dynamic_buffer *buff);

void n1(dynamic_buffer *buff){}
void n2(dynamic_buffer *buff){}
void n3(dynamic_buffer *buff){}
void other(dynamic_buffer *buff){}

func table[] = {n1, n2, n3, other};

int get_index(char *str)
{
    int index;

    index = atoi(str);
    if (index > 2 || index < 0)
        return 3;
    return index;
}

char *handle_flag(dynamic_buffer *buff, char *str)
{
    str++;
    int index = get_index(str);
    table[index](buff);
    
    if (*str)
        str++;
    return str;
}

void    nc_printf(char *input, ...)
{
    dynamic_buffer *buff;
    buff = create_dynamic_buffer();

    while(*input)
    {
        if (*input == '%')
            input = handle_flag(buff, input);
        else
            add_to_buffer(buff, input, 1);
        if (*input)
            input++;
    }
    debug_print_buffer(buff);
    delete_dynamic_buffer(buff);
}


int main(void)
{
    char *str1 = "this is my string ";
    nc_printf(str1);
}