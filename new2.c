#include<stdio.h>
void main()
{
    int age;
    printf("enter age\t");
    scanf("%d",&age);
    if(age>=18)
    {
        printf("you are eligible to vote");
    }
    else
    {
        printf("you are not eligible to vote");
    }
    getch();
}