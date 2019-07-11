#include "nc_printf.h"
#include <stdio.h>

int main(int argc, char **argv)
{
   char *str1 = "this %a is my string  okay";
   nc_printf("%o\t%pthis %s is%i ok%dy%c",100, str1, "******", 42, 42,'w');
   printf("%o\t%pthis %s is%i ok%dy%c",100, str1, "******", 42, 42,'w');
}