#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void merge(void *array, int left,int middle,int right,size_t elemSize,int (*compare)(const void*a,const void*b))
{
    size_t leftLength=(size_t)(middle-left+1), rightLength=(size_t)(right-middle);

    void *leftArray=malloc(elemSize*leftLength);
    void *rightArray=malloc(elemSize*rightLength);

    for(size_t i=0;i<leftLength;i++)    //leftArray[i]=array[left+i];
        for(size_t j=0;j<elemSize;j++)
        *((char*)leftArray+i*elemSize+j)=*((char*)array+(left+i)*elemSize+j); // asta e varianta manuala, copiaza octet cu octet
        //mempcpy(leftArray+i*elemSize,array+(left+i)*elemSize,elemSize); // asta e cu memcpy si e ca mai jos, cu un singur for loop
    
    for(size_t i=0;i<rightLength;i++) //rightArray[i]=array[middle+1+i];
        memcpy(rightArray+i*elemSize,array+(middle+1+i)*elemSize,elemSize);
    
    size_t i=0,j=0;
    
    while(i<leftLength&&j<rightLength)
    {
        if(compare(leftArray+i*elemSize,rightArray+j*elemSize)<0)
            {
                memcpy(array+left*elemSize,leftArray+i*elemSize,elemSize);
                i++;
            }
        else
        {
            memcpy(array+left*elemSize,rightArray+j*elemSize,elemSize);
                j++;
        }
        left++;
    }

    while(i<leftLength)
    {
        memcpy(array+left*elemSize,leftArray+i*elemSize,elemSize);
        i++;
        left++;
    }

    while(j<rightLength)
    {
        memcpy(array+left*elemSize,rightArray+j*elemSize,elemSize);
        j++;
        left++;
    }

    free(leftArray);
    free(rightArray);

}
void mergeSort(void *array,int left, int right, size_t elemSize,int (*compare)(const void*a,const void*b))
{
    if(left<right)
    {
        int middle=(left+right)/2;
        mergeSort(array,left,middle,elemSize,compare);
        mergeSort(array,middle+1,right,elemSize,compare);
        merge(array,left,middle,right,elemSize,compare);
    }
}
int compareInt(const void*a,const void *b)
{
    return *((int*)a)-*((int*)b);
}

int compareChar(const void*a,const void*b)
{
    return *(char*)a-*(char*)b;
}

int compareFloat(const void*a,const void*b)
{
    float result=*(float*)a-*(float*)b;
    if( result < 0 ) return -1;
    if( result >0 ) return 1;
    return 0;  

}

int main()
{
    int v[10]={-47,46,-91,-64,100,92,-20,83,-12,10};
    float w[5]={5.,4.,3.,2.,1.};
    char c[5]={'e','d','c','b','a'};
    mergeSort(v,0,9,sizeof(int),compareInt);
    mergeSort(w,0,4,sizeof(float),compareFloat);
    mergeSort(c,0,4,sizeof(char),compareChar);
    display(v,10);
    puts("");
    for(int i=0;i<5;i++)
        {
            printf("%f ",w[i]);
        }
    
        puts("");
    for(int i=0;i<5;i++)
        {
            printf("%c ",c[i]);
        }


}