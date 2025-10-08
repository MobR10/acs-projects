#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct binaryTree
{
    int data;
    struct binaryTree *left;
    struct binaryTree *right;
};
typedef struct binaryTree bTree;

void freeTree(bTree *root)
{
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void display(bTree *root,bTree *current) // parcurgere post-order
{
    if(current)
    {
        display(root,current->left);
        display(root,current->right);
        if(current==root)
        printf("%d\n",current->data);
        else printf("%d, ",current->data);
    }
}

void insert(bTree **root, int data)
{
    bTree *temp = (bTree *)malloc(sizeof(bTree));
    bTree *current, *parent;

    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    if ((*root) == NULL)
    {
        *root = temp;
    }
    else
    {
        current = *root;
        parent = NULL;

        while (1)
        {
            parent = current;

            if (data < parent->data)
            {
                current = current->left;
                if (current == NULL)
                {
                    parent->left = temp;
                    return;
                }
            }
            else
            {
                current = current->right;
                if (current == NULL)
                {
                    parent->right = temp;
                    return;
                }
            }
        }
    }
}
bTree *getParent(bTree *root, int data)
{
    if (root->data == data)
        return NULL;
    bTree *current = root, *parent;
    while (current)
    {
        parent = current;
        if (root->data > data)
        {
            current = current->left;
            if (current != NULL && current->data == data)
                return parent;
        }
        else
        {
            current = current->right;
            if (current != NULL && current->data == data)
                return parent;
        }
    }
    return NULL;
}
int getDepth(bTree *root, int data, int depth) // parcurgere pre-order
{
    if (root == NULL)
        return -1;

    if (root->data == data)
        return depth;

    int leftDepth = getDepth(root->left, data, depth + 1);
    if (leftDepth != -1)
        return leftDepth;

    return getDepth(root->right, data, depth + 1);
}
bTree *getNode(bTree *root, int data)
{
    if (root->data == data)
        return root;
    bTree *current = root;
    while (current)
    {
        if (root->data > data)
        {
            current = current->left;
            if (current != NULL && current->data == data)
                return current;
        }
        else
        {
            current = current->right;
            if (current != NULL && current->data == data)
                return current;
        }
    }
    return NULL;
}
int getHeight(bTree *root) // parcurgere pre-order
{
    if (root == NULL)
        return -1;

    int height1 = getHeight(root->left);
    int height2 = getHeight(root->right);

    return (height1 > height2 ? height1 : height2) + 1;
}

// EX1
int isEven(bTree *root)
{
    if (root == NULL)
        return 1;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if (abs(leftHeight - rightHeight) > 1)
        return 0;
    return isEven(root->left) && isEven(root->right);
}

// EX2
int isBinarySearchTree(bTree *root, bTree *minNode, bTree *maxNode) // parcurgere in-order
{
    if (root == NULL)
        return 1;

    if ((minNode != NULL && root->data < minNode->data) || (maxNode != NULL && root->data > maxNode->data))
        return 0;

    return isBinarySearchTree(root->left, minNode, root) && isBinarySearchTree(root->right, root, maxNode);
}

// EX3
bTree* closestRelative(bTree *root, int node1, int node2) // parcurgere post-order
{
    // Dacă arborele este gol, nu există strămoș comun
    if (root == NULL)
        return NULL;

    // Dacă unul dintre noduri este chiar nodul curent, acesta este strămoșul comun
    if (root->data == node1 || root->data == node2)
        return root;

    // Caută în subarborele stâng și drept
    bTree *leftLCA = closestRelative(root->left, node1, node2);
    bTree *rightLCA = closestRelative(root->right, node1, node2);

    // Dacă nodurile sunt găsite în subarbori diferiți, nodul curent este strămoșul comun
    if (leftLCA != NULL && rightLCA != NULL)
        return root;

    // Dacă ambele noduri sunt în același subarbore, întoarce acel subarbore
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

// EX4
void addToString(char **dest, int data)
{
    // Convert the integer to a string
    char buffer[20]; // Temporary buffer to hold the integer as a string
    sprintf(buffer, "%d", data); // this is interesting

    // Calculate the new size for the destination string
    size_t destLen = *dest ? strlen(*dest) : 0; // if(!(*dest)) destLen= strlen(*dest) else destLen=0;
    size_t bufferLen = strlen(buffer);

    // Reallocate memory to fit the new string
    *dest = (char *)realloc(*dest, destLen + bufferLen + 2); // +2 for separator and null terminator
    if (*dest == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Append the new string
    if (destLen > 0)
        strcat(*dest, ","); // Add a separator (comma)
    strcat(*dest, buffer);
}
// Convert the binary tree into a string
void btreeToString(bTree *root, char **dest) // parcurgere pre-order
{
    if (root == NULL)
        return;

    addToString(dest, root->data);

    btreeToString(root->left, dest);
    btreeToString(root->right, dest);
}

//Convert a string into a binary tree
bTree* stringToBtree(char *string)
{
    if(string == NULL)
        return NULL;
    bTree *root=NULL;
    char *stringCopy=strdup(string),*p;
    p=strtok(stringCopy," ,");
    while(p)
    {
        insert(&root,atoi(p));
        p=strtok(NULL," ,");
    }
    return root;
}

// EX5

int areCousins(bTree *root, int data1, int data2) // initial function to check just 2 nodes
{
    if (data1 == data2)
        return 0;
    if (getDepth(root, data1, 0) != getDepth(root, data2, 0))
        return 0;
    bTree *parent1 = getParent(root, data1);
    bTree *parent2 = getParent(root, data2);
    if (parent1 == parent2)
        return 0;
    return 1;
}

int hasCousins(bTree *root) // i couldn't have come out with this bruh :))
{
    if (!root)
        return 0;

    // Use a queue for level-order traversal
    typedef struct {
        bTree *node;
        bTree *parent;
    } NodeInfo;

    NodeInfo queue[100]; // Simple queue for BFS (adjust size as needed)
    int front = 0, rear = 0;

    // Enqueue the root node with a NULL parent
    queue[rear++] = (NodeInfo){root, NULL};

    while (front < rear)
    {
        int levelSize = rear - front; // Number of nodes at the current level
        bTree *firstParent = NULL;

        for (int i = 0; i < levelSize; i++)
        {
            NodeInfo current = queue[front++];

            // Check if there are multiple nodes at the same level with different parents
            if (firstParent && firstParent != current.parent)
                return 1; // Found cousins

            firstParent = current.parent;

            // Enqueue left and right children
            if (current.node->left)
                queue[rear++] = (NodeInfo){current.node->left, current.node};
            if (current.node->right)
                queue[rear++] = (NodeInfo){current.node->right, current.node};
        }
    }

    return 0;
}

int main()
{
    // create an binary search tree
    //                  _____8_____
    //                  |         |
    //                __4__     __10__
    //                |   |     |    |
    //                2   6     9    20
    bTree *root = NULL;
    insert(&root, 8);
    insert(&root, 4);
    insert(&root, 6);
    insert(&root, 2);
    insert(&root, 10);
    insert(&root, 9);
    insert(&root, 20);

    // specifically create a binary tree that is not a binary search tree
    bTree *root1 = (bTree *)malloc(sizeof(bTree));       //                             ___8___
    root1->left = (bTree *)malloc(sizeof(bTree));        //                             |     |
    root1->right = (bTree *)malloc(sizeof(bTree));       //                           __4__   10
    root1->left->left = (bTree *)malloc(sizeof(bTree));  //                           |   |
    root1->left->right = (bTree *)malloc(sizeof(bTree)); //                           2   9
    root1->data = 8;
    root1->left->data = 4;
    root1->right->data = 10;
    root1->left->left->data = 2;
    root1->left->right->data = 9;

    root1->left->left->left = NULL;
    root1->left->left->right = NULL;
    root1->left->right->left = NULL;
    root1->left->right->right = NULL;
    root1->right->left = NULL;
    root1->right->right = NULL;

    // RUALRE EXERCITII
    puts("EXERCITIUL 1:\n");
    printf("Primul arbore binar este echilibrat (1 sau 0): %d.\n", isEven(root));

    puts("\nEXERCITIUL 2:\n");
    printf("Al doilea arbore binar este binary search tree (1 sau 0): %d.\n", isBinarySearchTree(root1, NULL, NULL));

    puts("\nEXERCITIUL 3:\n");
    printf("Cel mai apropiat stramos comun pentru nodurile 6 si 9 din primul arbore este: %d.\n",closestRelative(root,6,9)->data);

    puts("\nEXERCITIUL 4:\n");
    bTree *root2=NULL;
    root2=stringToBtree("1,2,3,4,5");
    printf("Convertim string-ul \"1,2,3,4,5\" intr-un arbore si afisam nodurile: ");
    display(root2,root2);

    char *string=NULL;
    btreeToString(root2,&string);
    printf("Acum convertim arborele creat intr-un string si afisam string-ul: %s.\n",string);

    puts("\nEXERCITIUL 5:\n");
    printf("Primul arbore are verisori (1 sau 0): %d.\n", hasCousins(root));

    puts("\nEXERCITIUL 6:\n");
    printf(
    "Un arbore AVL este un arbore auto-echilibrant, numit dupa Adelson-Velsky si Landis. Practic, de fiecare data "
    "cand se face o operatie de stergere sau inserare, daca se gasesc oricare noduri care sa aiba o diferenta de nivel mai mare decat 1, "
    "atunci se realizeaza niste operatii de rotatie: left-rotation, right-rotation, left-right rotation si right-left rotation cu o complexitate de O(logn) "
    "astfel incat arborele sa ramana mereu echilibrat. Tiparul acesta e folosit in situatiile in care se fac update-uri frecvente, cum ar fi in "
    "baze de date si sisteme de fisiere.\n\n"
    "B-Tree: este un arbore multi-directional de cautare. E folosit in bazele de date, precum MySQL, PostgreSQL sau in sisteme de fisiere, NTFS, ex4, pentru ca "
    "eficientizeaza operatiile de intrare si iesire ale discului pentru a accesa si stoca cantitati mari de informatie. " 
    "E structurat in felul urmator: e ca un binary search tree, dar nodurile au mai multe chei de access, adica in loc sa fie ca la arborele binar "
    "unde poti avea maxim 2 copii, un B-tree poate avea mai multi copii si fiecare copil la randul sau poate sa indice catre copii " 
    "cu mai multe chei fiecare si tot asa."
    );

    free(string);
    freeTree(root);
    freeTree(root1);
    freeTree(root2);
}