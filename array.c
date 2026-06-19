#include <stdio.h>
int main() {
    int n,i,max,arr[50],loc=0;
    printf("Enter the number of elements in the array: ");
    scanf("%d",&n);
    printf("Enter the elements of the array: ");
    for(i=0;i<n;i++) {
        scanf("%d",&arr[i]);
    }
    max=arr[0];
    for(i=1;i<n;i++)
    {
        if(arr[i]>max) {
            max=arr[i];
            loc=i;
        }
    }
    printf("%d is maximum value present at %d location",max,loc+1);
    return 0;
    
}