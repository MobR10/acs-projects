#include <stdio.h>
#include <stdlib.h>

void display(int *v,int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",v[i]);
}

void swap(int *a,int *b)
{
    int aux=*a;
    *a=*b;
    *b=aux;
}
void mergeArrays(int *v,int left,int middle,int right)
{
    int leftLength,rightLength;
    leftLength=middle-left+1;
    rightLength=right-middle;
    int *leftArray=(int*)malloc(sizeof(int)*leftLength),*rightArray=(int*)malloc(sizeof(int)*rightLength);
    for(int i=0;i<leftLength;i++)
    {
        leftArray[i]=v[left+i];
    }
    for(int i=0;i<rightLength;i++)
    {
        rightArray[i]=v[middle+1+i];
    }

    int i=0,j=0;

    while(i<leftLength&&j<rightLength)
    {
        if(leftArray[i]<rightArray[j])
            {
                v[left]=leftArray[i];
                i++;
            }
        else
        {
            v[left]=rightArray[j];
            j++;
        }
        left++;
    }
    while(i<leftLength)
    {
        v[left]=leftArray[i];
        i++;
        left++;
    }
    while(j<rightLength)
    {
        v[left]=rightArray[j];
        j++;
        left++;
    }
    free(leftArray);
    free(rightArray);
}
void mergeSort(int *v,int left,int right)
{
    if(left<right)
    {
        int middle=(left+right)/2;
        mergeSort(v,left,middle);
        mergeSort(v,middle+1,right);
        mergeArrays(v,left,middle,right); 
    }
    

}

int comp(const void*a,const void *b)
{
    return *((int*)a)-*((int*)b);
}

int main()
{
    int v[10]={-47,46,-91,-64,100,92,-20,83,-12,10};
    mergeSort(v,0,9);
    display(v,10);

}