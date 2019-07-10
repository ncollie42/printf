#include "header.h"

int main(int argc, char **argv)
{
   char *str1 = "this %a is my string  okay";
   nc_printf("this %a is%a ok%ay", 42, 42, 42);
}