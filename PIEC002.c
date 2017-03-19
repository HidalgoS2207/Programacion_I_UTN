#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float number = 0;

    float promedio = 0.0;
    float suma = 0;
    float numb_max = (float)INT_MIN;
    float numb_min = (float)INT_MAX;

    for(int i = 0 ; i < 5 ; i++)
    {
        scanf("%f" , &number);

        suma += number;

        if(number > numb_max)
        {
            numb_max = number;
        }

        if(number < numb_min)
        {
            numb_min = number;
        }
    }

    promedio = suma / 5;

    printf("\n\nMaximo = %.2f \n Minimo = %.2f \n Promedio = %.2f \n" , numb_max , numb_min , promedio);

    return 0;
}