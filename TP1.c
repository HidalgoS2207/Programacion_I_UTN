#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int numero = 0;

    int contador_pares = 0;
    int contador_impares = 0;
    int contador_total = 0;
    int sumatoria_impares = 0;
    int sumatoria_total = 0;
    float promedio_general = 0.0;
    int numero_mayor = INT_MIN;
    int impar_menor = INT_MAX;
    int intervalo[3]; // [0] -> de 3 a 15 | [1] -> de 16 a 29 | [2] -> 30 o mas

    memset(intervalo , 0 , sizeof(int) * 3);

    int i = 0;

    int sumatoria_antecesores = 0;

    printf("\n-----------------------------------------\n           TRABAJO PRACTICO Nro 1\n\n");
    printf("Ingrese un numero (negativo para salir):\n->");
    scanf("%d" , &numero);

    while(numero >= 0)
    {
        contador_total++;

        if(numero > numero_mayor)
        {
            numero_mayor = numero;
        }

        if(numero % 2 == 0)
        {
            contador_pares++;
        }
        else
        {
            contador_impares++;

            if(numero < impar_menor)
            {
                impar_menor = numero;
            }

            sumatoria_impares += numero;
        }

        sumatoria_total += numero;

        if(numero >= 3 && numero <= 15)
        {
            intervalo[0]++;
        }
        else if(numero >= 16 && numero <= 29)
        {
            intervalo[1]++;
        }
        else if(numero >= 30)
        {
            intervalo[2]++;
        }

        printf("Ingrese siguiente numero (negativo para salir):\n->");
        scanf("%d" , &numero);
    }

    if(contador_total != 0)
    {
        promedio_general = (float)sumatoria_total / (float)contador_total;

        printf("\n------------------------------------------------------\nRESULTADOS: \n");
        printf("\nCANTIDAD NUMEROS PARES --> %d" , contador_pares);
        printf("\nCANTIDAD NUMEROS IMPARES --> %d" , contador_impares);
        printf("\nSUMATORIA IMPARES --> %d" , sumatoria_impares);
        printf("\nPROMEDIO GENERAL --> %.2f" , promedio_general);
        printf("\nMAYOR NUMERO INGRESADO --> %d" , numero_mayor);
        if(impar_menor != INT_MAX)
        {
            printf("\nMENOR NUMERO IMPAR --> %d" , impar_menor);
        }
        printf("\nNUMEROS ENTRE 3 y 15 --> %d" , intervalo[0]);
        printf("\nNUMEROS ENTRE 16 y 29 --> %d" , intervalo[1]);
        printf("\nNUMEROS MAYORES A 30 --> %d" , intervalo[2]);

        printf("\n\n¿Desea ver lista de antecesores a la suma de imprares\n1 - SI\n0 - NO\n\n");
        scanf("%d" , &numero);

        while(numero > 1 || numero < 0)
        {
            printf("\nError. ¿Desea ver lista de antecesores a la suma de imprares\n1 - SI\n0 - NO\n\n");
            scanf("%d" , &numero);
        }

        for(i = sumatoria_impares ; i > 0 ; i--)
        {
            sumatoria_antecesores += i;

            if(numero)
            {
                printf("\n--> %d" , i);
            }
        }

        printf("\n\nSUMATORIA ANTECESORES A LA SUMA DE NUMEROS IMPARES --> %d" , sumatoria_antecesores);
    }
    else
    {
        printf("\n\nNo se ingreso ningun numero\n----------------------------------------\nPROGRAMA TERMINADO\n\n");
    }

    return 0;
}