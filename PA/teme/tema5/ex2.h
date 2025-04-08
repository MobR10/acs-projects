#include <stdio.h>
#include <stdlib.h>

int isLeftEmpty(size_t leftHeight)
{
    if (leftHeight == 0)
        return 1;
    return 0;
}

int isRightEmpty(size_t rightHeight)
{
    if (rightHeight == 0)
        return 1;
    return 0;
}
void displayLeft(int *v, size_t leftHeight)
{
    if (isLeftEmpty(leftHeight))
    {
        puts("Left stack is empty. Can't display anything.");
    }
    else
    {
        puts("Left Stack:");
        size_t i = 0;
        while (i < leftHeight)
        {
            printf("(Index: %zu, Data: %d)\n", leftHeight - 1 - i, v[leftHeight - i - 1]);
            i++;
        }
    }
}

void displayRight(int *v, size_t leftHeight, size_t rightHeight)
{
    if (isRightEmpty(rightHeight))
    {
        puts("Right stack is empty. Can't display anything.");
    }
    else
    {
        puts("Right Stack:");
        size_t i = 0;
        while (i < rightHeight)
        {
            printf("(Index: %zu, Data: %d)\n", rightHeight - 1 - i, v[leftHeight + rightHeight - i - 1]);
            i++;
        }
    }
}

void displayStacks(int *v, size_t leftHeight, size_t rightHeight)
{
    displayLeft(v, leftHeight);
    puts("");
    displayRight(v, leftHeight, rightHeight);
}

int *createStacks(size_t *leftHeight, int leftData, size_t *rightHeight, int rightData)
{
    *leftHeight = 1;
    *rightHeight = 1;
    int *v = (int *)malloc(((*leftHeight) + (*rightHeight)) * sizeof(int));
    checkAllocation(v);
    v[0] = leftData;
    v[1] = rightData;
    return v;
}

void pushLeft(int **v, size_t *leftHeight, size_t rightHeight, int data)
{
    (*leftHeight)++;
    *v = (int *)realloc(*v, sizeof(int) * ((*leftHeight) + rightHeight));
    checkAllocation(*v);
    for (size_t i = (*leftHeight) + rightHeight - 1; i >= (*leftHeight); i--)
    {
        (*v)[i] = (*v)[i - 1];
    }
    (*v)[(*leftHeight) - 1] = data;
}

void pushRight(int **v, size_t leftHeight, size_t *rightHeight, int data)
{
    (*rightHeight)++;
    *v = (int *)realloc(*v, sizeof(int) * (leftHeight + (*rightHeight)));
    checkAllocation(*v);
    (*v)[leftHeight + (*rightHeight) - 1] = data;
}

void pushElements(int **v, size_t *leftHeight, int leftData, size_t *rightHeight, int rightData)
{
    pushLeft(v, leftHeight, *rightHeight, leftData);
    pushRight(v, *leftHeight, rightHeight, rightData);
}

void popLeft(int **v, size_t *leftHeight, size_t rightHeight)
{
    if (isLeftEmpty(*leftHeight))
    {
        puts("Left stack is empty. Can't pop.");
    }
    else
    {
        for (size_t i = (*leftHeight) - 1; i < (*leftHeight) + rightHeight - 1; i++)
            (*v)[i] = (*v)[i + 1];
        *v = (int *)realloc(*v, sizeof(int) * ((*leftHeight) + rightHeight - 1));
        (*leftHeight)--;
    }
}

void popRight(int **v, size_t leftHeight, size_t *rightHeight)
{
    if (isRightEmpty(*rightHeight))
    {
        puts("Right stack is empty. Can't pop.");
    }
    else
    {
        *v = (int *)realloc(*v, sizeof(int) * (leftHeight + (*rightHeight) - 1));
        (*rightHeight)--;
    }
}