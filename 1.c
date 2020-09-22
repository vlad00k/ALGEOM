


БИБЛИОТЕКА
#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED
#include <math.h>
#include <malloc.h>
#define PI 3.1415926535

typedef struct
{
    // Алгебраический вид
    float real; // Вещественная часть
    float imag; // Мнимая часть

    // Тригонометрический вид
    float arg; // Аргумент
    float module; // Модуль
} Complex;

Complex create_complex_number(float real_part, char sign, float imag_part)
{
    Complex z;
    z.real = real_part;
    z.imag = sign == '+' ? imag_part : -imag_part;
    z.module = sqrt(pow(z.real, 2) + pow(z.imag, 2));
    z.arg = atan2(z.imag, z.real);

    return z;
};

Complex in_power(Complex z, int n)
{
    Complex z_in_power;
    z_in_power.module = pow(z.module, n);
    z_in_power.arg = z.arg * n;
    z_in_power.real = z_in_power.module * cos(z_in_power.arg);
    z_in_power.imag = z_in_power.module * sin(z_in_power.arg);

    return z_in_power;
}

void print_algebraic_notation(Complex z)
{
    char sign = z.imag >= 0 ? '+' : '-';

    if (z.imag == 0)
    {
        printf("z = %.2f\n", z.real);
    }
    else if (sign == '+')
    {
        printf("z = %.2f + %.2fi\n", z.real, z.imag);
    }
    else
    {
        printf("z = %.2f - %.2fi\n", z.real, -z.imag);
    }
}

void print_trigonometric_notation(Complex z)
{
    char sign = z.arg >= 0 ? '+' : '-';

    if (z.arg == 0)
    {
        printf("z = %.2f * (cos(0) + i * sin(0))\n", z.module);
    }
    else if (sign == '+')
    {
        printf("z = %.2f * (cos(%.2f * pi) + i * sin(%.2f * pi))\n", z.module, fmod(z.arg, 2 * PI) / PI, fmod(z.arg, 2 * PI) / PI);
    }
    else
    {
        printf("z = %.2f * (cos(%.2f * pi) - i * sin(%.2f * pi))", z.module, fmod(-z.arg, 2 * PI) / PI, fmod(-z.arg, 2 * PI) / PI);
    }
}

void get_roots(Complex z, int n, Complex *roots)
{
    float real_part, imag_part;
    float module_in_power = pow(z.module, 1/(float)n);
    for (int k = 0; k < n; ++k)
    {
        real_part = module_in_power * cos((z.arg + 2 * PI * k) / n);
        imag_part = module_in_power * sin((z.arg + 2 * PI * k) / n);
        char sign = imag_part >= 0 ? '+' : '-';
        roots[k] = create_complex_number(real_part, sign, imag_part);
    }
}

#endif // COMPLEX_H_INCLUDED



#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include "complex.h"







int main()
{
    setlocale(LC_ALL, "Russian");
    Complex z;
    int n;
    float real_part, imag_part;
    char sign, imag_unit;
    printf("Введите комплексное число в формате x + yi:\n");
    printf("z = ");
    scanf("%f %c %f%c", &real_part, &sign, &imag_part, &imag_unit);
    z = create_complex_number(real_part, sign, imag_part);
    printf("n = ");
    scanf("%d", &n);
    printf("\n");

    printf("Число z:\n", n);
    printf("Алгебраическая форма:\n");
    print_algebraic_notation(z);
    printf("Тригонометрическая форма:\n");
    print_trigonometric_notation(z);
    printf("\n\n");

    printf("Число z ^ -1:\n");
    Complex re_z = in_power(z, -1);
    printf("Алгебраическая форма:\n");
    print_algebraic_notation(re_z);
    printf("Тригонометрическая форма:\n");
    print_trigonometric_notation(re_z);
    printf("\n\n");

    printf("Число z в степени %d:\n", n);
    Complex z_in_power = in_power(z, n);
    printf("Алгебраическая форма:\n");
    print_algebraic_notation(z_in_power);
    printf("Тригонометрическая форма:\n");
    print_trigonometric_notation(z_in_power);
    printf("\n\n");

    printf("Корни %d-ой степени из z:\n", n);
    Complex *roots = malloc(n * sizeof(Complex));
    get_roots(z, n, roots);
    for (int i = 0; i < n; ++i)
    {
        printf("%d.) ", i + 1);
        print_algebraic_notation(roots[i]);
    }

    return 0;
}





