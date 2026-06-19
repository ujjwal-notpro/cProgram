#include<stdio.h>
int main()
{
    char op;
    float a,b;
    printf("enter two numbers\t");
    scanf("%f%f",&a,&b);
    printf("enter an operator (+,-,*,/)\t");
    scanf(" %c",&op);
    switch(op)
    {
        case '+':
            printf("result = %f",a+b);
            break;
        case '-':
            printf("result = %f",a-b);
            break;
        case '*':
            printf("result = %f",a*b);
            break;
        case '/':
            printf("result = %f",a/b);
            break;
        default:
            printf("invalid operator");
    }
    return 0;
}