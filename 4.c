
#include <stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int matrix[n][n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
         scanf("%d",&matrix[i][j]);
        }
    }
printf("det=%d",det_calculate(n,matrix));


}
void print_matrix ( int n,int matrix[][n])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
         printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

int det_calculate(int n, int matrix[][n])
{
    int det=0;
    if(n==2)
    {
        det=matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
        return det;
    }
    else if (n==1)
        return matrix[0][0];
    int sub_matrix[n-1][n-1];
    for(int i=0;i<n;i++)
    {
     int a=matrix[0][i];
     int sign;
     if(i%2==0)
     {
        sign=1;
     }
     else
     {
        sign=-1;
     }
     a=sign*a;

         for(int k=0;k<n-1;k++)
        {
            for(int j=0;j<i;j++)
            {
             sub_matrix[k][j]=matrix[k+1][j];
            }
        }

        for(int k=0;k<n-1;k++)
        {
            for(int j=i+1;j<n;j++)
            {
             sub_matrix[k][j-1]=matrix[k+1][j];
            }
        }
    det+=a*det_calculate(n-1,sub_matrix);
    }
    return det;

}
