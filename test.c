#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "nc_lib.h"
#include <unistd.h>

typedef struct table 
{
    char *name;
    void (*func)(void);
} func_info;

void func3(void)
{
    printf("(3333)");
    fflush(stdout);
}
void func2(void)
{
    printf("(2222)");
    fflush(stdout);
}
void func1(void)
{
    printf("(1111)");
    fflush(stdout);
}
void error_func(void)
{
    printf("(Called default error function)");
    fflush(stdout);
}

int get_index(char *input)
{
    int number_from_input = atoi(input);
    if (number_from_input < 1 || number_from_input > 3) 
        return 3;
    return (number_from_input - 1);
}
  struct table newTable[] = 
    {{"abc", func1},
    {"abc", func2},
    {"abc", func3},
    {"abc", error_func}};


typedef void (*func_pointer)(void);


typedef struct string_info
{
    char *last_location;
    char *new_location;
} string_info;

void    print_regular(string_info *string)
{
    int size = string->new_location - string->last_location;
    write(1, string->last_location, size);
}


/*
    when it gets here it's at the %, +1 get's it to the char, +1 again it gets it to the next spot
 */
func_pointer    get_function_N_update_ptr(string_info *string)
{
    int index;

    string->new_location++;
    index = get_index(string->new_location);
    string->new_location++;
    return (newTable[index].func);
}

void    print_special(string_info *string)
{
    func_pointer func;
    
    func = get_function_N_update_ptr(string);
    func();
}
enum bool{FALSE, TRUE};

int find_percent_flag(string_info *string)
{
    if ((string->new_location = nc_strchr(string->new_location, '%')))
        return TRUE;
    return FALSE;

}


func_pointer nc_printf(char *input)
{
    string_info string;
    string.last_location = input;
    string.new_location = input;
    while (find_percent_flag(&string))
    {
        print_regular(&string);
        
        print_special(&string);

        string.last_location = string.new_location;
    }
    //finish end of string till null
    return func1;
}

int main(int argc, char **argv)
{
    char *testing_string0 = "this is %4 abcd ";
    char *testing_string1 = "this is %4 abcd %3 88888%1 hahah%";
    char *testing_string2 = "this string has no sign?";
    char *testing_string3 = "this string has no sign? %1";
    char *testing_string4 = "this is %4%3 88888%1 hahah%";
    if (argc == 2)
    {

        nc_printf(testing_string4);

        return EXIT_SUCCESS;
    }
    printf("input something\n");
    return EXIT_FAILURE;
}

//find %
// figure out what func to call
//  -> it looks around %, all func, moves pointer to right possition
// loop
