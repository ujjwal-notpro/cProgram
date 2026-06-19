#include<stdio.h>
int main()
{
    int num, originalNum, remainder, result = 0;
    printf("Enter an integer: ");
    scanf("%d", &num);
    originalNum = num;
    while (originalNum != 0) {
        remainder = originalNum % 10;
        result = result * 10 + remainder;
        originalNum /= 10;
    }
    if (result == num){
        printf("%d is a pelindrome number",num);
    }
    else{
        printf("%d is not a pelindrome number",num);
    }
    return 0;
}