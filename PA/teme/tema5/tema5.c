#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define QUEUE_MAX_INDEX 6
struct stack{
    int data;
};
typedef struct stack Stack;

struct queue{
    int data;
    size_t index;
    struct queue *next;
};
typedef struct queue Queue;

void isNull(void *ptr)
{
    if(ptr==NULL)
    {
        puts("Memory allocation failed!");
        exit(1);
    }
}

// Exercitiul 1
Queue *createQueue(int data)
{
    Queue *front=(Queue*)malloc(sizeof(Queue));
    isNull(front);
    front->index=0;
    front->data=data;
    front->next=NULL;
    return front;
}

/*
Queue
Make sure front pointer is initialized with NULL or it is declared as global or static variable 
*/
Queue *getRear(Queue *front)
{
    if(front==NULL)
    {
        puts("The queue is empty. There is no rear!");
    }
    else
    {
        Queue *i;
        for(i=front;i->next!=NULL;i=i->next);
        return i;
    }
}

void displayQueue(Queue *front)
{
    for(Queue *i=front;i!=NULL;i=i->next)
    {
        if(i->next==NULL)
            printf("(Index: %zu, Data: %d)",i->index,i->data);
        else
            printf("(Index: %zu, Data: %d) -> ",i->index,i->data);
    }
    puts("");
}

void resetQueueIndex(Queue *front)
{
    size_t index=0;
    for(Queue *i=front;i!=NULL;i=i->next)
        i->index=index++;
}

int push();

int pop();

int enqueue(Queue **rear,int data)
{
    Queue *new=(Queue*)malloc(sizeof(Queue));
    isNull(new);
    new->next=NULL;
    new->data=data;
    new->index=(*rear)->index+1;
    (*rear)->next=new;
    *rear=new;
}
int dequeue(Queue **front)
{
    Queue *i=(*front);
    (*front)=(*front)->next;
    free(i);
    resetQueueIndex(*front);
}

int isEmpty();

int isFull();

Queue* peek(Queue *rear){

}


int main()
{
    Queue *front=createQueue(1);
    Queue *rear=getRear(front);  
    enqueue(&rear,5);
    enqueue(&rear,10);
    enqueue(&rear,21);
    displayQueue(front); 
    printf("%d",rear->data);
    dequeue(&front);
    displayQueue(front);

}