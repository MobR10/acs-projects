#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma once

#define QUEUE 10
#ifndef QUEUE_MAX
#define QUEUE_MAX 6
#endif
#define STACK 29
#define STACK_MAX 6

struct stack
{
    int data;
    size_t index;
    struct stack *next;
    struct stack *prev;
};
typedef struct stack Stack;

struct queue
{
    int data;
    size_t index;
    struct queue *next;
};
typedef struct queue Queue;

#define overflow(type)                                                                        \
    do                                                                                        \
    {                                                                                         \
        if ((type) == QUEUE)                                                                  \
            printf("The queue is full. You can have a maximum of %u elements.\n", QUEUE_MAX); \
        else if ((type) == STACK)                                                             \
            printf("The stack is full. You can have a maximum of %u elements.\n", STACK_MAX); \
    } while (0)

#define wrongNode(type)                                                                                                   \
    do                                                                                                                    \
    {                                                                                                                     \
        if ((type) == QUEUE)                                                                                              \
            puts("Ma boi, you really tried introducing the wrong node instead of actual FRONT or REAR? Come on bruh..."); \
        else if ((type) == STACK)                                                                                         \
            puts("Ma boi, you really tried introducing the wrong node instead of actual TOP? Come on bruh...");           \
    } while (0)

/*
Works for both QUEUE and STACK, but make sure you send a properly initialized pointer with anticipated behaviour.
Don't declare the pointer locally without initialization of NULL, as it will result in unexpected behaviour.
*/
int isEmpty(void *ptr)
{
    if (ptr == NULL)
        return 1;
    return 0;
}

/*
Works for both QUEUE and STACK, but make sure you send a properly initialized pointer with anticipated behaviour.
Don't declare the pointer locally without initialization of NULL, as it will result in unexpected behaviour.
You will get segmentation fault otherwise.
*/
int isFull(void *ptr, int type)
{
    if (type == QUEUE)
    {
        if (((Queue *)ptr)->next != NULL)
        {
            wrongNode(QUEUE);
            return -1;
        }
        if (((Queue *)ptr)->index + 1 < QUEUE_MAX)
            return 0;
        else
        {
            return 1;
        }
    }
    else if (type == STACK)
    {
        if (((Stack *)ptr)->next != NULL)
        {
            wrongNode(STACK);
            return -1;
        }
        if (((Stack *)ptr)->index + 1 < QUEUE_MAX)
            return 0;
        else
        {
            return 1;
        }
    }
    else
    {
        puts("Either enter QUEUE or STACK as type. Otherwise, it ain't gonna work, fam.");
        return -1;
    }
}

void checkAllocation(void *ptr)
{
    if (ptr == NULL)
    {
        puts("Memory allocation failed!");
        exit(1);
    }
}

// QUEUE FUNCTIONS

/*
Queue
Display all the nodes in queue
Make sure front is either defined, initialized with NULL or undefined, but declared as static or global.
*/
void displayQueue(Queue *front)
{
    if (isEmpty(front) == 1)
    {
        puts("The queue is empty. There is nothing to display.");
    }
    else
    {
        puts("Displaying queue:");
        for (Queue *i = front; i != NULL; i = i->next)
        {
            if (i->next == NULL)
                printf("(Index: %zu, Data: %d)", i->index, i->data);
            else
                printf("(Index: %zu, Data: %d) -> ", i->index, i->data);
        }
        puts("");
    }
}

void resetQueueIndex(Queue *front)
{
    size_t index = 0;
    for (Queue *i = front; i != NULL; i = i->next)
        i->index = index++;
}

/*
Queue
Frees all the nodes from memory
Make sure both front and rear are either defined, initialized with NULL or undefined, but declared as static or global.
*/
void freeQueue(Queue **front, Queue **rear)
{
    if (isEmpty(*front) == 1)
    {
        puts("Can't free an empty list.");
    }
    else if ((*front)->index != 0 || (*rear)->next != NULL)
    {
        wrongNode(QUEUE);
    }
    else
    {
        Queue *temp, *i = (*front);
        while (i != NULL)
        {
            temp = i;
            i = i->next;
            free(temp);
        }
        *front = NULL;
        *rear = NULL;
    }
}

/*
Queue
Return pointer to front
*/
Queue *createQueue(int data)
{
    Queue *front = (Queue *)malloc(sizeof(Queue));
    checkAllocation(front);
    front->index = 0;
    front->data = data;
    front->next = NULL;
    //printf("Created queue. Front is (Index: 0, Data: %d).\n", front->data);
    return front;
}

/*
Queue
Make sure front is either defined, initialized with NULL or undefined, but declared as static or global.
*/
Queue *getRear(Queue *front)
{
    if (isEmpty(front) == 1)
    {
        puts("The queue is empty. There is no rear!");
        return NULL;
    }
    else
    {
        Queue *i;
        for (i = front; i->next != NULL; i = i->next)
            ;
        return i;
    }
}

/*
Queue
Adds one element at the end of the queue
Make sure both front and rear are either defined, initialized with NULL or undefined, but declared as static or global.
*/
void enqueue(Queue **front, Queue **rear, int data)
{
    if (isEmpty(*front) == 1)
    {
        *front = createQueue(data);
        *rear = getRear(*front);
    }
    else
    {
        if (isEmpty(*rear) == 1)
            *rear = getRear(*front);
        if (isFull(*rear, QUEUE) == 1)
            puts("The queue is full. Can't enqueue.");
        else
        {
            Queue *new = (Queue *)malloc(sizeof(Queue));
            checkAllocation(new);
            new->next = NULL;
            new->data = data;
            new->index = (*rear)->index + 1;
            (*rear)->next = new;
            *rear = new;
            //printf("Enqueued (Index: %zu, Data: %d) to the queue.\n", new->index, new->data);
        }
    }
}

/*
Queue
Removes the first element in front
Make sure both front and rear are either defined, initialized with NULL or undefined, but declared as static or global.
*/
void dequeue(Queue **front, Queue **rear)
{
    if (isEmpty(*front) == 1)
    {
        puts("The queue is already empty. There is nothing to dequeue!");
    }
    else
    {
        //printf("Removed (Index: %zu, Data: %d) from the queue.\n", (*front)->index, (*front)->data);
        Queue *i = (*front);
        (*front) = (*front)->next;
        free(i);
        if (!isEmpty(*front))
            resetQueueIndex(*front);
        else
            *rear = NULL;
    }
}

/*
Queue
Visualize the specified element's attributes from the queue
*/
void queuePeek(Queue *node)
{
    if (node == NULL)
    {
        puts("This node is NULL. Can't peek.");
    }
    else
        printf("Peeking element with index = %zu and data = %d from the queue.\n", node->index, node->data);
}

// STACK FUNCTIONS

void displayStack(Stack *top)
{
    if (isEmpty(top))
    {
        puts("The stack is empty, there is nothing to display.");
    }
    else
    {
        puts("Displaying stack:");
        for (Stack *i = top; i != NULL; i = i->prev)
        {
            printf("(Index: %zu, Data: %d)\n", i->index, i->data);
        }
    }
}

/*
Stack
Frees all the nodes from memory
Make sure top is either defined, initialized with NULL or undefined, but declared as static or global.
*/
void freeStack(Stack **top)
{
    if (isEmpty(*top) == 1)
    {
        puts("The stack is empty. There is nothing to free.");
    }
    else if ((*top)->next != NULL)
    {
        wrongNode(STACK);
    }
    else
    {
        Stack *temp, *i = (*top);
        while (i != NULL)
        {
            temp = i;
            i = i->prev;
            free(temp);
        }
        *top = NULL;
        puts("Deleted stack.");
    }
}

/*
Stack
Returns a pointer to the freshly created stack
*/
Stack *createStack(int data)
{
    Stack *top = (Stack *)malloc(sizeof(Stack));
    checkAllocation(top);
    top->index = 0;
    top->data = data;
    top->next = NULL;
    top->prev = NULL;
    printf("Created stack. Top is (Index: %zu, Data: %d).\n", top->index, top->data);
    return top;
}

/*
Stack
Add an element on top of the stack
Make sure top is either defined, initialized with NULL or undefined, but declared as static or global.
*/
void push(Stack **top, int data)
{
    if (isEmpty(*top) == 1)
    {
        *top = createStack(data);
    }
    else if (isFull(*top, STACK))
    {
        overflow(STACK);
    }
    else
    {
        Stack *new = (Stack *)malloc(sizeof(Stack));
        checkAllocation(new);
        new->index = (*top)->index + 1;
        new->next = NULL;
        new->prev = (*top);
        new->data = data;
        (*top)->next = new;
        *top = new;
        printf("Added (Index: %zu, Data: %d) at the top of the stack.\n", new->index, new->data);
    }
}

/*
Stack
Removes the element on top of the stack
Make sure top is either defined, initialized with NULL or undefined, but declared as static or global.
*/
void pop(Stack **top)
{
    if (isEmpty(*top) == 1)
    {
        puts("The stack is empty. There is nothing to pop out.");
    }
    else
    {
        printf("Removed (Index: %zu, Data: %d) from the top of the stack.\n", (*top)->index, (*top)->data);
        Stack *temp = (*top);
        (*top) = (*top)->prev;
        if (!isEmpty(*top))
            (*top)->next = NULL;
        free(temp);
    }
}

/*
Stack
Visualize the element on top of the stack
Make sure top is either defined, initialized with NULL or undefined, but declared as static or global.
*/
void stackPeek(Stack *top)
{
    if (isEmpty(top) == 1)
    {
        puts("Stack is empty. Can't peek.");
    }
    else if (top->next != NULL)
    {
        wrongNode(STACK);
    }
    else
    {
        printf("Peeking top of the stack with index = %zu and data = %d.\n", top->index, top->data);
    }
}