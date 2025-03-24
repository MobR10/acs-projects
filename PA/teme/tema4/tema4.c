#include <stdio.h>
#include <stdlib.h>

int array[10];

int* mergeArrays(int *leftArray,int *rightArray,int left, int middle,int right)
{
    //int *array=(int*)malloc(sizeof(int)*(right-left+1));
    int i=left,j=middle+1,index=0;
    while(i<=middle&&j<=right)
    {
        if(leftArray[i]>rightArray[j])
            {
                array[index]=rightArray[j];
                index++;
                j++;
            }
        else
            {
                array[index]=leftArray[i];
                index++;
                i++;
            }
    }
    while(i<=middle)
    {
        array[index]=leftArray[i];
        index++;
        i++;
    }
    while(j<=right)
    {
        array[index]=rightArray[j];
        index++;
        j++;
    }
    return array;
}

int * mergeSort(int *v,int left,int right)
{
    if(left==right)
        return v+left;

    int middle=(left+right)/2;
    int *leftArray=mergeSort(v,left,middle);
    int *rightArray=mergeSort(v,middle+1,right);

    return mergeArrays(leftArray,rightArray,left,middle,right);

}

void display(int *v,int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",v[i]);
}

int main()
{
    int v[10]={-47,46,-91,-64,100,92,-20,83,-12,10};
    int *w=mergeSort(v,0,9);
    display(w,10);
}