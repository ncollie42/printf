#include "nc_printf.h"
#include <stdio.h>

int main(int argc, char **argv)
{
   char *str1 = "this %a is my string  okay";
   int size1 = nc_printf("%o\t%pthis %s is%i ok%dy%c\n",100, str1, "******", 42, 42,'w');
   int size2 = printf("%o\t%pthis %s is%i ok%dy%c\n",100, str1, "******", 42, 42,'w');
   printf("%d\n%d", size1, size2);
}