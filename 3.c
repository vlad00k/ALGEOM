#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>

float dot(int vector[], float basis_vector[], int dementions);
int is_new_basis(int vector[], float* basis[], int dementions);
float get_length(int vector[], int dementions);
void add_unit_vector(int vector[], float basis_vector[], int dementions);
int is_zero_vector(int vector[], int dementions);
int is_zero_basis_vector(float vector[], int dementions);
void init_basis(float* basis[], int demensions);
int almost_equal(float a, float b);
int is_new_basis_vector(int vector[], float* basis[], int dementions);
int is_linear_combination(float* matrix[], float* basis[], int vector[], int dementions, int column_number);
void swap_rows(float* matrix[], int d, int row_idx);
int get_row_idx(float* matrix[], int d, int columns);
void print_matrix(float* matrix[], int dementions, int column_number);


int main()
{
	setlocale(LC_ALL, "Rus");
	int number_of_vectors,dementions;
	printf("Enter n k\n");
	scanf("%d %d",&dementions,&number_of_vectors);
	int* vectors[number_of_vectors];
	for (int i=0;i<number_of_vectors;i++)
	{
			int*vector=(int*)malloc(dementions*sizeof(int));
			printf("Enter coordinates of %d vector with spaces:",i+1);  
			for(int j=0;j<dementions;j++)
			{
					scanf("%d",&vector[j]);

			}
			vectors[i]=vector;
	}


	float** basis;
	basis = (float**)malloc(dementions * sizeof(float*));
	init_basis(basis, dementions);
	int current_basis_idx = 0;
	int extra_vector_counter = 0;
	for (int i = 0; i < number_of_vectors; i++)
	{
		if (current_basis_idx >= dementions)
		{
			extra_vector_counter += number_of_vectors - i;
			break;
		}

		if (!is_zero_vector(vectors[i], dementions))
		{
			if (is_new_basis(vectors[i], basis, dementions))
			{
				add_unit_vector(vectors[i], basis[current_basis_idx], dementions);
				current_basis_idx++;
			}
			else
				extra_vector_counter++;
		}
		else
			extra_vector_counter++;
	}

	printf("System rank is %d\n", current_basis_idx);  // Ранг системы %d
	if (extra_vector_counter > 0)
		printf("Given vectors contain %d additional vector(s)\n", extra_vector_counter);  // Линейная оболочка содержит %d дополнительных векторов

	for (int i = 0; i < dementions; i++)
	{
		if (is_zero_basis_vector(basis[i], dementions))
			break;
		printf("%d basis vector is: ", i + 1);  // %d базисный вектор: 
		for (int k = 0; k < dementions; k++)
			printf("%.2f ", basis[i][k]);
		printf("\n");
	}
}

int almost_equal(float a, float b)
{
	if (a > b)
		return a - b < 0.001 ? 1 : 0;
	else
		return b - a < 0.001 ? 1 : 0;
}

int is_new_basis(int vector[], float* basis[], int dementions)
{
	if (is_zero_basis_vector(basis[0], dementions))
		return 1;
	if (is_new_basis_vector(vector, basis, dementions))
		return 1;
	return 0;
}

float get_length(int vector[], int dementions)
{
	int l = 0;
	for (int i = 0; i < dementions; i++)
		l += vector[i] * vector[i];
	return (float)sqrt((long double)l);
}

void add_unit_vector(int vector[], float basis_vector[], int dementions)
{
	float vector_length = get_length(vector, dementions);
	for (int i = 0; i < dementions; i++)
	{
		basis_vector[i] = (float)vector[i] / vector_length;
	}
}

int is_zero_vector(int vector[], int dementions)
{
	for (int i = 0; i < dementions; i++)
		if (vector[i] != 0)
			return 0;
	return 1;
}

int is_zero_basis_vector(float vector[], int dementions)
{
	for (int i = 0; i < dementions; i++)
		if (vector[i] != 0.0)
			return 0;
	return 1;
}

void init_basis(float* basis[], int demensions)
{
	for (int i = 0; i < demensions; i++)
	{
		basis[i] = (float*)malloc(demensions * sizeof(float));
		for (int k = 0; k < demensions; k++)
			basis[i][k] = 0;
	}
}

int is_solved_matrix(float* matrix[], float* basis[], int vector[], int dementions, int columns)
{
	float row_sum;
	int vector_idx = columns - 1;
	for (int d = 0; d < dementions; d++)
	{
		row_sum = 0.0;
		for (int c = 0; c < vector_idx; c++)
			row_sum += matrix[c][vector_idx] * basis[c][d];
		if (!almost_equal(row_sum, (float)vector[d]))
			return 0;
	}
	return 1;
}

int is_new_basis_vector(int vector[], float* basis[], int dementions)
{
	int column_number = 0;
	for (int v  = 0; v < dementions; v++)
	{
		if (is_zero_basis_vector(basis[v], dementions))
			break;
		column_number++;
	}

	if (column_number == 0)
		return 1;

	column_number++;  // basis + vector column

	//  MATRIX CREATION
	float** matrix = (float**)malloc(dementions * sizeof(float*));
	for(int d = 0; d < dementions; d++)
	{
		matrix[d] = (float*)malloc(column_number * sizeof(float));
		for (int c = 0; c < column_number - 1; c++)
			matrix[d][c] = basis[c][d];
	}
	for (int d = 0; d < dementions; d++)
		matrix[d][column_number - 1] = (float)vector[d];
	
	int result = is_linear_combination(matrix, basis, vector, dementions, column_number);
	for(int d = 0; d < dementions; d++)
		free((void*)matrix[d]);
	free((void*)matrix);

	return !result;
}

void print_matrix(float* matrix[], int dementions, int column_number)
{
	for (int d = 0; d < dementions; d++)
	{
		for (int c = 0; c < column_number; c++)
		{
			printf("%.2f ", matrix[d][c]);
		}
		printf("\n");
	}			
}

int is_linear_combination(float* matrix[], float* basis[], int vector[], int dementions, int column_number)
{
	int vector_idx = column_number - 1;
	int row_idx;
	float ratio;
	for (int d = 0; (d < dementions) && (d < vector_idx); d++)
	{		
		row_idx = get_row_idx(matrix, d, column_number);
		if (row_idx == -1)
		{
			if (!almost_equal(matrix[vector_idx][d], 0.0))
				return 0;
			else
				continue;
		}

		// Swap current row and the first row with not zero value of d demention
		swap_rows(matrix, d, row_idx);
		for (int c = vector_idx; c > - 1; c--)
			matrix[d][c] /= matrix[d][d];

		// Row reducing
		for (int i = d + 1; i < dementions; i++)
		{
			ratio = matrix[i][d];
			for (int c = 0; c < column_number; c++)
			{
				matrix[i][c] -= ratio * matrix[d][c];
				if (almost_equal(matrix[i][c], 0.0))
					matrix[i][c] = 0.0;
			}
		}
		for (int i = d - 1; i > -1; i--)
		{
			ratio = matrix[i][d];
			for (int c = 0; c < column_number; c++)
			{
				matrix[i][c] -= ratio * matrix[d][c];
				if (almost_equal(matrix[i][c], 0.0))
					matrix[i][c] = 0.0;
			}
		}
	}
	if(is_solved_matrix(matrix, basis, vector, dementions, column_number))
		return 1;
	return 0;
}

void swap_rows(float* matrix[], int d, int row_idx)
{
	float* temp = matrix[d];
	matrix[d] = matrix[row_idx];
	matrix[row_idx] = temp;
}

int get_row_idx(float* matrix[], int d, int column_number)
{
	for (int c = 0; c < column_number - 1; c++)
		if (!almost_equal(matrix[d][c], 0.0))
			return c;
	return -1;
}
