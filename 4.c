#include <stdio.h>
#include <malloc.h>

int get_determinant(int n, int matrix[][n]);
void print_matrix(int n, int matrix[][n]);

int main()
{
    int N;
    printf("Enter N: ");
    scanf("%d", &N);
    int matrix[N][N];
    printf("Enter matrix value with spaces:\n");
    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            scanf("%d", &matrix[i][k]);

    printf("Matrix determinant = %d", get_determinant(N, matrix));
}

int get_determinant(int n, int matrix[][n])
{
    // print_matrix(n, matrix);
    // printf("\n")
    int determinant = 0;
    if (n == 2)
        determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else
    {
        int sign = 1;
        int submatrix[n - 1][n - 1];
        for (int i = 0; i < n; i++)
        {
            for (int ii = 0; ii < i; ii++)
                for (int kk = 0; kk < n - 1; kk++)
                    submatrix[ii][kk] = matrix[ii][kk + 1];

            for (int ii = i + 1; ii < n; ii++)
                for (int kk = 1; kk < n; kk++)
                    submatrix[ii - 1][kk - 1] = matrix[ii][kk];
            determinant += sign * matrix[i][0] * get_determinant(n - 1, submatrix);
            sign = -1 * sign;
        }
    }
    return determinant;
}

void print_matrix(int n, int matrix[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
            printf("%d ", matrix[i][k]);
        printf("\n");
    }
}
