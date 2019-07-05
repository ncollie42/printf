#include <stdio.h>

struct table 
{
    char *name;
    void (*func);
};

void func3(void)
{
    printf("333\n");
}
void func2(void)
{
    printf("2222\n");
}
void func1(void)
{
    printf("1111\n");
}

int main(int argc, char **argv)
{
    struct table newTable = {"abc", func1};

    if (argc == 2)
    {
        char *tmp = argv[1];
        newTable.func();
    }
}