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

bTree *search(bTree *root,int data)
{
    if(root==NULL)
        return NULL;
    
    printf("Nodul %d\n",root->data);
    if(data==root->data)
        return root;
    search(root->left,data);
    search(root->right,data);
}
int isEven(bTree *root)
{
    int max1=0,max2=0;
    bTree *left=root,*right=root;
    while(left)
    {
        if(left)
            max1++;
        
    }
}
int main()
{
    bTree *root=NULL;
    insert(&root,7);
    insert(&root,8);
    insert(&root,11);
    insert(&root,4);
    insert(&root,6);
    insert(&root,2);
    insert(&root,1);
    search(root,2);
}