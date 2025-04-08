#include <stdio.h>
#include <time.h>
#define QUEUE_MAX 15
#include "ex1.h"

int generatePotato(Queue *front, int players)
{
    int potato;
    if (isEmpty(front))
        return 0;
    else
    {
        do
        {
            potato = rand() % players + 1; // generate any number between 1 and the number of players
            for (Queue *i = front; i != NULL; i = i->next)
                if (i->data == potato)
                {
                    return potato;
                }
        } while (1);
    }
}

void rotatePlayers(Queue **front, Queue **rear, int potato, int *eliminatedPlayers, int *eliminatedLength)
{
    if ((*front)->next != NULL)
    {
        Queue *temp = (*front);
        while (temp->data != potato)
        {
            int data = temp->data;
            temp = temp->next;
            dequeue(front, rear);
            enqueue(front, rear, data);
        }
    }
    eliminatedPlayers[(*eliminatedLength)] = potato;
    (*eliminatedLength)++;
    dequeue(front, rear);
}