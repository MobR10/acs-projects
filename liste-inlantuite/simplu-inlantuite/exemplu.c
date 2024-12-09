#include <stdio.h>
#include <stdlib.h>

struct node{
    int info;
    struct node *urm;
};
typedef struct node Node;

void check_node(Node *node)
{
    if(node==NULL)
        exit(1);
}

// void create_list(Node **first,int info)
// {
//     (*first)=(Node*)malloc(sizeof(Node));
//     check_node(*first);
//     (*first)->info=info;
//     (*first)->urm=NULL;
// }
// SAU
Node* create_list(Node*first,int info)
{
    first=(Node*)malloc(sizeof(Node));
    check_node(first);
    first->info=info;
    first->urm=NULL;
    return first;
}
void add_last(Node *first,int info)
{
        Node *q=(Node*)malloc(sizeof(Node));
        check_node(q);
        q->info=info;
        q->urm=NULL;
        Node *i;
        for(i=first;i->urm!=NULL;i=i->urm);
        i->urm=q;
}

void add_first(Node*first,int info)
{
    Node*q=(Node*)malloc(sizeof(Node));
    check_node(q);
    q->info=info;
    q->urm=first->urm;
    first->urm=q;
}

int add_position(Node*first,int info,int pos)
{
    if(pos==0)
    {
        
       first->info=info;
       return 1; 
    }
    else{
        Node*q=(Node*)malloc(sizeof(Node));
    check_node(q);
    q->info=info;
    int i=1,ok=0;
    for(Node*j=first->urm;j!=NULL;j=j->urm)
        {
            if(i==pos)
                {
                    j->info=info;
                }
        }
    }
    

}

int main()
{

    Node *first=NULL;
    first=create_list(first,1);

    for(int i=1;i<10;i++)
        add_last(first,i+1);
    for(Node *i=first;i!=NULL;i=i->urm)
        printf("%d ",i->info);

    printf("\n");
    add_first(first,44);
    for(Node *i=first;i!=NULL;i=i->urm)
        printf("%d ",i->info);

}