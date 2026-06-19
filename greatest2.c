#include<stdio.h>
void main()
{
    int a,b,c,greatest;
    printf("Enter three numbers:");
    scanf("%d%d%d",&a,&b,&c);
    greatest = (a > b) ? (a > c ? a : c) : (b > c ? b : c);
printf("the greatest number is %d\n", greatest);
getch();
}