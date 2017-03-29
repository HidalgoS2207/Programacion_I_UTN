#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int verificador_posicion(int * tablero)
{
    int i = 0;

    for(i = 0; i < 8; i++)
    {
        if(*(tablero + i) != i + 1)
        {
            return 0;
        }
    }

    return 1;
}   

int validar_movimiento(int * tablero , int posicion , char direccion)
{
    int index= 0;
    int i = 0 ;

    for(i = 0; i < 9 ; i++)
    {
        if(posicion == *(tablero + i))
        {
            index = i;
        }
    }

    if(direccion == 's')
    {
        if(index < 3)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if(direccion == 'b')
    {
        if(index > 5)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if(direccion == 'd')
    {
        if(index == 2 || index == 5 || index == 8)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if(index == 0 || index == 3 || index == 6)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

void mostrar_tablero(int * tablero)
{
    int i = 0;

    for(i = 0 ; i < 8 ; i++)
    {
        printf(" %d " , *(tablero + i));

        if(i == 2 || i == 5)
        {
            printf("\n\n");
        }
    }

    printf(" %d \n" , *(tablero + i));

    printf("\n-------------------------------------------------\n");
}

void intercambiar_fichas(int * a , int * b)
{
    int aux_var = 0;

    aux_var = *a;
    *a = *b;
    *b = aux_var;
}

void intercambiar_fichas_user(int * tablero ,int ficha , char sentido)
{
    int i = 0;
    int index = 0;
    int aux = 0;

    for(i = 0; i < 9 ; i++)
    {
        if(ficha == *(tablero + i))
        {
            index = i;
        }
    }

    if(sentido == 's')
    {
        aux = *(tablero + index);
        *(tablero + index) = *(tablero + index - 3);
        *(tablero + index - 3) = aux;
    }
    else if(sentido == 'b')
    {
        aux = *(tablero + index);
        *(tablero + index) = *(tablero + index + 3);
        *(tablero + index + 3) = aux;
    }
    else if(sentido == 'd')
    {
        aux = *(tablero + index);
        *(tablero + index) = *(tablero + index + 1);
        *(tablero + index + 1) = aux;
    }
    else
    {
        aux = *(tablero + index);
        *(tablero + index) = *(tablero + index - 1);
        *(tablero + index - 1) = aux;
    }
}

void desordenar_tablero(int * tablero)
{
    int posicion = 0;
    int direccion = 0;
    int repeticiones = 0;

    int i = 0;

    repeticiones = (rand()%91) + 10;

    for( i = 0 ; i < repeticiones ; i++)
    {
        posicion = rand() % 5;
        if(posicion < 4)
        {
            direccion = rand() % 2;

            switch(posicion)
            {
                case 0:
                    if(direccion)
                    {
                        intercambiar_fichas((tablero + 0) , (tablero + 1));
                    }
                    else
                    {
                        intercambiar_fichas((tablero + 0) , (tablero + 3));
                    }
                    break;
                case 1:
                    if(direccion)
                    {
                        intercambiar_fichas((tablero + 2) , (tablero + 1));
                    }
                    else
                    {
                        intercambiar_fichas((tablero + 2) , (tablero + 5));
                    }
                    break;
                case 2:
                    if(direccion)
                    {
                        intercambiar_fichas((tablero + 8) , (tablero + 5));
                    }
                    else
                    {
                        intercambiar_fichas((tablero + 8) , (tablero + 7));
                    }
                    break;
                case 3:
                    if(direccion)
                    {
                        intercambiar_fichas((tablero + 6) , (tablero + 3));
                    }
                    else
                    {
                        intercambiar_fichas((tablero + 6) , (tablero + 7));
                    }
                    break;
            }
        }
        else
        {
            direccion = rand() % 4;

            switch(direccion)
            {
                case 0:
                    intercambiar_fichas((tablero + 4) , (tablero + 5));
                    break;
                case 1:
                    intercambiar_fichas((tablero + 4) , (tablero + 7));
                    break;
                case 2:
                    intercambiar_fichas((tablero + 4) , (tablero + 3));
                    break;
                case 3:
                    intercambiar_fichas((tablero + 4) , (tablero + 1));
                    break;
            }
        }
    }
}

int jugar(int * tablero)
{
    int ficha = 1;
    char destino = 's';
    int ganador = 0;

    while(ficha)
    {
        printf("\nSeleccione la ficha a mover:\n-->");
        scanf("%d" , &ficha);

        while(ficha > 8 || ficha < 0)
        {
            printf("\nError. Seleccione la ficha a mover:\n-->");
            scanf("%d" , &ficha);
        }

        if(ficha != 0)
        {
            getc(stdin);
            printf("\nSeleccione el sentido a mover la ficha:\n-->");
            scanf("%c" , &destino);

            while(destino != 's' && destino != 'b' && destino != 'd' && destino != 'i')
            {
                printf("\nError. Seleccione el sentido a mover la ficha:\n-->");
                scanf("%c" , &destino);
            }

            if(validar_movimiento(tablero , ficha ,destino))
            {
                intercambiar_fichas_user(tablero , ficha , destino);

                printf("\n\n");
                mostrar_tablero(tablero);

                if(verificador_posicion(tablero))
                {
                    ficha = 0;
                    ganador = 1;
                }
            }
            else
            {
                printf("\n\nError. Movimiento invalido\n");
            }
        }

    }

    if(ganador)
    {
        printf("\n\n-------------------------------------------------\nFELICITACIONES A GANADO EL JUEGO!\n\n");
    }

    return 0;
}

int main()
{
    int tablero[9];  

    srand((unsigned int)time(NULL));

    memset(tablero , 0 , sizeof(int ) * 9);

    int i = 0;

    for(i = 0; i < 8;i++)
    {
        *(tablero + i) = i + 1;
    }

    printf("\n-------------------------------------------------\n          POSICION DE FICHAS ESPERADO: \n\n");

    mostrar_tablero(tablero);

    printf("\n-------------------------------------------------\n          DESARROLLO: \n\n");
    printf("\n1 - Selecciona ficha por numero (0 para salir del juego)\n\n");
    printf("\n2 - Elije movimiento \n\n      Subir = s | Bajar = b | Derecha = d | Izquierda = i\n\n");
    printf("\n-------------------------------------------------\n                COMIENZA:\n\n");

    desordenar_tablero(tablero);

    mostrar_tablero(tablero);

    return jugar(tablero);
}