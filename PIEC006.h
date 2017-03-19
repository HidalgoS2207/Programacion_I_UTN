//bilioteca validacion de input de usuario

#include <stdio.h>
#include <stdlib.h>

int val_only_words(char * user_str_p)
{
    int counter = 0;

    while(*(user_str + counter) != '\0')
    {
        counter++;
    }

    if(counter == 0)
    {
        return 0;
    }

    for(int i = 0; i < counter - 1; i++)
    {
        if(*(user_str + i) != 0x0020)
        {
            if((*(user_str + i) > 64 &&  *(user_str + i) < 91) || (*(user_str + i) > 96 &&  *(user_str + i) < 123))
            {
                ;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

int val_only_numbers(char * user_str)
{
    int counter = 0;
    int numeros = 0;

    while(*(user_str + counter) != '\0')
    {
        counter++;
    }

    if(counter == 0)
    {
        return 0;
    }

    for(int i = 0; i < counter - 1; i++)
    {
        if(*(user_str + i) != 0x0020)
        {
            if((*(user_str + i) > 47 &&  *(user_str + i) < 58))
            {
                ;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

int val_only_numbers_and_words(char * user_str)
{
    int counter = 0;

    int letras = 0;
    int numeros = 0;
    int espacios = 0;

    while(*(user_str + counter) != '\0')
    {
        counter++;
    }

    if(counter == 0)
    {
        return 0;
    }

    for(int i = 0; i < counter - 1; i++)
    {
        if(*(user_str + i) != 0x0020)
        {
            if((*(user_str + i) > 64 &&  *(user_str + i) < 91) || (*(user_str + i) > 96 &&  *(user_str + i) < 123))
            {
                letras++;
            }
            else if((*(user_str + i) > 47 &&  *(user_str + i) < 58))
            {
                numeros++;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    if(letras != 0 && numeros != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int detect_content(char * user_str)
{
    int counter = 0;

    int letras = 0;
    int numeros = 0;
    int espacios = 0;

    while(*(user_str + counter) != '\0')
    {
        counter++;
    }

    if(counter == 0)
    {
        return -1;
    }

    for(int i = 0; i < counter - 1; i++)
    {
        if(*(user_str + i) != 0x0020)
        {
            if((*(user_str + i) > 64 &&  *(user_str + i) < 91) || (*(user_str + i) > 96 &&  *(user_str + i) < 123))
            {
                letras++;
            }
            else if((*(user_str + i) > 47 &&  *(user_str + i) < 58))
            {
                numeros++;
            }
            else
            {
                return -2;
            }
        }
        else
        {
            espacios++;
        }
    }

    if(!espacios)
    {
        if(!letras)
        {
            return 0;
        }
        else if(!numeros)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        if(!letras && !numeros)
        {
            return -2;
        }
        else
        {
            if(!letras)
            {
                return 0;
            }
            else if(!numeros)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
    }

}



