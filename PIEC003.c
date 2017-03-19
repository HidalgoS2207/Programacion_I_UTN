#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float get_number()
{
    float ret = 0.0;

    printf("\nIngrese Numero:");
    scanf("%f" , &ret);

    return ret;
}

float get_area(float radio)
{
    return  3.141592 * pow(radio , 2);    
}

int main()
{
    printf("\n\n%.3f\n",get_area( get_number() ) );

    return 0;
}