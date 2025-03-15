#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct node
{
    int key, data;
    struct node *prev, *next;
};

typedef struct node Node;

int isEmpty(Node *head) // functie basic de a verifica daca un nod sau un pointer in general e NULL
{
    if (head == NULL)
        return 1;
    return 0;
}

Node *createSimpleLinkedList() // funcite de creare a unei liste simplu inlantuite, intrebam user-ul cate noduri si ce valori sa puna
{
    int n, data;
    printf("CREARE LISTA SIMPLU INLANTUITA\nCate noduri doriti, domnisorule/domnisoara? (macar 3, maxim 10): ");
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
        if (current == NULL)
        {
            puts("Error in createSimpleLinkedList: cant allocate memory for node.");
            exit(1);
        }
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
            if (current->data == head->data) //cand gasim duplicata, schimbam nextul sa sara peste duplicata si eliberam memoria.
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
    if (v == NULL)
    {
        puts("Error in palindrom: cant allocate memory for array");
        exit(1);
    }
    while (head)
    {
        v = realloc(v, sizeof(int) * (long long unsigned int)(n + 1));
        if (v == NULL) // verificam daca s-a alocat memorie
        {
            puts("Error in palindrom: cant reallocate memory for array");
            exit(1);
        }
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

    free(v);

    if (n1 == n2)
    {
        puts("Este palindrom");
        return 1;
    }

    puts("Nu este palindrom");
    return 0;
}
////////////////////////////////////////////////////////////////////

// EX 3 (N=numar elemente)
////////////////////////////////////////////////////////////////////
/*
    daca N impar atunci elimin elementul de pe pozitia N/2+1
    daca N par atunci elimin elementele de pe pozitiile N/2 si N/2+1
*/
void createDoubleLinkedList(Node **head, Node **end) // functie de creare a unei liste dublu inlantuite, intrebam user-ul cate noduri sa creeze si ce valori sa puna in ele
{
    int n, data;
    printf("CREARE LISTA DUBLU INLANTUITA\nCate noduri doriti, domnisorule/domnisoara? (macar 3, maxim 10): ");
    do
    {
        scanf("%d", &n);
        if (n < 3 || n > 10)
            puts("Credeam ca avem o intelegere. Ti-am zis macar 3 si maxim 10...");
    } while (n < 3 || n > 10);

    Node *prev = NULL, *current;
    for (int i = 0; i < n; i++)
    {
        printf("Nodul %d, Introdu campul \"data\": ", i);
        scanf("%d", &data);
        current = (Node *)malloc(sizeof(Node));
        if (current == NULL)
        {
            puts("Error in createDoubleLinkedList: cant allocate memory for node.");
            exit(1);
        }
        current->data = data;
        current->key = i;
        current->next = NULL;
        current->prev = prev;
        if (prev)
            prev->next = current;

        if (i == 0)
            *head = current;
        if (i == n - 1)
            *end = current;
        prev = current;
    }
}
int deleteMiddle(Node *head)
{
    if (isEmpty(head))
    {
        puts("Error in deleteMiddle: head is null");
        return 0;
    }

    Node *temp = head;
    int n = 0, c = 1;
    while (temp)
    {
        n++;
        temp = temp->next;
    }

    if (n == 2)
    {
        puts("Bro, mai sunt doar 2 noduri, ce vrei sa mai stergi? uite ca nu te las!");
        return 0;
    }

    while(c < n/2)
    {
        c++;
        head=head->next;
    }

    // acum stergem nodul de pe pozitia N/2 sau ne deplasam in fata o data, in functie de paritatea lui n
    if (n % 2 == 0)
    {
        head->prev->next = head->next; // mutam "next"-ul nodului posterior nodului curent catre nodul anterior nodului curent
        head->next->prev = head->prev; // mutam "prev"-ul nodului anterior nodului curent catre nodul posterior nodului curent  (phrasing 9000)
        temp = head;
        head = head->next;
        free(temp);
    }
    else head=head->next;

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

int inverseRecursive(Node **head, Node *prev, Node *current)
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
        Node *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        return inverseRecursive(head, prev, current);
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

// macrofunctie de afisare a unui nod dupa ce optiune doresc (key sau data)
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
            Node *temp = (head); /* facem copie dupa nod */   \
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

int removeList(Node **head) // functie de a sterge o lista
{
    if (isEmpty(*head))
    {
        puts("Error in removeList: head is null");
        return 0;
    }

    Node *current = *head;
    while (current)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
    return 1;
}

void makeChoice(Node **head) // functie folosita in main ca sa alegi daca vrei sa pastrezi o lista nou creata sau sa o stergi si sa creezi alta, daca la un anume exercitiu ai nevoie
{
    int choice = -1;
    do
    {
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            removeList(head);
            break;
        case 1:
            break;
        default:
            puts("Te rog introdu 1 sau 0");
        }
    } while (choice != 0 && choice != 1);
}

// In main e doar un algoritm care sa faca programul interactiv pentru user... nu merge la infinit, in sensul ca nu poti rula acelasi exercitiu de mai multe ori din cauza modului de lucru cu liste, in comparatie cu simple array-uri.
int main()
{
    Node *head1 = NULL, *head2 = NULL, *head3 = NULL, *end3 = NULL;
    int n = -1, showLists = 0, chose1 = 0, chose2 = 0, chose3 = 0, chose4 = 0, chose5 = 0;
    do
    {
        printf("Te rog sa alegi unul dintre exercitiile de mai jos sau 0, daca vrei sa iesi:\n"
               "1. Realizati un program care sa stearga duplicatele dintr-o lista simplu inlantuita nesortata.\n"
               "2. Realizati un algoritm care sa verifice ca o lista simplu inlantuita este palindrom.\n"
               "3. Realizati o lista dublu inlantuita in care sa cautati elementul de la mijloc si sa il stergeti.\n"
               "4. Inversati o lista inlantuita folosind un algoritm recursiv si unul iterativ.\n"
               "5. Combinati doua liste inlantuite intr-una singura.\n");

        if (head1)
        {
            printf("Lista 1(simpla): ");
            display(head1, data);
        }
        if (head3)
        {
            printf("Lista 2(dubla): ");
            display(head3, data);
        }

        do
        {
            scanf("%d", &n);
            if (n != 0 && (n < 1 || n > 5))
                printf("%d nu este o varianta valida.\n", n);
        } while (n != 0 && (n < 1 || n > 5));

        switch (n)
        {
        case 1:
            if (!head1)
            {
                puts("Lista 1 nu exista, hai sa o cream.");
                head1 = createSimpleLinkedList();
            }
            printf("Lista initiala (valori): ");
            display(head1, data);
            deleteDuplicates(head1);
            printf("Lista dupa stergerea duplicatelor (valori): ");
            display(head1, data);
            printf("Doresti sa pastrezi lista pentru alte exercitii sau sa o stergi?\nPastreaza (1) sau Sterge (0)\n");
            makeChoice(&head1);
            break;
        case 2:
            if (!head1)
            {
                puts("Lista 1 nu exista, hai sa o cream.");
                head1 = createSimpleLinkedList();
            }
            printf("Lista initiala (valori): ");
            display(head1, data);
            palindrom(head1);
            printf("Doresti sa pastrezi lista pentru alte exercitii sau sa o stergi?\nPastreaza (1) / Sterge (0)\n");
            makeChoice(&head1);
            break;
        case 3:
            if (!head3)
            {
                puts("Lista 2 nu exista, hai sa o cream.");
                createDoubleLinkedList(&head3, &end3);
            }
            printf("Lista initiala (valori): ");
            display(head3, data);
            if (deleteMiddle(head3))
            {
                printf("Lista dupa stergere mijloc (valori): ");
                display(head3, data);
            }
            printf("Doresti sa pastrezi lista 2 pentru a repeta exercitiul asupra ei sau sa o stergi?\nPastreaza (1) / Sterge (0)\n");
            makeChoice(&head3);
            break;
        case 4:
            if (!head1)
            {
                puts("Lista 1 nu exista, hai sa o cream.");
                head1 = createSimpleLinkedList();
            }
            printf("Lista initiala (valori): ");
            display(head1, data);
            // inverseIterative(&head1);
            inverseRecursive(&head1, NULL, head1);
            printf("Lista dupa inversare (valori): "); display(head1,data);
            printf("Doresti sa pastrezi lista pentru alte exercitii sau sa o stergi?\nPastreaza (1) / Sterge (0)\n");
            makeChoice(&head1);
            break;
        case 5:
            if (!head1)
            {
                puts("Lista 1 nu exista, hai sa o cream.");
                head1 = createSimpleLinkedList();
            }
                puts("Hai sa cream lista pe care sa o adaugam la finalul listei 1.");
                head2 = createSimpleLinkedList();
            printf("Lista initiala (valori): ");
            display(head1, data);
            combineLists(head1, head2);
            printf("Lista dupa concatenare (valori): ");
            display(head1, data);
            printf("Doresti sa pastrezi lista 1 pentru alte exercitii sau sa o stergi?\nPastreaza (1) / Sterge (0)\n");
            makeChoice(&head1);
            break;
        default:
            break;
        }
    } while (n != 0);

    if (head1)
        removeList(&head1);
    if (head3)
        removeList(&head3);

    puts("Am inteles, ma voi inchide. Apasa orice tasta pentru a incheia...");

    getch();
}