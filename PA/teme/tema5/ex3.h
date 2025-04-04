#include <stdio.h>
#include <stdlib.h>
#include "ex1.h"

/*
Asta e varianta care mi-a venit in minte. tot algoritmul de "scoatere" e o ciorba, dar functioneaza.
Am folosit 2 stive, chiar daca prima are un singur element(o folosesc pe post de "front"), iar a 2-a pe post de "rear stack".
Adica e o coada a carui prim element este o stiva cu un element, si restul cozii este o stiva intreaga.
Afisarea o fac prin recursivitate, pentru ca pornesc de la rear catre baza stivei "rear" si afisez in sens invers ca sa dea impresia falsa ca e o coada.
Front-ul pur si simplu il afisez primul, nu e nimic recursiv acolo. Doar pentru "rear stack" e recursiv.
*/

void afiseaza(Stack *front, Stack *rear, int showFront)
{
    if (isEmpty(front))
    {
        puts("Coada e goala sau capatul nu exista.");
    }
    else
    {
        if (showFront == 1)
        {
            if (rear==NULL)
                printf("(Index: 0, Data: %d)", front->data);
            else
            {
                printf("(Index: 0, Data: %d) -> ", front->data);
                afiseaza(front, rear, 0);
            }
        }
        else
        {
            if (rear->prev == NULL && rear->next != NULL)
                printf("(Index: %zu, Data: %d) -> ", rear->index + 1, rear->data);
            else if (rear->prev == NULL && rear->next == NULL)
                printf("(Index: %zu, Data: %d)\n", rear->index + 1, rear->data);
            else if (rear->next == NULL)
            {
                afiseaza(front, rear->prev, 0);
                printf("(Index: %zu, Data: %d)\n", rear->index + 1, rear->data);
            }
            else
            {
                afiseaza(front, rear->prev, 0);
                printf("(Index: %zu, Data: %d) -> ", rear->index + 1, rear->data);
            }
        }
    }
}

void adauga(Stack **rear, int data)
{
    push(rear, data);
}

void scoate(Stack **front, Stack **rear)
{
    if (isEmpty(*front) == 1)
    {
        puts("Coada e goala. Nu am ce scoate.");
    }
    else if (isEmpty(*rear) == 1)
    {
        Stack *temp = (*front);
        *front = NULL;
        free(temp);
    }
    else
    {
        pop(front);
        if ((*rear)->prev == NULL) // in toata coada sunt doar 2 elemente
        {
            *front = createStack((*rear)->data);
            free(*rear);
            *rear = NULL;
        }
        else
        {
            Stack *i;
            for (i = (*rear); i->prev != NULL; i = i->prev)
            {
                i->index--;
            }
            *front = createStack(i->data);
            if (!isEmpty(i->next))
                i->next->prev = NULL;
            free(i);
        }
    }
}