#include<stdio.h>
void main()
{
    int m1,m2,m3,m4,m5;
    printf("enter the marks obtained by the student\t");
    scanf("%d%d%d%d%d",&m1,&m2,&m3,&m4,&m5);
    printf("total marks obtained by the student=%d\n",m1+m2+m3+m4+m5);
    
    printf("percentage marks obtained by the student=%f\t",(m1+m2+m3+m4+m5)/5.0);
    getch();
}