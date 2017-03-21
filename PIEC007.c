#include "utn.h"

#define AGENDA_MAX_SIZE 200

void agenda_constructor(char * nombre_p , char * apellido_p , int * legajo_p)
{
    memset(nombre_p , '\0' , 128);
    memset(apellido_p , '\0' , 128);
    *legajo_p = -1;
} 

struct Agenda
{
    char nombre[128];
    char apellido[128];
    int legajo;  
};

int chequear_validez_ultimo(struct Agenda * agenda_p , int ultimo_legajo , int counter)
{
    if(ultimo_legajo <= 0)
    {
        return 0;
    }
    else
    {
        for(int i = 0; i < counter; i++)
        {
            if(ultimo_legajo == (agenda_p + i)->legajo)
            {
                return 0;
            }
        }
    }

    return 1;
}

int chequear_validez_general(struct Agenda * agenda_p , int legajo , int index)
{
    if(legajo <= 0)
    {
        return 0;
    }
    else
    {
        for(int i = 0; i < AGENDA_MAX_SIZE; i++)
        {
            if(i != index)
            {
                if(legajo == (agenda_p + i)->legajo)
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}

void ingreso_datos(struct Agenda * agenda_p)
{
    int counter = 0;
    int exit_carga_datos = 0;

    while((!exit_carga_datos) || (counter == AGENDA_MAX_SIZE - 1))
    {
        printf("\n---- Persona %d ----\nIngrese nombre de la persona \n-> " , counter + 1);
        scanf("%s" , (agenda_p + counter)->nombre );

        printf("\nIngrese apellido de la persona \n-> ");
        scanf("%s" , (agenda_p + counter)->apellido );

        printf("\nIngrese numero de legajo de la persona \n-> ");
        scanf("%d" , &(agenda_p + counter)->legajo );

        if(!chequear_validez_ultimo(agenda_p ,(agenda_p + counter)->legajo , counter ))
        {
            memset((agenda_p + counter)->nombre , '\0' , 128);
            memset((agenda_p + counter)->apellido , '\0' , 128);
            (agenda_p + counter)->legajo = -1;

            printf("\nError. Legajo repetido. La ultima operacion fue descartada\n\n");
        }
        else
        {
            printf("\nInformacion guardada correctamente\n");

            counter++;
        }

        printf("\nElija una accion \n0 - Ingresar otra persona \n1 - Finalizar carga de datos \n-> ");
        scanf("%d" , &exit_carga_datos );

        while(exit_carga_datos > 1 || exit_carga_datos < 0)
        {
            printf("\nError. Elija una accion \n0 - Ingresar otra persona \n1 - Finalizar carga de datos \n-> ");
            scanf("%d" , &exit_carga_datos );
        }
    }
}

void listar_todas(struct Agenda * agenda_p)
{
    for(int i = 0 ; i < AGENDA_MAX_SIZE ; i++)
    {
        if((agenda_p + i)->legajo != -1)
        {
            printf("\n----- PERSONA %d -----\n\n" , i + 1);
            printf("\nNombre: %s \nApellido: %s \nLegajo Nro: %d\n" , (agenda_p + i)->nombre , (agenda_p + i)->apellido , (agenda_p + i)->legajo);
            printf("\n----------------------\n\n");
        }
    }
}

int find_free_spot(struct Agenda * agenda)
{
    for(int i = 0; i < AGENDA_MAX_SIZE ; i++)
    {
        if((agenda + i)->legajo == -1)
        {
            return i;
        }
    }

    return -1;
}

void optimizar_espacio(struct Agenda * agenda , int index)
{
    for(int i = index + 1; i < AGENDA_MAX_SIZE;i++)
    {
        if((agenda + i)->legajo != -1)
        {
            (agenda + i - 1)->legajo = (agenda + i)->legajo;
            strcpy((agenda + i - 1)->nombre , (agenda + i)->nombre);
            strcpy((agenda + i - 1)->apellido, (agenda + i)->apellido);

            (agenda + i)->legajo = -1;
            memset((agenda + i)->nombre , '\0' , 128);
            memset((agenda + i)->apellido , '\0' , 128);
        }
    }
}

int main()
{
    printf("\n\n---------------------------------------------------------\n       EJERCICIO CLASE 007\n\n");

    struct Agenda agenda[AGENDA_MAX_SIZE];

    int opcion = 0;

    for( int i = 0 ; i < AGENDA_MAX_SIZE ; i++)
    {
        agenda_constructor((agenda + i)->nombre , (agenda + i)->apellido , &(agenda + i)->legajo);
    }

    ingreso_datos(agenda);

    while(opcion != 6)
    {
        printf("\n\n---------------------------------------------------------\n             MENU OPCIONES\n");
        printf("\n\n1 - Listar todas las personas agendadas \n2 - Listar una persona segun indice\n3 - Agregar una persona\n4 - Eliminar una persona\n5 - Modificar datos de una persona\n6 - Salir\n\n ->");
        scanf("%d" , &opcion);

        while(opcion > 6 || opcion < 1)
        {
            printf("\n\nERROR. Elija nuevamente. \n\n1 - Listar todas las personas agendadas \n2 - Listar una persona segun indice\n3 - Agregar una persona\n4 - Eliminar una persona\n5 - Modificar datos de una persona\n6 - Salir\n\n ->");
            scanf("%d" , &opcion);
        }

        switch(opcion)
        {
            case 1:
                listar_todas(agenda);
                break;
            case 2:
                {
                    int index = 0;

                    printf("\nIndique indice a buscar (1 - 200):\n ->");
                    scanf("%d" , &index);

                    while(index > 200 || index < 1)
                    {
                        printf("\nError. Indique nuevamente indice a buscar (1 - 200):\n ->");
                        scanf("%d" , &index);    
                    }

                    if((agenda + index)->legajo != -1)
                    {
                        printf("\n----- PERSONA %d -----\n\n" , index);
                        printf("\nNombre: %s \nApellido: %s \nLegajo Nro: %d\n" , (agenda + index - 1)->nombre , (agenda + index - 1)->apellido , (agenda + index - 1)->legajo);
                        printf("\n----------------------\n\n");
                    }
                    else
                    {
                        printf("\nError. Ninguna persona se encuentra agendada en ese indice.\n\n");
                    }
                }
                break;
            case 3:
                {
                    int index = find_free_spot(agenda);

                    if(index < 0)
                    {
                        printf("\n\nError. No hay mas espacio en la agenda. Intente primero eliminando archivos no necesarios.\n");
                    }
                    else
                    {
                        printf("\n---- Nueva Persona ----\nIngrese nombre de la persona \n-> ");
                        scanf("%s" , (agenda + index)->nombre );

                        printf("\nIngrese apellido de la persona \n-> ");
                        scanf("%s" , (agenda + index)->apellido);

                        printf("\nIngrese numero de legajo de la persona \n-> ");
                        scanf("%d" , &(agenda + index)->legajo);

                        if(!chequear_validez_general(agenda , (agenda + index)->legajo , index))
                        {
                            memset((agenda + index)->nombre , '\0' , 128);
                            memset((agenda + index)->apellido , '\0' , 128);
                            (agenda + index)->legajo = -1;

                            printf("\n\nError. Ese legajo ya existe en la base de datos. La ultima operacion fue descartada.\n");
                        }
                        else
                        {
                            printf("\n\nDatos cargados correctamente en la posicion %d" , index + 1);
                        }
                    }
                }
                break;
            case 4:
                {
                    int index = 0;
                    int confirmacion = 0;

                    printf("\nIndique indice a buscar (1 - 200):\n ->");
                    scanf("%d" , &index);

                    while(index > 200 || index < 1)
                    {
                        printf("\nError. Indique nuevamente indice a buscar (1 - 200):\n ->");
                        scanf("%d" , &index);    
                    }

                    if((agenda + index - 1)->legajo != -1)
                    {
                        printf("\n-----ELIMINAR PERSONA %d -----\n\n" , index);
                        printf("\nNombre: %s \nApellido: %s \nLegajo Nro: %d\n" , (agenda + index - 1)->nombre , (agenda + index - 1)->apellido , (agenda + index - 1)->legajo);
                        printf("\n----------------------\n\n");

                        printf("CONFIRMAR OPERACION\n0 - Cancelar Operacion de borrado\n1 - Confirmar operacion de borrado\n ->");
                        scanf("%d" , &confirmacion);

                        while(confirmacion < 0 || confirmacion > 1)
                        {
                            printf("\nError.0 - Cancelar Operacion de borrado\n1 - Confirmar operacion de borrado\n ->");
                            scanf("%d" , &confirmacion);    
                        }

                        if(confirmacion)
                        {
                            memset((agenda + index - 1)->nombre , '\0' , 128);
                            memset((agenda + index - 1)->apellido , '\0' , 128);
                            (agenda + index - 1)->legajo = -1;

                            if(index - 1 < AGENDA_MAX_SIZE - 1)
                            {
                                optimizar_espacio(agenda , index - 1);  
                            }
                            
                            printf("\nOperacion realizada con exito.\n\n");
                        }
                        else
                        {
                            printf("\nOperacion cancelada.\n\n");
                        }
                    }
                    else
                    {
                        printf("\nError. Ninguna persona se encuentra agendada en ese indice.\n\n");
                    }
                }
                break;
            case 5:
                {
                    int index = 0;
                    int confirmacion = 0;

                    char aux_nombre[128];
                    char aux_apellido[128];
                    int aux_legajo = -1;

                    memset(aux_nombre , '\0' , 128);
                    memset(aux_apellido , '\0' , 128);

                    printf("\nIndique indice a buscar (1 - 200):\n ->");
                    scanf("%d" , &index);

                    while(index > 200 || index < 1)
                    {
                        printf("\nError. Indique nuevamente indice a buscar (1 - 200):\n ->");
                        scanf("%d" , &index);    
                    }

                    if((agenda + index - 1)->legajo != -1)
                    {
                        printf("\n-----MODIFICAR DATOS PERSONA %d -----\n\n" , index);
                        printf("\nNombre: %s \nApellido: %s \nLegajo Nro: %d\n" , (agenda + index - 1)->nombre , (agenda + index - 1)->apellido , (agenda + index - 1)->legajo);
                        printf("\n----------------------\n\n");

                        printf("\n---- Modificar datos Persona ----\nIngrese nombre de la persona \n-> ");
                        scanf("%s" , aux_nombre);

                        printf("\nIngrese apellido de la persona \n-> ");
                        scanf("%s" , aux_apellido);

                        printf("\nIngrese numero de legajo de la persona \n-> ");
                        scanf("%d" ,&aux_legajo);

                        if(!chequear_validez_general(agenda , aux_legajo , -1))
                        {
                            printf("\n\nError. Ese legajo ya existe en la base de datos. La ultima operacion fue descartada.\n");
                        }
                        else
                        {
                                printf("\nCONFIRMAR OPERACION\n0 - Cancelar Operacion de modificacion de datos\n1 - Confirmar operacion de modificacion de datos\n ->");
                                scanf("%d" , &confirmacion);

                                while(confirmacion < 0 || confirmacion > 1)
                                {
                                    printf("\nError.0 - Cancelar Operacion de modificacion de datos\n1 - Confirmar operacion de modificacion de datos\n ->");
                                    scanf("%d" , &confirmacion);    
                                }

                                if(confirmacion)
                                {
                                    memset((agenda + index - 1)->nombre , '\0' , 128);
                                    memset((agenda + index - 1)->apellido , '\0' , 128);
                                    (agenda + index - 1)->legajo = -1;

                                    strcpy((agenda + index - 1)->nombre , aux_nombre);
                                    strcpy((agenda + index - 1)->apellido , aux_apellido);
                                    (agenda + index - 1)->legajo = aux_legajo;

                                    printf("\nOperacion realizada con exito.\n\n");
                                }
                                else
                                {
                                    printf("\nOperacion cancelada.\n\n");
                                }
                        }
                    }
                    else
                    {
                        printf("\nError. Ninguna persona se encuentra agendada en ese indice.\n\n");
                    }
                }
                break;
            default:
                break;
        }
    }

    return 0;
}

