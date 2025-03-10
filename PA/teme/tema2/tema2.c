#include <stdio.h>
#include <stdlib.h>

typedef struct{

    int key,value;

    Node *next;
}Node;

int isEmpty(Node *head)
{
    if(head == NULL)
        return 1;
    return 0;
}

// void inverse(Node *current,Node *prev,Node *next,Node**head)
// {
//     if(current==NULL)
//         current=*head;
//     else
//     {
        
//     }
// }

// {
//     if()
// }

void insertLast(Node **head,int value)
{
    if(isEmpty(*head))
    {
        *head=(Node*)malloc(sizeof(Node));
        (*head)->key=0;
        (*head)->next=NULL;
        (*head)->value=value;
    }
    else
    {
        Node *current=*head;
        while(current->next!=NULL)
        {
            current=current->next;
        }
        Node *node=(Node*)malloc(sizeof(Node));
        current->next=node;
        node->next=NULL;
        node->value=value;
        node->key=current->key+1;
    }
}

void display(Node *head)
{
    if(!isEmpty(head))
    {
        printf("v[ ");
    while(head!=NULL)
    {
        printf("%d , ",head->value);
        head=head->next;
    }
    printf("]\n");
    }
    else
    {
        puts("List is empty!");
    }
}

int main()
{


}