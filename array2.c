#include <stdio.h>

int main() {
    int arr[50], n, i, j, count;
    int visited[50] = {0};

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for(i = 0; i < n; i++) {
        if(visited[i] == 1)
            continue;
    
        count = 1;

        for(j = i + 1; j < n; j++) {
            if(arr[i] == arr[j]) {
                count++;
                visited[j] = 1;
            }
        }

        printf("%d occurs %d times\n", arr[i], count);
}

    return 0;
}