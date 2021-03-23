#include <stdio.h>
int x =0;
void main()
{
int*const ptr=&x;
printf("%X\n",ptr);
ptr++;
printf("%X\n",ptr);
}