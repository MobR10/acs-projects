#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key, data;
    struct node *prev, *next;
};

typedef struct node Node;

int isEmpty(Node *head)
{
    if (head == NULL)
        return 1;
    return 0;
}

Node *createSimpleLinkedList()
{
    int n, data;
    printf("CREARE LISTA SIMPLU INLANTUITA\nCate noduri doriti, domnisorule/domnisoara? (macar 3, maxim 10)");
    do
    {
        scanf("%d", &n);
        if (n < 3 || n > 10)
            puts("Credeam ca avem o intelegere. Ti-am zis macar 3 si maxim 10...");
    } while (n < 3 || n > 10);

    Node *prev = NULL, *head, *current;
    for (int i = 0; i < n; i++)
    {
        printf("Nodul %d, Introdu campul \"data\": ", i);
        scanf("%d", &data);
        current = (Node *)malloc(sizeof(Node));
        current->data = data;
        current->key = i;
        current->next = NULL;
        if (prev)
        {
            prev->next = current;
        }

        else
        {
            head = current;
        }
        prev = current;
    }
    return head;
}
// EX 1
////////////////////////////////////////////////////////////////////
int deleteDuplicates(Node *head)
{

    if (isEmpty(head))
    {
        puts("Error in deleteDuplicates: HEAD is NULL");
        return 0;
    }
    Node *prev, *current = head, *temp;
    while (head)
    {

        current = head->next;
        prev = head;
        while (current)
        {
            if (current->data == head->data)
            {
                prev->next = current->next;
                temp = current;
                current = current->next;
                free(temp);
            }
            else
            {
                current = current->next;
                prev = prev->next;
            }
        }
        head = head->next;
    }
    return 1;
}
////////////////////////////////////////////////////////////////////

// EX 2
////////////////////////////////////////////////////////////////////
int palindrom(Node *head)
{
    if (isEmpty(head))
    {
        puts("ERROR in palindrom: head is null");
        return 0;
    }
    int n = 0, *v = (int *)malloc(1);
    while (head)
    {
        v=realloc(v, sizeof(int) * (long long unsigned int)(n + 1));
        v[n] = head->data;
        n++;
        head = head->next;
    }
    int n1 = 0, n2 = 0, p = 1;
    for (int i = 0; i < n; i++)
    {
        n1 = n1 * 10 + v[i];
        n2 = v[i] * p + n2;
        p *= 10;
    }

    if (n1 == n2)
    {
        puts("Este palindrom");
        return 1;
    }

    puts("Nu este palindrom");
    return 0;
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
#define display(head, option)                                 \
    do                                                        \
    {                                                         \
        if (isEmpty(head))                                    \
        {                                                     \
            printf("ERROR in macro display: head is null\n"); \
        }                                                     \
        else                                                  \
        {                                                     \
            printf("v[ ");                                    \
            Node *temp = (head); /* Create a copy of head */  \
            while (temp)                                      \
            {                                                 \
                printf("%d", temp->option);                   \
                temp = temp->next;                            \
                if (temp)                                     \
                    printf(", ");                             \
            }                                                 \
            printf(" ]\n");                                   \
        }                                                     \
    } while (0)
////////////////////////////////////////////////////////////////////

// EX 3 (N=numar elemente)
////////////////////////////////////////////////////////////////////
/*
    daca N impar atunci elimin elementul de pe pozitia N/2+1
    daca N par atunci elimin elementele de pe pozitiile N/2 si N/2+1
*/
Node *createDoubleLinkedList()
{
    int n, data;
    printf("CREARE LISTA DUBLU INLANTUITA\nCate noduri doriti, domnisorule/domnisoara? (macar 3, maxim 10)");
    do
    {
        scanf("%d", &n);
        if (n < 3 || n > 10)
            puts("Credeam ca avem o intelegere. Ti-am zis macar 3 si maxim 10...");
    } while (n < 3 || n > 10);

    Node *head, *prev = NULL, *current;
    for (int i = 0; i < n; i++)
    {
        printf("Nodul %d, Introdu campul \"data\": ", i);
        scanf("%d", &data);
        current = (Node *)malloc(sizeof(Node));
        current->data = data;
        current->key = i;
        current->next = NULL;
        current->prev = prev;
        if (prev)
            prev->next = current;

        if (i == 0)
            head = current;

        prev = current;
    }
    return head;
}
int deleteMiddle(Node *head)
{
    if (isEmpty(head))
    {
        puts("Error in deleteMiddle: head is null");
        return 0;
    }

    Node *temp = head;
    int n = 0, c = 0;
    while (temp)
    {
        n++;
        temp = temp->next;
    }

    if(n==2)
    {
        puts("Bro, mai sunt doar 2 noduri, ce vrei sa mai stergi? uite ca nu te las!");
        return 0;
    }

    while (c != n / 2)
    {
        c++;
        head = head->next;
    }

    // acum stergem nodul de pe pozitia N/2
    if (n % 2 == 0)
    {
        head->prev->next = head->next; // mutam "next"-ul nodului posterior nodului curent catre nodul anterior nodului curent
        head->next->prev = head->prev; // mutam "prev"-ul nodului anterior nodului curent catre nodul posterior nodului curent  (phrasing 9000)
        temp = head;
        head = head->next;
        free(temp);
    }

    // acum stergem nodul de pe pozitia N/2+1
    head->prev->next = head->next;
    head->next->prev = head->prev;
    temp = head;
    head = head->next;
    free(temp);

    return 1;
}
////////////////////////////////////////////////////////////////////

// EX 4
////////////////////////////////////////////////////////////////////
int inverseIterative(Node **head)
{
    if (isEmpty(*head))
    {
        puts("Error in inverseIterative: head is null");
        return 0;
    }
    Node *prev = NULL, *current = *head, *next;

    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
    return 1;
}

int inverseRecursive(Node **head, Node *prev, Node *current, Node *next)
{
    if (isEmpty(*head))
    {
        puts("Error in inverseRecursive: head is null");
        return 0;
    }

    if (!current)
    {
        *head = prev;
        return 1;
    }
    else
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        return inverseRecursive(head, prev, current, next);
    }
}
////////////////////////////////////////////////////////////////////
// EX 5
int combineLists(Node *head1, Node *head2)
{
    if (isEmpty(head1))
    {
        puts("Error in combineLists: head1 is null");
        return 0;
    }
    if (isEmpty(head2))
    {
        puts("Error in combineLists: head2 is null");
        return 0;
    }

    while (head1->next)
        head1 = head1->next;

    int key = head1->key;
    head1->next = head2;
    head1 = head1->next;
    
    while (head1) // aici setam noile chei (pentru ca cheile sunt unice, intr o lista nu trebuie sa se regaseasca aceeasi cheie de mai multe ori)
    {
        key++;
        head1->key = key;
        head1 = head1->next;
    }
    return 1;
}
////////////////////////////////////////////////////////////////////

// you can ignore this
////////////////////////////////////////////////////////////////////
// void display(Node *head)
// {
//     if(!isEmpty(head))
//     {
//         printf("v[ ");
//     while(head)
//     {
//         printf("%d ",head->key);
//         head=head->next;
//         if(head) printf(", ");
//     }
//     printf("]\n");
//     }
//     else
//     {
//         puts("List is empty!");
//     }
// }
////////////////////////////////////////////////////////////////////

int main()
{
    Node *head1 = NULL, *head2 = NULL, *head3 = NULL;
    int n=-1, repeat = 1;

    do
    {
        if(n!=-1)
            printf("Introdu din nou un numar: ");
        do
        {
            if (repeat)
            {
                printf("Te rog sa alegi unul dintre exercitiile de mai jos sau 0, daca vrei sa iesi:\n"
                       "1. Realizati un program care sa stearga duplicatele dintr-o lista simplu inlantuita nesortata.\n"
                       "2. Realizati un algoritm care sa verifice ca o lista simplu inlantuita este palindrom.\n"
                       "3. Realizati o lista dublu inlantuita in care sa cautati elementul de la mijloc si sa il stergeti.\n"
                       "4. Inversati o lista inlantuita folosind un algoritm recursiv si unul iterativ.\n"
                       "5. Combinati doua liste inlantuite intr-una singura.\n");
                repeat = 0;
            }

            scanf("%d", &n);
            switch (n)
            {
            case 1:
                puts("Rulare exercitiu 1:");
                if (!head1)
                {
                    puts("Mai intai, hai sa cream o lista simplu inlantuita");
                    head1 = createSimpleLinkedList();
                }
                printf("Lista initiala: (numar data): ");
                display(head1, data);
                deleteDuplicates(head1);
                printf("Lista dupa stergere duplicate: ");
                display(head1, data);
                puts("");
                break;
            case 2:
                puts("Rulare exercitiu 2:");
                if (!head1)
                {
                    puts("Mai intai, hai sa cream o lista simplu inlantuita");
                    head1 = createSimpleLinkedList();
                }
                printf("Lista initiala: (afisare dupa campul \"data\") ");
                display(head1, data);
                palindrom(head1);
                puts("");
                break;
            case 3:
                puts("Rulare exercitiu  3:");
                if (!head3)
                {
                    puts("Mai intai hai sa cream o lista dublu inlantuita");
                    head3 = createDoubleLinkedList();
                }
                printf("Lista initiala (dupa data): ");
                display(head3, data);
                deleteMiddle(head3);
                printf("Lista dupa stergerea mijlocului (dupa data): ");
                display(head3, data);
                puts("");
                break;
            case 4:
                if (!head1)
                {
                    puts("Mai intai, hai sa cream o lista simplu inlantuita");
                    head1 = createSimpleLinkedList();
                }
                puts("Rulare exercitiu 4:");
                printf("Lista initiala: ");
                display(head1, data);
                puts("");
                inverseIterative(&head1);
                //inverseRecursive(&head1, NULL, head1, head1->next); 
                printf("Lista dupa inversare: ");
                display(head1, data);
                puts("");
                break;
            case 5:
                if (!head1)
                {
                    puts("Mai intai, hai sa cream prima lista simplu inlantuita");
                    head1 = createSimpleLinkedList();
                }
                if (!head2)
                {
                    puts("Hai sa cream a doua lista simplu inlantuita");
                    head2 = createSimpleLinkedList();
                }
                puts("Rulare exercitiu  5:");
                printf("Lista 1: ");
                display(head1, data);
                puts("");
                printf("Lista 2: ");
                display(head2, data);
                puts("");
                combineLists(head1, head2);
                printf("Lista combinata: ");
                display(head1, data);
                break;
            case 0:
                break;
            default:
                puts("Introdu un numar natural minim 1, maxim 5 sau 0 pentru a iesi");
            }
        } while (n != 0 && (n < 1 || n > 5));
    } while (n != 0);
}