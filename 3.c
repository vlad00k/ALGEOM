#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>
float dot(int vector[], float basis_vector[], int dementions);
int is_new_basis(int vector[], float* basis[], int dementions);
float get_length(int vector[], int dementions);
void get_unit_vector(int vector[], float basis_vector[], int dementions);
int is_zero_vector(int vector[], int dementions);
int is_zero_basis_vector(float vector[], int dementions);
void init_basis(float* basis[], int demensions);
int almost_equal(float a, float b);
float is_collinear(int vector[], float basis_vector[], int dementions);
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
				get_unit_vector(vectors[i], basis[current_basis_idx], dementions);
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

float is_collinear(int vector[], float basis_vector[], int dementions)
{
	float ratio = 0.0;
	for (int i = 0; i < dementions; i++)
		if (vector[i] != 0 && !almost_equal(basis_vector[i], 0.0))
		{
			ratio += (float)vector[i] / basis_vector[i];
			break;
		}

	if (ratio == 0.0)
		return 0;
	else
	{
		for (int i = 0; i < dementions; i++)
			if (!almost_equal((float)vector[i], ratio * basis_vector[i]))
				return 0;
	}
	return 1;

}

int almost_equal(float a, float b)
{
	if (a > b)
		return a - b < 0.0001 ? 1 : 0;
	else
		return b - a < 0.0001 ? 1 : 0;
}

int is_new_basis(int vector[], float* basis[], int dementions)
{
	if (is_zero_basis_vector(basis[0], dementions))
		return 1;
	for (int i = 0; i < dementions; i++)
	{
		if (is_zero_basis_vector(basis[i], dementions))
			return 1;
		if (is_collinear(vector, basis[i], dementions))
			return 0;
	}
	return 0;
}

float get_length(int vector[], int dementions)
{
	int l = 0;
	for (int i = 0; i < dementions; i++)
		l += vector[i] * vector[i];
	return (float)sqrt((long double)l);
}

void get_unit_vector(int vector[], float basis_vector[], int dementions)
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
