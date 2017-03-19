#include "utn.h"

int main()
{
    srand((unsigned int)time(NULL));

    int adivinar;
    int numero  = 101;
    int intentos = 0;

    char exit_game = 'n';

    printf("\n-------------------------------------------------------\nADIVINE EL NUMERO OCULTO\n\n");

    while(exit_game != 'y' && exit_game != 'Y')
    {
        adivinar = (rand() % 100);
        intentos = 0;  

        while(numero != adivinar && numero > 0)
        {
            getInt(&numero);
            intentos++;

            if(numero >= 0)
            {
                if(numero == adivinar)
                {
                    printf("\nFELCITACIONES HA ACERTADO EN %d INTENTOS\n" , intentos);
                }
                else if(numero > adivinar)
                {
                    printf("\nEl numero ingresado está por encima del numero oculto\n");
                }
                else
                {
                    printf("\nEl numero ingresado está por debajo del numero oculto\n");
                }
            }
            else
            {
                printf("\nJUEGO FINALIZADO POR EL USUARIO\n");
            }
        }

        numero = 101;

        printf("\nDesea terminar el programa? (y/n)");
        getChar(&exit_game);
    }

    printf("\n-----------------------------------------------------------\n");

    return 0;
}