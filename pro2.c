#include<stdio.h>
#include<conio.h>
void main()

{
    int a,b,temp;
    printf("input 2 numbers");
    scanf("%d%d",&a,&b);
    temp=a;
    a=b;
    b=temp;
    printf("swapped value of a=%d\tb=%d,a,b");
    getch();
}