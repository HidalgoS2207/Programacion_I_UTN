//#include "utn.h"

//banca quebrada
//muestra de puntajes obtenidos
//posible bug en la premiacion cuando un jugador quedo descartado
//cuando se oprime 4 para ver el esta de los jugadores debe decir OPONENTES en vez de JUGADORES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <limits.h>

//clase 009
//juego del 7 y medio

struct Carta
{
    int numero;
    float valor;
    char nombre[16];
    int disponible;
};

struct Jugador
{
    float presupuesto;
    struct Carta *cartas_jugador[12];
    float suma_cartas;
    int estado;
    int indice_carta_oculta;
    float apuesta_realizada;
    int cantidad_cartas;
};

void inicializar_jugador(struct Jugador * jugador_p)
{
    (jugador_p)->presupuesto = 200;
    (jugador_p)->suma_cartas = 0;
    (jugador_p)->estado = 1;
    (jugador_p)->indice_carta_oculta = 0;
    (jugador_p)->apuesta_realizada = 0;
    (jugador_p)->cantidad_cartas = 0;

	int i = 0;

    for(i = 0; i < 12 ; i++)
    {
        *((jugador_p)->cartas_jugador + i) = NULL;
    }
}

void inicializar_cartas(struct Carta * cartas_p)
{
	int i = 0;
	int j = 0;

    for(j = 0; j < 4 ; j++)
    {
        for(i = 0; i < 10;i++)
        {
            if(i >= 7)
            {
                (cartas_p + i+ (j*10))->valor = 0.5;
                (cartas_p + i + (j*10))->numero = i + 3;
            }
            else
            {
                (cartas_p + i + (j*10))->valor = i + 1;
                (cartas_p + i + (j*10))->numero = i + 1;
            }

            switch(j)
            {
                case 0:
                    strcpy((cartas_p + i + (j*10))->nombre ,"Oro");
                    break;
                case 1:
                    strcpy((cartas_p + i + (j*10))->nombre , "Copa");
                    break;
                case 2:
                    strcpy((cartas_p + i + (j*10))->nombre , "Espada");
                    break;
                case 3:
                    strcpy((cartas_p + i + (j*10))->nombre , "Basto");
                    break;
            }

            (cartas_p + i + (j*10))->disponible = 1;
        }
    }
}

void reset_cartas(struct Carta * cartas_p)
{
	int i = 0;

    for(i = 0; i < 40 ; i++)
    {
        (cartas_p + i)->disponible = 1;
    }
}

void reset_jugadores(struct Jugador * jugador_p)
{
	int i = 0;

    (jugador_p)->suma_cartas = 0;
    (jugador_p)->apuesta_realizada = 0;
    (jugador_p)->cantidad_cartas = 0;
    (jugador_p)->indice_carta_oculta = 0 ;
    
    if((jugador_p)->presupuesto < 10)
    {
        (jugador_p)->estado = 0;
    }
    else
    {
        (jugador_p)->estado = 1;
    }

    for( i = 0; i < 12 ; i++)
    {
        ((jugador_p)->cartas_jugador)[i] = NULL;
    }
}

float get_factor(float valor_carta)
{
    if(valor_carta == .5)
    {
        return .25;
    }
    else if(valor_carta > .5 && valor_carta <= 3 )
    {
        return .125;
    }
    else if(valor_carta > 3 && valor_carta <= 5)
    {
        return .175;
    }
    else if(valor_carta > 5)
    {
        return .325;
    }
}

int IA_move(struct Jugador * op_lista ,  int turno_oponente , struct Jugador * jugador_1 , struct Carta * cartas_p,int tipo_de_operacion, int banca_flag )
{
    switch(tipo_de_operacion)
    {
        case 0: //realiza apuesta
            (op_lista + turno_oponente)->apuesta_realizada = get_factor((op_lista + turno_oponente)->cartas_jugador[0]->valor) * (op_lista + turno_oponente)->presupuesto;
            if((op_lista + turno_oponente)->apuesta_realizada < 10.0)
            {
                (op_lista + turno_oponente)->apuesta_realizada = 10.0;
            }
            (op_lista + turno_oponente)->presupuesto -= (op_lista + turno_oponente)->apuesta_realizada;

            printf("\n\nOponente %d Realiza apuesta de $%.1f\n" , turno_oponente + 1 , (op_lista + turno_oponente)->apuesta_realizada);
            return 0;
        case 1: //realiza una jugada
            {
                int indice_aux = 0;
                if((op_lista + turno_oponente)->suma_cartas <= 5)
                {
                    indice_aux = rand() % 40;

                    while(!(cartas_p + indice_aux)->disponible)
                    {
                        indice_aux = rand() % 40;
                    }

                    ((op_lista + turno_oponente)->cartas_jugador)[(op_lista + turno_oponente)->cantidad_cartas] = (cartas_p + indice_aux);
                    (cartas_p + indice_aux)->disponible = 0;
                    (op_lista + turno_oponente)->cantidad_cartas++;

                    if(rand() % 2)
                    {
                        (op_lista + turno_oponente)->indice_carta_oculta = (op_lista + turno_oponente)->cantidad_cartas - 1;
                    }

                    (op_lista + turno_oponente)->suma_cartas += (cartas_p + indice_aux)->valor;

                    if(!banca_flag)
                    {
                        printf("\n--> Oponente %d Pide una carta." , turno_oponente + 1);
                    }
                    else
                    {
                        printf("\n--> La Banca Pide una carta.");
                    }
                }
                else
                {
                    int decision = rand() % 2;

                    if(decision)
                    {
                        indice_aux = rand() % 40;

                        while(!(cartas_p + indice_aux)->disponible)
                        {
                            indice_aux = rand() % 40;
                        }

                        ((op_lista + turno_oponente)->cartas_jugador)[(op_lista + turno_oponente)->cantidad_cartas] = (cartas_p + indice_aux);
                        (cartas_p + indice_aux)->disponible = 0;
                        (op_lista + turno_oponente)->cantidad_cartas++;

                        if(rand() % 2)
                        {
                            (op_lista + turno_oponente)->indice_carta_oculta = (op_lista + turno_oponente)->cantidad_cartas - 1;
                        }

                        (op_lista + turno_oponente)->suma_cartas += (cartas_p + indice_aux)->valor;

                        if(!banca_flag)
                        {
                            printf("\n--> Oponente %d Pide una carta." , turno_oponente + 1);
                        }
                        else
                        {
                            printf("\n--> La Banca Pide una carta.");
                        }
                    }
                    else
                    {
                        if(!banca_flag)
                        {
                            printf("\n--> Oponente %d Finaliza el turno." ,turno_oponente + 1 );
                        }
                        else
                        {
                            printf("\n--> La Banca finaliza su turno.");
                        }
                        return 1;
                    }
                }
                
                if((op_lista + turno_oponente)->suma_cartas > 7.5)
                {
                    (op_lista + turno_oponente)->estado = 0;

                    if(!banca_flag)
                    {
                        printf("\n--> Oponente %d Queda fuera de la partida por excederse de 7.5 en la suma de cartas." , turno_oponente + 1);
                    }
                    else
                    {
                        printf("\n--> La Banca finaliza su turno.");
                    }
                }
            }

            if((op_lista + turno_oponente)->estado)
            {
                return 0;
            }
            else
            {
                return 1;
            }
    }
}

int update(int * state ,int * turno,int * turno_oponente, struct Jugador * banca , struct Jugador * jugador_1 , struct Jugador * op_lista, int oponentes , struct Carta * cartas_p)
{
	int i = 0;
	int j = 0;

    switch(*state)
    {
        case 0: //repartir cartas 1 por jugador
            {
                int indice_aux = 0;

                for( i = 0 ; i < oponentes ; i++)
                {
                    if((op_lista + i)->presupuesto > 10)
                    {
                        indice_aux = rand() % 40;

                        while(!(cartas_p + indice_aux)->disponible)
                        {
                            indice_aux = rand() % 40;
                        }

                        ((op_lista + i)->cartas_jugador)[0] = (cartas_p + indice_aux);
                        (cartas_p + indice_aux)->disponible = 0;
                        (op_lista + i)->cantidad_cartas++;
                    }
                }

                indice_aux = rand() % 40;

                while(!(cartas_p + indice_aux)->disponible)
                {
                    indice_aux = rand() % 40;
                }

                (cartas_p + indice_aux)->disponible = 0;
                jugador_1->cartas_jugador[0] = (cartas_p + indice_aux);
                jugador_1->cantidad_cartas++;

                indice_aux = rand() % 40;

                while(!(cartas_p + indice_aux)->disponible)
                {
                    indice_aux = rand() % 40;
                }

                (cartas_p + indice_aux)->disponible = 0;
                banca->cartas_jugador[0] = (cartas_p + indice_aux);
                banca->cantidad_cartas++;
            }

            if(*turno == 0)
            {
                (*state)++;
            }
            else
            {
                (*state) = 2;
            }
            
            return 0;
        case 1: //pide jugador 1
            {
                int finalizar_turno = 0;
                int siguiente_accion = 0;

                printf("\n--------------------------------------\nTURNO JUGADOR 1 --> \nSu carta es el %d de %s -- \nValor de la carta -> %.1f -- \nPuntaje total -> %.1f --" ,  jugador_1->cartas_jugador[0]->numero , jugador_1->cartas_jugador[0]->nombre , jugador_1->cartas_jugador[0]->valor , jugador_1->cartas_jugador[0]->valor );

                jugador_1->suma_cartas += jugador_1->cartas_jugador[0]->valor;

                printf("\nSaldo actual: $%.1f -- \n\nRealice su apuesta:\n->" , jugador_1->presupuesto);
                scanf("%f" , &(jugador_1->apuesta_realizada));

                while(jugador_1->apuesta_realizada < 10 || jugador_1->apuesta_realizada > jugador_1->presupuesto)
                {
                    if(jugador_1->apuesta_realizada < 10)
                    {
                        printf("\n\nSu apuesta esta por debajo de lo permitido en esta ronda. Haga una apuesta mas grande.\n->");
                    }
                    else
                    {
                        printf("\n\nSu apuesta supera su saldo actual. Haga una apuesta acorde a su saldo.\n->");
                    }

                    scanf("%f" , &(jugador_1->apuesta_realizada));
                }

                jugador_1->presupuesto -= jugador_1->apuesta_realizada;
                banca->presupuesto += jugador_1->apuesta_realizada;
                printf("\nApuesta realizada con exito. Su saldo actual es de $%.1f.- \nComienza el juego:\n" , jugador_1->presupuesto);

                while(!finalizar_turno && jugador_1->estado)
                {
                    printf("\n\n-------------------------------\n\nElija siguiente accion \n1 - Plantarse\n2 - Pedir Carta Tapada\n3 - Pedir carta Visible\n4 - Ver estado del resto de los jugadores\n->");
                    scanf("%d" , &siguiente_accion);

                    while(siguiente_accion > 4 || siguiente_accion < 1)
                    {
                        printf("\n\n-------------------------------\n\nError. Elija siguiente accion \n1 - Plantarse\n2 - Pedir Carta Tapada\n3 - Pedir carta Visible\n4 - Ver estado del resto de los jugadores\n->");
                        scanf("%d" , &siguiente_accion); 
                    }
                    
                    switch(siguiente_accion)
                    {
                        case 1:
                            finalizar_turno = 1;
                            break;
                        case 2:
                        {
                            int indice_aux = 0;

                            indice_aux = rand() % 40;

                            while(!(cartas_p + indice_aux)->disponible)
                            {
                                indice_aux = rand() % 40;
                            }

                            (cartas_p + indice_aux)->disponible = 0;
                            jugador_1->cartas_jugador[jugador_1->cantidad_cartas] = (cartas_p + indice_aux);
                            jugador_1->cantidad_cartas++;
                            jugador_1->indice_carta_oculta = jugador_1->cantidad_cartas - 1;

                            jugador_1->suma_cartas += (cartas_p + indice_aux)->valor;

                            printf("\nSuma de puntos: %.1f" , jugador_1->suma_cartas);

                            for( j = 0; j < jugador_1->cantidad_cartas;j++)
                            {
                                if(jugador_1->indice_carta_oculta != j)
                                {
                                        printf("\nCarta Visible Nro %d --> %d de %s" , j + 1, jugador_1->cartas_jugador[j]->numero , jugador_1->cartas_jugador[j]->nombre );
                                }
                                else
                                {
                                        printf("\nCarta Oculta Nro %d --> %d de %s" , j + 1, jugador_1->cartas_jugador[j]->numero , jugador_1->cartas_jugador[j]->nombre );
                                }
                            }

                            if(jugador_1->suma_cartas > 7.5)
                            {
                                jugador_1->indice_carta_oculta = -1;
                                jugador_1->estado = 0;

                                printf("\n\nLa suma del puntaje de las cartas ha superado 7.5 puntos. Usted queda fuera del juego.");
                            }
                        }
                            break;
                        case 3:
                        {
                            int indice_aux = 0;

                            indice_aux = rand() % 40;

                            while(!(cartas_p + indice_aux)->disponible)
                            {
                                indice_aux = rand() % 40;
                            }

                            (cartas_p + indice_aux)->disponible = 0;
                            jugador_1->cartas_jugador[jugador_1->cantidad_cartas] = (cartas_p + indice_aux);
                            jugador_1->cantidad_cartas++;

                            jugador_1->suma_cartas += (cartas_p + indice_aux)->valor;

                            printf("\nSuma de puntos: %.1f" , jugador_1->suma_cartas);

                            for( j = 0; j < jugador_1->cantidad_cartas;j++)
                            {
                                if(jugador_1->indice_carta_oculta != j)
                                {
                                        printf("\nCarta Visible Nro %d --> %d de %s" , j + 1, jugador_1->cartas_jugador[j]->numero , jugador_1->cartas_jugador[j]->nombre );
                                }
                                else
                                {
                                        printf("\nCarta Oculta Nro %d --> %d de %s" , j + 1, jugador_1->cartas_jugador[j]->numero , jugador_1->cartas_jugador[j]->nombre );
                                }
                            }

                            if(jugador_1->suma_cartas > 7.5)
                            {
                                jugador_1->indice_carta_oculta = -1;
                                jugador_1->estado = 0;

                                printf("\n\nLa suma del puntaje de las cartas ha superado 7.5 puntos. Usted queda fuera del juego.");
                            }
                        }
                            break;
                        case 4:
                            for( i = 0; i < oponentes ; i++)
                            {
                                printf("\n---------------\nJUGADOR %d\n" , i + 1);

                                for( j = 0; j < (op_lista + i)->cantidad_cartas;j++)
                                {
                                    if((op_lista + i)->indice_carta_oculta != j)
                                    {
                                        printf("\nCarta Nro %d --> %d de %s" , j + 1, (op_lista + i)->cartas_jugador[j]->numero , (op_lista + i)->cartas_jugador[j]->nombre );
                                    }
                                    else
                                    {
                                        printf("\nCarta Oculta.");
                                    }
                                }
                            }
                            break;
                    }
                }
            }
            *turno = -1;
            if((*turno_oponente) == oponentes)
            {
                (*state)  = 3;
            }
            else
            {
                (*state)++;
            }
            return 0;
        case 2: // piden oponentes
        {
            if((*turno_oponente) + 1 <= oponentes)
            {
                if((op_lista + (*turno_oponente))->estado)
                {
                    int finalizar_turno = 0;

                    while(!finalizar_turno)
                    {
                        if((op_lista + (*turno_oponente))->apuesta_realizada == 0)
                        {
                            printf("\n-------------------------\nTurno Oponente %d\n" , (*turno_oponente) + 1);

                            (op_lista + (*turno_oponente))->suma_cartas += (op_lista + (*turno_oponente))->cartas_jugador[0]->valor;

                            IA_move(op_lista , *turno_oponente , jugador_1 ,cartas_p, 0 ,0 );

                            banca->presupuesto += (op_lista + (*turno_oponente))->apuesta_realizada;
                        }
                        else
                        {
                            finalizar_turno = IA_move(op_lista , *turno_oponente , jugador_1 ,cartas_p, 1 ,0 );
                        }
                    }

                    if(!(op_lista + (*turno_oponente))->estado)
                    {
                        //banca->presupuesto += (op_lista + (*turno_oponente))->apuesta_realizada;
                        (op_lista + (*turno_oponente))->apuesta_realizada = 0;
                    }
                }
                else
                {
                    printf("\n-------------------------\nJugador %d no participa por falta de fondos para esta sesion." , (*turno_oponente) + 1);
                }
            }
        }
            if((*turno_oponente) + 1 > oponentes)
            {
                if((*turno) == -1)
                {
                    (*state) = 3;
                }
                else
                {
                    (*state) = 1;
                }
            }
            else if((*turno_oponente) + 1 == *turno)
            {
                (*state) = 1;

                (*turno_oponente)++;
            }
            else
            {
                (*turno_oponente)++;
            }
            return 0;
        case 3: //pide la banca
            int finalizar_turno = 0;

            printf("\n-------------------------\nTurno de la Banca\n");

            while(!finalizar_turno)
            {
                finalizar_turno = IA_move(banca , 0 , jugador_1 ,cartas_p, 1  ,1 );
            }
            (*state) = 4;
            return 0;
        case 4: //resultados
            {
                int i = 0;
                int counter = 0;

                float dif_banca = -1;
                float dif_oponentes[6];
                memset(dif_oponentes, -1 ,sizeof(float) * 6 );
                float dif_jugador_1 = -1;

                if((banca)->suma_cartas <= 7.5)
                {
                    dif_banca = 7.5 - (banca)->suma_cartas;
                }

                for(i = 0 ; i < oponentes; i++)
                {
                    if((op_lista + i)->estado)
                    {
                        dif_oponentes[i] = 7.5 - (op_lista)->suma_cartas;

                        counter++;
                    }
                }

                if(jugador_1->estado)
                {
                    dif_jugador_1 = 7.5 - (jugador_1)->suma_cartas;

                    counter++;
                }

                if(counter == 0)
                {
                    printf("\n\n--------------------------------------------------\n\nTodos los jugadores quedaron descartados por superar los 7.5 puntos en la suma de cartas.\n\n");
                }
                else
                {
                    counter = 0;

                    if(dif_banca == -1)
                    {
                        printf("\n\n--------------------------------------------------\n\nLa banca paga a todos los jugadores que no superaron los 7.5 puntos en la suma de cartas.\n\n");

                        for(i = 0; i < oponentes;i++)
                        {
                            if(dif_oponentes[i] >= 0)
                            {
                                (op_lista + i)->presupuesto += (((op_lista + i)->apuesta_realizada) * 2);
                                (banca)->presupuesto -= (((op_lista + i)->apuesta_realizada) * 2);

                                printf("\n\nOponente %d recibe $%.1f de la banca\n" , i + 1,(((op_lista + i)->apuesta_realizada))*2);
                                counter++;
                            }
                        }

                        if(dif_jugador_1 >= 0)
                        {
                            (jugador_1)->presupuesto += (((jugador_1)->apuesta_realizada) * 2);
                            (banca)->presupuesto -= (((jugador_1)->apuesta_realizada) * 2);

                            printf("\n\nJugador 1 recibe $%.1f de la banca\n" ,(((jugador_1)->apuesta_realizada))*2);
                            counter++;
                        }

                        if(counter == 0)
                        {
                            printf("\n\nNingun jugador sumo por debajo de los 7.5 puntos.\n\n");
                        }
                    }
                    else
                    {
                        printf("\n\n--------------------------------------------------\n\nLa banca compite con los jugadores por cercania a los 7.5 puntos en la suma de cartas.\n\n");

                        for(i = 0; i < oponentes;i++)
                        {
                            if(dif_oponentes[i] < dif_banca && dif_oponentes[i] != -1)
                            {
                                (op_lista + i)->presupuesto += (((op_lista + i)->apuesta_realizada) * 2);
                                (banca)->presupuesto -= (((op_lista + i)->apuesta_realizada) * 2);

                                printf("\n\nOponente %d recibe $%.1f de la banca\n" , i + 1,(((op_lista + i)->apuesta_realizada)) * 2);

                                counter++;
                            }
                        }

                        if(dif_jugador_1 < dif_banca && dif_jugador_1 != -1)
                        {
                            (jugador_1)->presupuesto += (((jugador_1)->apuesta_realizada) * 2);
                            (banca)->presupuesto -= (((jugador_1)->apuesta_realizada) * 2);

                            printf("\n\nJugador 1 recibe $%.1f de la banca\n" ,(((jugador_1)->apuesta_realizada))*2);

                            counter++;
                        }

                        if(counter == 0)
                        {
                            printf("\n\nNingun jugador supero a la banca en la suma de puntos.\n\n");
                        }
                    }
                }
            }
            return 1;
        default:
            return -1;
    }
}

int main()
{
    int game_over = 0;
    int otra_partida = 1;
     
    int game_state = 0;
    int turno_J1 = 0;
    int turno_oponente = 0;
    int bolsillo = 1000;
    int oponentes = 0;
    struct Jugador * op_lista = NULL;
    struct Jugador jugador_1;
    struct Jugador banca;

    struct Carta cartas[40];

	int i = 0;
	int j = 0;

    srand((unsigned int)time(NULL));

    inicializar_cartas(cartas);

    printf("-------------------------------------------------\n\n               CLASE 009 - JUEGO DEL 7 y MEDIO\n\n");
    printf("\nDefina cantidad de oponentes (1 - 7): ");
    scanf("%d" , &oponentes);

    while(oponentes > 7 || oponentes < 1)
    {
        printf("\nError. Defina cantidad de oponentes (1 - 7): ");
        scanf("%d" , &oponentes);
    }
    
    if(oponentes > 1)
    {
        oponentes--;

        op_lista = (struct Jugador*) malloc(oponentes);

        for( i = 0 ; i < oponentes;i++)
        {
            inicializar_jugador(op_lista + i);
        }
    }
    else
    {
        oponentes--;
    }

    if(oponentes == 0)
    {
        turno_J1 = 0;
    }
    else
    {
        turno_J1 = (rand() % (oponentes + 1));
        //turno_J1 = 5;
    }

    inicializar_jugador(&jugador_1);
    inicializar_jugador(&banca);

    banca.presupuesto = 5000;

    //loop principal del juego
    while(!game_over && otra_partida)
    {
        game_over = update( &game_state ,&turno_J1,&turno_oponente, &banca , &jugador_1 , op_lista , oponentes , cartas);

        if(game_over == 1)
        {
            printf("\n\n\n                  JUEGO TERMINADO\n-----------------------------------------\nDesea jugar de nuevo?\n1 - SI \n0 - NO\n->");
            scanf("%d", &otra_partida);

            while(otra_partida < 0 || otra_partida > 1)
            {
                printf("\nError. Desea jugar de nuevo?\n1 - SI \n0 - NO\n->");
                scanf("%d", &otra_partida);
            }

            if(otra_partida && jugador_1.presupuesto >= 10)
            {
                game_state = 0;
                reset_cartas(cartas);

                for( i = 0 ; i < oponentes ; i++)
                {
                    reset_jugadores(op_lista + i);
                }

                reset_jugadores(&jugador_1);
                reset_jugadores(&banca);

                turno_J1 = (rand() % (oponentes + 1));
                turno_oponente = 0;

                game_over = 0;
            }
            else if(jugador_1.presupuesto < 10 && otra_partida)
            {
                otra_partida = 0;
                game_over = 1;

                printf("\n\nUsted no dispone de fondos suficientes para continuar jugando en esta sesion.\n\n--------------------------------------\n PROGRAMA TERMINADO");
            }
        }
        else if(game_over < 0)
        {
            printf("\n\n---------------------------------------------\n\nERROR. PROGRAMA TERMINADO.\n\n ");

            otra_partida = 0;
            game_over = 1;
        }
    }
    //~loop principal del juego

	if (op_lista != NULL)
	{
		for ( i = 0; i < oponentes; i++)
		{
			for ( j = 0; j < 12; j++)
			{
				((op_lista + i)->cartas_jugador)[j] = NULL;
			}
		}

		free(op_lista);
	}
	
    return 0;
}