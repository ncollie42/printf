#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "nc_header.h"

typedef struct table 
{
    char *name;
    void (*func)(void);
} func_info;

void func3(void)
{
    printf("3333\n");
}
void func2(void)
{
    printf("2222\n");
}
void func1(void)
{
    printf("1111\n");
}
void error_func(void)
{
    printf("Called default error function\n");
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

//  func_info function_table[] = 
//     {{"abc", func1},
//     {"abc", func2},
//     {"abc", func3},
//     {"abc", error_func}};

typedef void (*func_pointer)(void);

func_pointer get_func_from_input(char *input)
{
    char *tmp = input;
    while ((tmp = nc_strchr(tmp, '%')))
    {
        tmp++;
        printf("%s\n", tmp);       
    }
    return func1;
}

int main(int argc, char **argv)
{
    void (*special)(void);
    func_pointer f_p;
    char *testing_string = "this is %4 %3 %1 hahah%";
    if (argc == 2)
    {
        char *input = argv[1];
        int index = get_index(input);
        newTable[index].func();

        get_func_from_input(testing_string);

        // special = get_func_from_input(input);
        // f_p = get_func_from_input(input);
        // special();
        // f_p();
        // newTable[0].func();
        // newTable[1].func();
        // newTable[2].func();
        return EXIT_SUCCESS;
    }
    printf("input something\n");
    return EXIT_FAILURE;
}