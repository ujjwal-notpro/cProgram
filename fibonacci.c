#include<stdio.h>
int main()
{
    int n = 0, a = 0, b =1, c = 0, i;
    printf("enter the number of terms\t");
    scanf("%d",&n);
    printf("fibonacci series is\t");
    for(i=1;i<=n ;i++)
    {
        printf("%d\t",a);
        c = a + b;
        a = b;
        b = c;
    }
    return 0;
}