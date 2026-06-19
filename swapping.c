#include <stdio.h>
#include <conio.h>
void main()
 {
    int a, b, temp;
    
    printf("first number: ");
    scanf("%d", &a);
    
    printf("second number: ");
    scanf("%d", &b);
    
    printf("\nBefore swapping:\n");
    printf("a = %d, b = %d\n", a, b);
    // Swapping using temporary variable
    temp = a;
    a = b;
    b = temp;
    
    printf("\nAfter swapping:\n");
    printf("a = %d, b = %d\n", a, b);
    
    getch();
}