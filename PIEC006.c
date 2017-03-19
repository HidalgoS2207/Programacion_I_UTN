#include "PIEC006.h"

int main()
{
    char user_str[256];
    int counter = 0;

    int resultado = 0 ;

    printf("---------------------------------------------------\n\n       EJERCICIO CLASE 6\n\n");

    int terminar_programa = 0;

    while(!terminar_programa)
    {
        memset(user_str , '\0' , 256);
        counter = 0;

        printf("\n\nIngrese una secuencia de caracteres (MAX 256 B): \n\n-> ");
        
        while(user_str[counter - 1] != '\n' && counter < 256)
        {
            user_str[counter] = getc(stdin);

            counter++;
        }

        user_str[counter] = '\0';

        printf("\n\n");
        for(int i = 0; user_str[i] != '\0' ; i++)
        {
            printf("%c" , *(user_str + i));
        }

        switch(detect_content(user_str))
        {
            case -2:
                printf("\nError en la cadena de caraceteres.");
                break;
            case -1:
                printf("\nCadena de caracteres vacia.");
                break;
            case 0:
                printf("\nCadena de caracteres Numerica.");
                break;
            case 1:
                printf("\nCadena de caracteres Alfabetica.");
                break;
            case 2:
                printf("\nCadena de caracteres Alfanumerica.");
                break;
        }

        printf("\n\nSeleccione una opcion \n0 - Continuar \n1 - Salir \n\n-> ");
        scanf("%d" , &terminar_programa);

        while(terminar_programa > 1 || terminar_programa < 0)
        {
             printf("\n\nError. Seleccione una opcion \n 0 - Continuar \n 1 - Salir \n\n ->");
             scanf("%d" , &terminar_programa);
        }

        getchar();
    }

    printf("       PROGRAMA TERMINADO POR EL USUARIO\n\n---------------------------------------------------\n\n");

    return 0;
}