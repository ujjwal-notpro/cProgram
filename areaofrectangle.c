#include<stdio.h>
void main()
{
    int lenght,breadth,area;
    printf("enter lenght\n");
    scanf("%d",&lenght);

    printf("enter breadth\n");
    scanf("%d",&breadth);
    area =lenght*breadth;
    printf("area=%d",area);
    getch();
}