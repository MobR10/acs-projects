#include <stdio.h>
#include <stdlib.h>

struct binaryTree
{
    int data;
    struct binaryTree *left;
    struct binaryTree *right;
};
typedef struct binaryTree bTree;

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
bTree* closestRelative(bTree *root, int node1, int node2) // parcurgere post-oder
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

// EX5
int areCousins(bTree *root, int data1, int data2)
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

    // printf("%d\n", getHeight(root));
    // printf("%d\n", isEven(root));

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
    // printf("%d\n", isBinarySearchTree(root1, NULL, NULL));
    printf("%d\n", areCousins(root,4,9));
}