#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayIntArray(int *array, int length)
{
    for (int i = 0; i < length; i++)
        printf("%d ", array[i]);
    puts("");
}
void displayFloatArray(double *array, int length)
{
    for (int i = 0; i < length; i++)
        printf("%.9lf ", array[i]);
    puts("");
}
void displayCharArray(char *array, int length)
{
    for (int i = 0; i < length; i++)
        printf("%c ", array[i]);
    puts("");
}

void swap(void *a, void *b, size_t elemSize)
{
    void *p = malloc(elemSize);
    memcpy(p, a, elemSize);
    memcpy(a, b, elemSize);
    memcpy(b, p, elemSize);
    free(p);
}

int compareInt(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}
int compareChar(const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}
int compareDouble(const void *a, const void *b)
{
    double result = *(double *)a - *(double *)b;
    if (result < 0)
        return -1;
    if (result > 0)
        return 1;
    return 0;
}

void bubbleSort(void *array, size_t elemNum, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    for (size_t i = 0; i < elemNum; i++)
        for (size_t j = 0; j < elemNum - 1; j++)
        {
            if (compare(array + j * elemSize, array + (j + 1) * elemSize) > 0)
                swap(array + j * elemSize, array + (j + 1) * elemSize, elemSize);
        }
}
void insertionSort(void *array, size_t elemNum, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    void *temp = malloc(elemSize);
    for (size_t i = 1; i < elemNum; i++)
    {
        for (size_t j = 0; j < i; j++)
            if (compare(array + i * elemSize, array + j * elemSize) < 0)
            {
                memcpy(temp, array + i * elemSize, elemSize);
                for (size_t k = i; k > j; k--)
                    memcpy(array + k * elemSize, array + (k - 1) * elemSize, elemSize);
                memcpy(array + j * elemSize, temp, elemSize);
            }
    }
    free(temp);
}
void selectionSort(void *array, size_t elemNum, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    void *min = malloc(elemSize);
    memcpy(min, array, elemSize);
    for (size_t i = 0; i < elemNum - 1; i++)
    {
        for (size_t j = i + 1; j < elemNum; j++)
            if (compare(array + i * elemSize, array + j * elemSize) > 0)
                swap(array + i * elemSize, array + j * elemSize, elemSize);
        memcpy(min, array + (i + 1) * elemSize, elemSize);
    }
    free(min);
}
void merge(void *array, int left, int middle, int right, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    size_t leftLength = (size_t)(middle - left + 1), rightLength = (size_t)(right - middle);

    void *leftArray = malloc(elemSize * leftLength);
    void *rightArray = malloc(elemSize * rightLength);

    for (size_t i = 0; i < leftLength; i++) // leftArray[i]=array[left+i];
        for (size_t j = 0; j < elemSize; j++)
            *((char *)leftArray + i * elemSize + j) = *((char *)array + (left + i) * elemSize + j); // asta e varianta manuala, copiaza octet cu octet
    // mempcpy(leftArray+i*elemSize,array+(left+i)*elemSize,elemSize); // asta e cu memcpy si e ca mai jos, cu un singur for loop

    for (size_t i = 0; i < rightLength; i++) // rightArray[i]=array[middle+1+i];
        memcpy(rightArray + i * elemSize, array + (middle + 1 + i) * elemSize, elemSize);

    size_t i = 0, j = 0;

    while (i < leftLength && j < rightLength)
    {
        if (compare(leftArray + i * elemSize, rightArray + j * elemSize) < 0)
        {
            memcpy(array + left * elemSize, leftArray + i * elemSize, elemSize);
            i++;
        }
        else
        {
            memcpy(array + left * elemSize, rightArray + j * elemSize, elemSize);
            j++;
        }
        left++;
    }

    while (i < leftLength)
    {
        memcpy(array + left * elemSize, leftArray + i * elemSize, elemSize);
        i++;
        left++;
    }

    while (j < rightLength)
    {
        memcpy(array + left * elemSize, rightArray + j * elemSize, elemSize);
        j++;
        left++;
    }

    free(leftArray);
    free(rightArray);
}
void mergeSort(void *array, int left, int right, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        mergeSort(array, left, middle, elemSize, compare);
        mergeSort(array, middle + 1, right, elemSize, compare);
        merge(array, left, middle, right, elemSize, compare);
    }
}
size_t partition(void *array,size_t low,size_t high,size_t elemSize,int (*compare)(const void* a, const void*b))
{
    void *temp=malloc(elemSize);
    memcpy(temp,array+high*elemSize,elemSize);
    size_t i=low-1;

    for(size_t j=low;j<high;j++)
        {
            if(compare(array+j*elemSize,temp)<=0)
                {
                    i++;
                    if(j>i)
                    swap(array+j*elemSize,array+i*elemSize,elemSize);
                }
        }
        free(temp);
        return i; 
}
void quickSort(void *array,size_t low,size_t high, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    if(low < high)
    {
        size_t pivot=partition(array,low,high,elemSize,compare);

        quickSort(array,low,pivot-1,elemSize,compare);
        quickSort(array,pivot+1,high,elemSize,compare);
    }
}

int main()
{
    int v[10] = {-47, 46, -91, -64, 100, 92, -20, 83, -12, 10};
    double w[10] = {90.675, -60.980, 86.10, 4.99, 30.2682854, -29.178584028, -86.58683, -51.1535, -76.40793, 32.169};
    char c[10] = {'C', 'Y', 'E', 'B', 'D', 'W', 'a', 'O', 's', 'Y'};

    // bubbleSort(v, sizeof(v) / sizeof(int), sizeof(int), compareInt);
    // bubbleSort(w, sizeof(w) / sizeof(double), sizeof(double), compareDouble);
    // bubbleSort(c, sizeof(c) / sizeof(char), sizeof(char), compareChar);

    // insertionSort(v, sizeof(v) / sizeof(int), sizeof(int), compareInt);
    // insertionSort(w, sizeof(w) / sizeof(double), sizeof(double), compareDouble);
    // insertionSort(c, sizeof(c) / sizeof(char), sizeof(char), compareChar);

    // selectionSort(v, sizeof(v) / sizeof(int), sizeof(int), compareInt);
    // selectionSort(w, sizeof(w) / sizeof(double), sizeof(double), compareDouble);
    // selectionSort(c, sizeof(c) / sizeof(char), sizeof(char), compareChar);

    //mergeSort(v, 0, sizeof(v) / sizeof(int) - 1, sizeof(int), compareInt);
    // mergeSort(w, 0, sizeof(w) / sizeof(double) - 1, sizeof(double), compareDouble);
    // mergeSort(c, 0, sizeof(c) / sizeof(char) - 1, sizeof(char), compareChar);

    quickSort(v,0, sizeof(v) / sizeof(int)-1, sizeof(int), compareInt);
    quickSort(w,0, sizeof(w) / sizeof(double)-1, sizeof(double), compareDouble);
    quickSort(c,0, sizeof(c) / sizeof(char)-1, sizeof(char), compareChar);

    displayIntArray(v, sizeof(v) / sizeof(int));
    displayFloatArray(w, sizeof(w) / sizeof(double));
    displayCharArray(c, sizeof(c) / sizeof(char));
}