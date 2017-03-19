#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>

void getInt(int * numb)
{
    printf("\nIngrese numero entero: ");
    scanf("%d" , numb);
}

void getFloat(float * numb)
{
    printf("\nIngrese numero de precisión decimal (hasta 3 dec): ");
    scanf("%.3f" , numb);
}

void getChar(char * letra)
{   
    printf("\nIngrese un caracter: ");
    scanf( " %c" , letra);
}