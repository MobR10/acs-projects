#include <stdio.h>
#define QUEUE_MAX 15
#include "ex1.h"
#include "ex2.h"
#include "ex3.h"
#include "ex4.h"

// Scuze ca e totul asa o ciorba, Chis :) (mai putin la ex1)
int main()
{
    //EX 1
    puts("Exercitiul 1 (cream o coada, facem operatii pe ea si mai afisam din cand in cand, la fel si pentru stiva):");
    Queue *front=createQueue(1);
    Queue *rear=getRear(front);
    enqueue(&front,&rear,2);
    enqueue(&front,&rear,3);
    enqueue(&front,&rear,4);
    enqueue(&front,&rear,5);

    displayQueue(front);

    dequeue(&front,&rear);
    dequeue(&front,&rear);
    
    displayQueue(front);

    Stack *top=createStack(1);
    push(&top,2);
    push(&top,3);
    push(&top,4);
    push(&top,5);
    displayStack(top);
    pop(&top);
    displayStack(top);
    
    freeQueue(&front,&rear);

    //EXERCITIUL 2
    puts("\nExercitiul 2:");
    static size_t leftHeight, rightHeight;
    static int *v;
    v = createStacks(&leftHeight, 2, &rightHeight, 3);

    pushElements(&v, &leftHeight, 10, &rightHeight, 11);
    pushElements(&v, &leftHeight, 15, &rightHeight, 32);

    popRight(&v, leftHeight, &rightHeight);
    popLeft(&v, &leftHeight, rightHeight);
    displayLeft(v, leftHeight);
    popLeft(&v, &leftHeight, rightHeight);
    displayLeft(v, leftHeight);
    popLeft(&v, &leftHeight, rightHeight);

    displayStacks(v, leftHeight, rightHeight);

    free(v);

    // EXERCITIUL 3
    puts("\nExercitiul 3:");
    Stack *front2 = createStack(1); // actioneaza drept capul cozii
    Stack *rear2 = createStack(2);  // cu rear creez o stiva intreaga drept "rear stack"
    // analogie: front e capul sarpelui si rear e coada lui, unde coada e formata din bucati legate intre ele sub forma unei stive.
    // capul nu e legat de coada, doar ma comport ca si cand ar fi
    adauga(&rear2, 3);
    adauga(&rear2, 4);
    adauga(&rear2, 5);

    puts("=====");
    afiseaza(front2, rear2, 1);
    puts("=====");

    scoate(&front2, &rear2);

    puts("=====");
    afiseaza(front2, rear2, 1);
    puts("=====");

    scoate(&front2, &rear2);
    scoate(&front2, &rear2);
    scoate(&front2, &rear2);

    adauga(&rear2,12);
    puts("=====");
    afiseaza(front2, rear2, 1);
    puts("=====");
    adauga(&rear2,134);
    puts("=====");
    afiseaza(front2, rear2, 1);

    freeStack(&front2);
    freeStack(&rear2);

    // EXERCITIUL 4: HOT POTATO
    puts("\nExercitiul 4: hot potato");
    srand(time(NULL));                    // this is to modify the values rand() generates at each run of the program
    int players = rand() % QUEUE_MAX + 1; // generate a random number between 1 and 15 inclusive
    if (players < 5)
        players = 5; // at least 5 players
    printf("Number of players: %d\n", players);
    Queue *front3 = NULL, *rear3 = NULL;
    for (int i = 1; i <= players; i++)
    {
        enqueue(&front3, &rear3, i);
    }

    int *eliminatedPlayers = (int *)malloc(sizeof(int) * players);
    int eliminatedLength = 0;

    puts("Initial queue of players");
    displayQueue(front3);

    int potato;
    do
    {
        potato = generatePotato(front3, players);
        printf("Potato: %d\n", potato);
        rotatePlayers(&front3, &rear3, potato, eliminatedPlayers, &eliminatedLength);
        if (front3)
            displayQueue(front3);
    } while (front3);

    printf("Eliminated players: ");
    for (int i = eliminatedLength - 1; i >= 0; i--)
    {
        printf("%d ", eliminatedPlayers[i]);
    }
}