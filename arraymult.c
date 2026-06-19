#include<stdio.h>
int main ()
{
    int i,j,r1,c1,r2,c2,k,a[10][10],b[10][10],c[10][10],sum;
    printf("input order of first matrix:");
    scanf("%d%d",&r1,&c1);
    printf("input order of second matrix:");
    scanf("%d%d",&r2,&c2);
    if(c1!=r2)
    {
        printf("matrix multiplication is not possible");
    }
    else
    {
        printf("input first matrix:");
        for(i=0;i<r1;i++)
        {
            for(j=0;j<c1;j++)
            {
                scanf("%d",&a[i][j]);
            }
        }
        printf("input second matrix:");
        for(i=0;i<r2;i++)
        {
            for(j=0;j<c2;j++)
            {
                scanf("%d",&b[i][j]);
            }
        }
        for(i=0;i<r1;i++)
        {
            for(j=0;j<c2;j++)
            {
                sum=0;
                for(k=0;k<c1;k++)
                {
                    sum=sum+a[i][k]*b[k][j];
                }
                c[i][j]=sum;
            }
        }
        printf("product of the two matrices is:");
        for(i=0;i<r1;i++)        {
            for(j=0;j<c2;j++)
            {
                printf("%d\t",c[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}