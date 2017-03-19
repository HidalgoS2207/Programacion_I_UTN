#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calcular_parametros(float * conj_p , float * param_p)
{
    *(param_p + 1) = INT_MIN;
    *(param_p + 2) = INT_MAX;
    
    *(param_p) = (*(conj_p) + *(conj_p + 1) + *(conj_p + 2) + *(conj_p + 3) + *(conj_p + 4)) / 5;

    for(int i = 0; i < 5; i++)
    {
        if(*(conj_p + i) > *(param_p + 1))
        {
             *(param_p + 1) = *(conj_p + i);
        }

        if(*(conj_p + i) < *(param_p + 2))
        {
             *(param_p + 2) = *(conj_p + i);
        }
    }
}

void listar_todos_los_numeros(float * conj_p)
{
    printf("\n\nLISTA DE ELEMENTOS CARGADOS:\n");

    for(int i = 0; i < 5 ; i++)
    {
        printf("\n%d  - %.3f" , i+1 , *(conj_p + i));
    }

    printf("\n\n");
}

void input_usuario_inicial(float * conj_p)
{
    for(int i = 0; i < 5 ; i++)
    {
        printf("\nIngresar numero en posicion %d -> " , i + 1);
        scanf("%f" , (conj_p + i));
    }
}

int main_loop(float * conj_p)
{
    int exit_program = 0;
    int next_action = 0;

    float promedio = 0.0;

    float parametros[3]; // 0 - promedio || 1 - maximo valor || 2 - minimo valor

    input_usuario_inicial(conj_p);

    calcular_parametros(conj_p , parametros);

    while(!exit_program)
    {
        printf("\n\nSeleccione una accion: \n 1 - Listar todos los numeros ingresados \n 2 - Listas un numero especifico segun indice \n 3 - Mostrar maximo - minimo - promedio \n 4 - Modificar datos y recalcular parametros \n 5 - Salir\n\n ->");
        scanf("%d" , &next_action);

        while(next_action > 5 || next_action <= 0)
        {
            printf("\nError. Ingrese una de las siguientes acciones: \n 1 - Listar todos los numeros ingresados \n 2 - Listas un numero especifico segun indice \n 3 - Mostrar maximo - minimo - promedio \n 4 - Modificar datos y recalcular parametros \n 5 - Salir\n\n ->");
            scanf("%d" , &next_action);
        }

        switch(next_action)
        {
            case 1:
                listar_todos_los_numeros(conj_p);
                break;
            case 2:
            {
                int index = 0;

                printf("\nDefina el indice a buscar (1 - 5)  -> ");
                scanf("%d" , &index);
                
                while(index > 5 || index <= 0)
                {
                    printf("\nError. Fuera de rango. Vuelva a definir indice (1 - 5) ->");
                    scanf("%d" , &index);
                }

                printf("\n\nElemento %d = %.3f" , index ,*(conj_p + index - 1));
            }
                break;
            case 3:
                printf("\nLISTA DE PARAMETROS:\n\n Maximo  = %.3f \n Minimo = %.3f \n Promedio = %.3f \n" , *(parametros + 1) , *(parametros + 2) , *(parametros));
                break;
            case 4: 
            {
                int index = 0;
                float nuevo_numero = 0 ;

                printf("\nDefina el indice del numero a modificar (1 - 5)  -> ");
                scanf("%d" , &index);
                
                while(index > 5 || index <= 0)
                {
                    printf("\nError. Fuera de rango. Vuelva a definir indice (1 - 5) ->");
                    scanf("%d" , &index);
                }

                printf("\nDefina el nuevo valor a almacenar  -> ");
                scanf("%f" , &nuevo_numero);

                *(conj_p + index - 1) = nuevo_numero;

                calcular_parametros(conj_p , parametros);
            }
                break;
            case 5:
                exit_program = 1;
                break;
        }
    }

    printf("\n\nPrograma finalizado por el usuario.");
    printf("\n\n----------------------------------------------------------\n");

    return 0;
}

void inicializar_conjunto(float * conj_p)
{
    for(int i = 0 ; i < 5 ; i++)
    {
        *(conj_p + i) = 0.0;
    }
}

int main()
{
    printf("\n-----------------------------------------------------------\n");
    printf("\nEJERCICIO 5 - ARRAYS\n");

    float conjunto[5];

    inicializar_conjunto(conjunto);

    return main_loop(conjunto);
}