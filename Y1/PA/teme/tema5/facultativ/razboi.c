#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define QUEUE_MAX 52
#include "./../ex1.h"

int pachetGol(int pachet[])
{
    for (int i = 2; i <= 14; i++)
        if (pachet[i] > 0)
            return 0;
    return 1;
}
void imparteCarti(Queue **front1, Queue **rear1, Queue **front2, Queue **rear2)
{
    int pachet[15] = {-1, -1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    int turn = 1;
    do
    {
        int carte;
        do
        {
            carte = rand() % 13 + 2; // genereaza un numar intre 2 si 14
        } while (pachet[carte] == 0);

        if (turn == 1)
        {
            turn = 2;
            enqueue(front1, rear1, carte);
            pachet[carte]--;
        }
        else
        {
            turn = 1;
            enqueue(front2, rear2, carte);
            pachet[carte]--;
        }
    } while (!pachetGol(pachet));
}

int main()
{
    srand(time(NULL));

    Queue *front1 = NULL, *rear1 = NULL, *front2 = NULL, *rear2 = NULL;

    imparteCarti(&front1, &rear1, &front2, &rear2);
    puts("Razboi!\nAm impartit cartile!");

    puts("Cartile jucatorului 1:");
    displayQueue(front1);
    puts("\nCartile jucatorului 2:");
    displayQueue(front2);

    int rounds = 0;
    do
    {
        int carteActuala, carteCastigata;
        rounds++;
        if (front1->data == front2->data)
        {
            dequeue(&front1, &rear2);
            dequeue(&front2, &rear2);
        }
        else if (front1->data > front2->data)
        {
            carteActuala=front1->data;
            carteCastigata = front2->data;
            dequeue(&front1,&rear1);
            dequeue(&front2, &rear2);
            enqueue(&front1,&rear1,carteActuala);
            enqueue(&front1, &rear1, carteCastigata);
        }
        else
        {
            carteActuala=front2->data;
            carteCastigata = front1->data;
            dequeue(&front2,&rear2);
            dequeue(&front1, &rear1);
            enqueue(&front2,&rear2,carteActuala);
            enqueue(&front2, &rear2, carteCastigata);
        }
    } while (!isEmpty(front1) && !isEmpty(front2));

    printf("Runde jucate: %d.\n", rounds);
    if (isEmpty(front1) && isEmpty(front2))
        printf("Egalitate!");
    else if (isEmpty(front1))
        printf("Castigator: jucatorul 1!");
    else
        printf("Castigator: jucatorul 2!");
}