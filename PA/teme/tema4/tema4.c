#include <stdio.h>
#include <stdlib.h>
#include <string.h> // pentru memcpy
#include <time.h>   // pentru exercitiul 2
#include <ctype.h>

#define UPPER_LIMIT 100 // pentru exercitiul 2

#define EXERCITIUL_1 0
#define EXERCITIUL_2 0
#define EXERCITIUL_3 0
#define EXERCITIUL_4 0
#define EXERCITIUL_5 0

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

// Functii exercitiul 1
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
size_t partition(void *array, size_t low, size_t high, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    void *temp = malloc(elemSize);
    memcpy(temp, array + high * elemSize, elemSize);
    size_t i = low - 1;
    for (size_t j = low; j <= high; j++)
    {
        if (compare(array + j * elemSize, temp) <= 0)
        {
            i++;
            if (j > i)
                swap(array + j * elemSize, array + i * elemSize, elemSize);
        }
    }
    free(temp);
    return i;
}
void quickSort(void *array, size_t low, size_t high, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    if (low < high)
    {
        size_t pivot = partition(array, low, high, elemSize, compare);
        if (pivot > 0) // ca sa ne asiguram ca nu facem overflow la stanga. size_t i==-1 <=> size_t i==2^64 si strica tot algoritmul. learn new things everyday...
            quickSort(array, low, pivot - 1, elemSize, compare);
        quickSort(array, pivot + 1, high, elemSize, compare);
    }
}

// Functii exercitiul 2
void resetVector(int *array, int *arrayCopy, int length)
{
    for (int i = 0; i < length; i++)
        arrayCopy[i] = array[i];
}
// Functii exercitiul 3
int binarySearch(void *array, size_t left, size_t right, size_t elemSize, int (*compare)(void const *a, void const *b), int wanted)
{
    int found = 0, compareResult;
    size_t middle;
    while (!found && left <= right && (int)left>=0 && (int)right>=0)
    {
        middle = (left + right) / 2;
        if ((compareResult = compare(array + middle * elemSize, &wanted)) == 0)
            found = 1;
        else if (compareResult < 0)
        {
            left = middle + 1;
        }
        else
            right = middle - 1;
    }
    if (found)
    {
        return (int)middle; // return la pozitie la care il gaseste
    }
    return -1;
}

// Functii exercitiul 4
typedef struct
{
    char name[50];
    float time;
} Alergator;

int compareTime(const void *a, const void *b)
{
    float result = (((Alergator *)a)->time) - (((Alergator *)b)->time);
    if (result > 0)
        return 1;
    if (result < 0)
        return -1;
    return 0;
}

int main()
{
// EXERCITIU 1
#if EXERCITIUL_1 == 1
    int v[10] = {-47, 46, -91, -64, 100, 92, -20, 83, -12, 10};
    double w[10] = {90.675, -60.980, 86.10, 4.99, 30.2682854, -29.178584028, -86.58683, -51.1535, -76.40793, 32.169};
    char c[10] = {'C', 'Y', 'E', 'B', 'D', 'W', 'a', 'O', 's', 'Y'};

    bubbleSort(v, sizeof(v) / sizeof(int), sizeof(int), compareInt);
    bubbleSort(w, sizeof(w) / sizeof(double), sizeof(double), compareDouble);
    bubbleSort(c, sizeof(c) / sizeof(char), sizeof(char), compareChar);

    insertionSort(v, sizeof(v) / sizeof(int), sizeof(int), compareInt);
    insertionSort(w, sizeof(w) / sizeof(double), sizeof(double), compareDouble);
    insertionSort(c, sizeof(c) / sizeof(char), sizeof(char), compareChar);

    selectionSort(v, sizeof(v) / sizeof(int), sizeof(int), compareInt);
    selectionSort(w, sizeof(w) / sizeof(double), sizeof(double), compareDouble);
    selectionSort(c, sizeof(c) / sizeof(char), sizeof(char), compareChar);

    mergeSort(v, 0, sizeof(v) / sizeof(int) - 1, sizeof(int), compareInt);
    mergeSort(w, 0, sizeof(w) / sizeof(double) - 1, sizeof(double), compareDouble);
    mergeSort(c, 0, sizeof(c) / sizeof(char) - 1, sizeof(char), compareChar);

    quickSort(v, 0, sizeof(v) / sizeof(int) - 1, sizeof(int), compareInt);
    quickSort(w, 0, sizeof(w) / sizeof(double) - 1, sizeof(double), compareDouble);
    quickSort(c, 0, 9, sizeof(char), compareChar);

    displayIntArray(v, sizeof(v) / sizeof(int));
    displayFloatArray(w, sizeof(w) / sizeof(double));
    displayCharArray(c, sizeof(c) / sizeof(char));
#endif

// EXERCITIUL 2
#if EXERCITIUL_2 == 1
    clock_t time_req;
    int length = 10000, *vector, *vectorCopy;
    vector = (int *)malloc(length * sizeof(int));
    vectorCopy = (int *)malloc(length * sizeof(int));
    if (!vector)
    {
        puts("Nu s-a putut aloca memorie pentru vector");
        exit(1);
    }
    if (!vectorCopy)
    {
        puts("Nu s-a putut aloca memorie pentru vectorCopy");
        exit(1);
    }

    for (int i = 0; i < length; i++)
    {
        vector[i] = rand() % (UPPER_LIMIT + 1); // generez numere intre 0 si UPPER_LIMIT
        vectorCopy[i] = vector[i];
    }

    time_req = clock();
    bubbleSort(vectorCopy, length, sizeof(int), compareInt);
    time_req = clock() - time_req;
    printf("Timp pentru bubbleSort: %fs\n", (float)time_req / CLOCKS_PER_SEC);
    resetVector(vector, vectorCopy, length);

    time_req = clock();
    insertionSort(vectorCopy, length, sizeof(int), compareInt);
    time_req = clock() - time_req;
    printf("Timp pentru insertionSort: %fs\n", (float)time_req / CLOCKS_PER_SEC);
    resetVector(vector, vectorCopy, length);

    time_req = clock();
    selectionSort(vectorCopy, length, sizeof(int), compareInt);
    time_req = clock() - time_req;
    printf("Timp pentru selectionSort: %fs\n", (float)time_req / CLOCKS_PER_SEC);
    resetVector(vector, vectorCopy, length);

    time_req = clock();
    mergeSort(vectorCopy, 0, length - 1, sizeof(int), compareInt);
    time_req = clock() - time_req;
    printf("Timp pentru mergeSort: %fs\n", (float)time_req / CLOCKS_PER_SEC);

    time_req = clock();
    quickSort(vector, 0, length - 1, sizeof(int), compareInt);
    time_req = clock() - time_req;
    printf("Timp pentru quickSort: %fs\n", (float)time_req / CLOCKS_PER_SEC);

    free(vector);
    free(vectorCopy);
#endif

// EXERCITIUL 3
#if EXERCITIUL_3 == 1
    int arr1[10] = {-47, 46, -91, -64, 100, 92, -20, 83, -12, 10};
    int repeat = 1, firstTime = 1, wantedNumber = 0;
    char choice[100];
    do
    {
        if (firstTime)
        {
            puts("Exercitiul 3\nAvem urmatorul array: ");
            displayIntArray(arr1, 10);
            puts("Introduceti de la tastatura o valoare si vom cauta in array o pereche de numere care "
                 "adunate sa dea acea valoare introdusa. De asemenea, daca introduceti 'x', exercitiul se va inchide: ");
        }
        else
        {
            printf("Introduceti o alta valoare sau 'x' pentru a iesi: ");
        }
        do
        {
            scanf("%s", choice);
            if (choice[0] == 'x' || choice[0] == 'X')
            {
                puts("Exercitiul 3 se va inchide.");
                repeat = 0;
            }
            else if ((choice[0] < '0' || choice[0] > '9') && (choice[0] != '-' || (choice[0] == '-' && (choice[1] < '0' || choice[1] > '9'))))
            {
                printf("Te rog sa introduci un numar sau 'x': ");
            }
        } while (choice[0] != 'x' && choice[0] != 'X' && (choice[0] < '0' || choice[0] > '9') && (choice[0] != '-' || (choice[0] == '-' && (choice[1] < '0' || choice[1] > '9'))));

        if (repeat)
        {
            if (choice[0] != '-')
                wantedNumber = atoi(choice); // trece din string in integer
            if (choice[0] == '-')
                wantedNumber = -atoi(choice + 1);

            if(firstTime)
            {
                printf("Intai, hai sa sortam lista pentru a cauta mai rapid, folosind cautarea binara:\n");
                quickSort(arr1, 0, 9, sizeof(int), compareInt); // acum incepe rezolvarea propriu-zisa...finally... mi-a luat prea mult partea de mai sus cu conditiile alea...
                firstTime = 0;
                displayIntArray(arr1,10);
            }
            int length=(int)(sizeof(arr1)/sizeof(int)),found=0,position;
            for(int i=0;i<length&&!found;i++)
            {
                position=binarySearch(arr1, (size_t)(i+1), 9, sizeof(int), compareInt, wantedNumber-arr1[i]);
                if(position!=i&&position!=-1)
                    {
                        printf("Am gasit cele 2 valori. Ele sunt: %d si %d.\n\n",arr1[i],wantedNumber-arr1[i]);
                        found=1;
                    }
            }
            if(!found)
            printf("Nu am gasit 2 valori care adunate sa dea %d.\n\n",wantedNumber);
        }
    } while (repeat);
#endif

// EXERCITIUL 4
#if EXERCITIUL_4 == 1
    Alergator list[10] = {
        {"George", 10.22},
        {"Ana", 8.75},
        {"Liviu", 7.77},
        {"Robert", 7.5},
        {"Ilinca", 7.8},
        {"Darius", 7.2},
        {"Raffael", 7.2},
        {"Teodora", 7.8},
        {"Matei", 7.8},
        {"Eugen", 11}};
    mergeSort(list, 0, sizeof(list) / sizeof(Alergator) - 1, sizeof(Alergator), compareTime);
    int placement = 1;
    for (int i = 0; i < 10; i++)
    {
        if (i < 10 - 1)
        {
            if (list[i].time == list[i + 1].time)
            {
                printf("Locul %d (egalitate): ", placement);
                placement++;
                float value = list[i].time;
                while (list[i].time == value)
                {
                    if (list[i + 1].time != value)
                        printf("%s\n", list[i].name);
                    else
                        printf("%s, ", list[i].name);
                    i++;
                }
                i--;
            }
            else
            {
                printf("Locul %d: %s\n", placement, list[i].name);
                placement++;
            }
        }
        else
        {
            printf("Locul %d: %s\n", placement, list[i].name);
            placement++;
        }
    }
#endif
// EXERCITIUL 5
#if EXERCITIUL_5 == 1

#endif
}
