#include<stdio.h>
int factorial(int);
int factorial(int n)
{
    if(n==0 || n==1)
        return 1;
    else
        return n*factorial(n-1); // eg: factorial(5) = 5*factorial(4) = 5*4*factorial(3) = 5*4*3*factorial(2) = 5*4*3*2*factorial(1) = 5*4*3*2*1 = 120
}
int main()
{
    int a;
    printf("enter the number\t");
    scanf("%d",&a);
    printf("the factorial of %d is %d",a,factorial(a));
    return 0;
    }
