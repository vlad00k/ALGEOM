#include <stdio.h>
#include <malloc.h>

void swap_rows(double *matrix[], int d, int row_idx);
int get_row_idx(double *matrix[], int d, int rows);
void print_matrix(double *matrix[], int rows, int columns);
void solve_matrix(double *matrix[], int rows, int columns);
int almost_equal(double a, double b);

int main()
{
    int number_equasion;
	printf("Enter n: ");
    scanf("%d", &number_equasion);
	printf("Enter extended matrix:\n");
    int rows = number_equasion;
    int columns = rows + 1;
    double *matrix[rows];
    for (int i = 0; i < rows; i++)
    {
        double *equasion = (double *)malloc(columns * sizeof(double));
        for (int j = 0; j < columns; j++)
        {
            scanf("%lf", &equasion[j]);
        }
        matrix[i] = equasion;
    }

    // print_matrix(matrix, rows, columns);
    // printf("\n");
    solve_matrix(matrix, rows, columns);
    // print_matrix(matrix, rows, columns);

    for (int r = 0; r < rows; r++)
        printf("x%d = %.10lf\n", r + 1, matrix[r][rows]);

    for (int i = 0; i < rows; i++)
    {
        free((void *)matrix[i]);
    }

    return 0;
}

int almost_equal(double a, double b)
{
    if (a > b)
        return a - b < 0.001 ? 1 : 0;
    else
        return b - a < 0.001 ? 1 : 0;
}

void print_matrix(double *matrix[], int rows, int columns)
{
    for (int d = 0; d < rows; d++)
    {
        for (int c = 0; c < columns; c++)
        {
            printf("%.2f ", matrix[d][c]);
        }
        printf("\n");
    }
}

void solve_matrix(double *matrix[], int rows, int columns)
{
    int vector_idx = columns - 1;
    int row_idx;
    double ratio;
    for (int d = 0; (d < rows) && (d < vector_idx); d++)
    {
        // printf("Demention %d\n", d);
        // print_matrix(matrix, rows, columns);
        // printf("\n");
        row_idx = get_row_idx(matrix, d, rows);
        if (row_idx == -1)
            continue;
        // Swap current row and the first row with not zero value of d demention
        swap_rows(matrix, d, row_idx);
        for (int c = vector_idx; c > -1; c--)
            matrix[d][c] /= matrix[d][d];

        // print_matrix(matrix, rows, columns);
        // printf("\n");

        // Row reducing
        for (int i = d + 1; i < rows; i++)
        {
            ratio = matrix[i][d];
            for (int c = 0; c < columns; c++)
            {
                matrix[i][c] -= ratio * matrix[d][c];
                if (almost_equal(matrix[i][c], 0.0))
                    matrix[i][c] = 0.0;
            }
        }
        for (int i = d - 1; i > -1; i--)
        {
            ratio = matrix[i][d];
            for (int c = 0; c < columns; c++)
            {
                matrix[i][c] -= ratio * matrix[d][c];
                if (almost_equal(matrix[i][c], 0.0))
                    matrix[i][c] = 0.0;
            }
        }
        // printf("row reducing\n");
        // print_matrix(matrix, rows, columns);
        // printf("\n\n");
    }
}

void swap_rows(double *matrix[], int d, int row_idx)
{
    double *temp = matrix[d];
    matrix[d] = matrix[row_idx];
    matrix[row_idx] = temp;
}

int get_row_idx(double *matrix[], int d, int rows)
{
    for (int i = d; i < rows; i++)
        if (!almost_equal(matrix[i][d], 0.0))
            return i;
    return -1;
}
