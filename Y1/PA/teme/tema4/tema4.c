/*
This code is also posted at https://github.com/MobR10/acs-projects (newer changes are more likely to be kept on 'temp' branch for a long time before merging with 'main' so always check 'temp')
Summary of some of the functions used in this code:
- memcpy = copies a set of bytes from a source to a destination (stdlib.h) .
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // pentru memcpy
#include <time.h>   // pentru exercitiul 2

#define UPPER_LIMIT 100 // pentru exercitiul 2 la functia rand()

// Schimba din 0 in 1 pentru a rula exercitiul respectiv inainte de build&run
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
void displayDoubleArray(double *array, int length)
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
// Folosite la toate functiile de sortare, construite pentru a fi folosite la orice tip de date
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
            if (compare((char *)array + j * elemSize, (char *)array + (j + 1) * elemSize) > 0) // asta se repeta la toti algoritmii de sortare, doar ca uneori e cu > sau <= sau >= 0, depidne de algoritm
                swap((char *)array + j * elemSize, (char *)array + (j + 1) * elemSize, elemSize);
        }
}
void insertionSort(void *array, size_t elemNum, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    void *temp = malloc(elemSize);
    for (size_t i = 1; i < elemNum; i++)
    {
        for (size_t j = 0; j < i; j++)
            if (compare((char *)array + i * elemSize, (char *)array + j * elemSize) < 0)
            {
                memcpy(temp, (char *)array + i * elemSize, elemSize);
                for (size_t k = i; k > j; k--)
                    memcpy((char *)array + k * elemSize, (char *)array + (k - 1) * elemSize, elemSize);
                memcpy((char *)array + j * elemSize, temp, elemSize);
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
            if (compare((char *)array + i * elemSize, (char *)array + j * elemSize) > 0)
                swap((char *)array + i * elemSize, (char *)array + j * elemSize, elemSize);
        memcpy(min, (char *)array + (i + 1) * elemSize, elemSize);
    }
    free(min);
}
void merge(void *array, size_t left, size_t middle, size_t right, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    size_t leftLength = (size_t)(middle - left + 1), rightLength = (size_t)(right - middle);

    void *leftArray = malloc(elemSize * leftLength);
    void *rightArray = malloc(elemSize * rightLength);

    for (size_t i = 0; i < leftLength; i++) // leftArray[i]=array[left+i];
        for (size_t j = 0; j < elemSize; j++)
            *((char *)leftArray + i * elemSize + j) = *((char *)array + (left + i) * elemSize + j); // asta e varianta manuala, copiaza octet cu octet
    // mempcpy(leftArray+i*elemSize,array+(left+i)*elemSize,elemSize); // asta e cu memcpy si e ca mai jos, cu un singur for loop

    for (size_t i = 0; i < rightLength; i++) // rightArray[i]=array[middle+1+i];
        memcpy((char *)rightArray + i * elemSize, (char *)array + (middle + 1 + i) * elemSize, elemSize);

    size_t i = 0, j = 0;

    while (i < leftLength && j < rightLength)
    {
        if (compare((char *)leftArray + i * elemSize, (char *)rightArray + j * elemSize) < 0)
        {
            memcpy((char *)array + left * elemSize, (char *)leftArray + i * elemSize, elemSize);
            i++;
        }
        else
        {
            memcpy((char *)array + left * elemSize, (char *)rightArray + j * elemSize, elemSize);
            j++;
        }
        left++;
    }

    while (i < leftLength)
    {
        memcpy((char *)array + left * elemSize, (char *)leftArray + i * elemSize, elemSize);
        i++;
        left++;
    }

    while (j < rightLength)
    {
        memcpy((char *)array + left * elemSize, (char *)rightArray + j * elemSize, elemSize);
        j++;
        left++;
    }

    free(leftArray);
    free(rightArray);
}
void mergeSort(void *array, size_t left, size_t right, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    if (left < right)
    {
        size_t middle = (left + right) / 2;
        mergeSort(array, left, middle, elemSize, compare);
        mergeSort(array, middle + 1, right, elemSize, compare);
        merge(array, left, middle, right, elemSize, compare);
    }
}
size_t partition(void *array, size_t low, size_t high, size_t elemSize, int (*compare)(const void *a, const void *b))
{
    void *temp = malloc(elemSize);
    memcpy(temp, (char *)array + high * elemSize, elemSize);
    size_t i = low - 1;
    for (size_t j = low; j <= high; j++)
    {
        if (compare((char *)array + j * elemSize, temp) <= 0)
        {
            i++;
            if (j > i)
                swap((char *)array + j * elemSize, (char *)array + i * elemSize, elemSize);
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
    while (!found && left <= right && (int)left >= 0 && (int)right >= 0)
    {
        middle = (left + right) / 2;
        if ((compareResult = compare((char *)array + middle * elemSize, &wanted)) == 0)
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

// Functii exercitiul 5
// RadixSort luat de la www.geeksforgeeks.org/radix-sort/ si apoi parcurs manual ca sa vad ce operatii face pas cu pas.
// note to self: prea mare bataie de cap ca sa sorteze un array doar cu numere (plus ca trebuie schimbat pentru numere negative :clown_emoji:)
int getMax(int *array, int length)
{
    int max = array[0];
    for (int i = 1; i < length; i++)
        if (max < array[i])
            max = array[i];
    return max;
}
void countSort(int array[], int length, int exp)
{
    int *output = (int *)malloc(sizeof(int) * (size_t)length); // Output array
    if (!output)
    {
        puts("Error when allocating memory for output in countSort");
        exit(1);
    }
    int count[10] = {0}; // Initializam cu 0

    // numaram de cate ori apar cifrele
    for (int i = 0; i < length; i++)
        count[(array[i] / exp) % 10]++;

    // Aici schimbi valorile din count astfel incat sa reprezinte pozitia propriu-zisa a elementului in output
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Se contruieste output
    for (int i = length - 1; i >= 0; i--)
    {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }

    // Copiaza output peste array-ul principal
    for (int i = 0; i < length; i++)
        array[i] = output[i];
    free(output);
}
void radixSort(int *array, int length)
{

    int m = getMax(array, length);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(array, length, exp);
}

int main()
{
// EXERCITIU 1
#if EXERCITIUL_1 == 1
    printf("Exercitiul 1\nAvem 3 array-uri cu numere intregi, reale si char. Trebuie sortate folosind toti algoritmii de sortare prezentati la laborator:\n"
    "1) BubbleSort;\n2) InsertionSort;\n3) SelectionSort;\n4) MergeSort;\n5) QuickSort.\nArray-urile sunt:\n\n");
    int v[10] = {-47, 46, -91, -64, 100, 92, -20, 83, -12, 10};
    double w[10] = {90.675, -60.980, 86.10, 4.99, 30.2682854, -29.178584028, -86.58683, -51.1535, -76.40793, 32.169};
    char c[10] = {'C', 'Y', 'E', 'B', 'D', 'W', 'a', 'O', 's', 'Y'};

    printf("Arr1: "); displayIntArray(v,sizeof(v)/sizeof(int));
    printf("Arr2: "); displayDoubleArray(w,sizeof(w)/sizeof(double));
    printf("Arr3: "); displayCharArray(c,sizeof(c)/sizeof(char));

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
    
    printf("\n\nArray-urile dupa sortare:\n");
    printf("Arr1: "); displayIntArray(v,sizeof(v)/sizeof(int));
    printf("Arr2: "); displayDoubleArray(w,sizeof(w)/sizeof(double));
    printf("Arr3: "); displayCharArray(c,sizeof(c)/sizeof(char));
#endif

// EXERCITIUL 2
#if EXERCITIUL_2 == 1
    printf("\nExercitiul 2\nAvem un vector de 10000 de valori random si vrem sa vedem timpul de rulare al fiecarui"
           " algoritm de sortare:\n");
    clock_t timePassed;
    int length = 10000, *vector, *vectorCopy;
    vector = (int *)malloc((size_t)length * sizeof(int));
    vectorCopy = (int *)malloc((size_t)length * sizeof(int));
    if (!vector)
    {
        puts("\nNu s-a putut aloca memorie pentru vector\n");
        exit(1);
    }
    if (!vectorCopy)
    {
        puts("\nNu s-a putut aloca memorie pentru vectorCopy\n");
        exit(1);
    }

    for (int i = 0; i < length; i++)
    {
        vector[i] = rand() % (UPPER_LIMIT + 1); // generez numere intre 0 si UPPER_LIMIT
        vectorCopy[i] = vector[i];
    }

    timePassed = clock();
    bubbleSort(vectorCopy, (size_t)length, sizeof(int), compareInt);
    timePassed = clock() - timePassed;
    printf("Timp pentru BubbleSort: %fs\n", (float)timePassed / CLOCKS_PER_SEC);
    resetVector(vector, vectorCopy, length);

    timePassed = clock();
    insertionSort(vectorCopy, (size_t)length, sizeof(int), compareInt);
    timePassed = clock() - timePassed;
    printf("Timp pentru InsertionSort: %fs\n", (float)timePassed / CLOCKS_PER_SEC);
    resetVector(vector, vectorCopy, length);

    timePassed = clock();
    selectionSort(vectorCopy, (size_t)length, sizeof(int), compareInt);
    timePassed = clock() - timePassed;
    printf("Timp pentru SelectionSort: %fs\n", (float)timePassed / CLOCKS_PER_SEC);
    resetVector(vector, vectorCopy, length);

    timePassed = clock();
    mergeSort(vectorCopy, 0, (size_t)length - 1, sizeof(int), compareInt);
    timePassed = clock() - timePassed;
    printf("Timp pentru MergeSort: %fs\n", (float)timePassed / CLOCKS_PER_SEC);

    timePassed = clock();
    quickSort(vector, 0, (size_t)length - 1, sizeof(int), compareInt);
    timePassed = clock() - timePassed;
    printf("Timp pentru QuickSort: %fs\n", (float)timePassed / CLOCKS_PER_SEC);

    free(vector);
    free(vectorCopy);
#endif

// EXERCITIUL 3
#if EXERCITIUL_3 == 1
    int arr1[10] = {-47, 46, -91, -64, 100, 92, -20, 83, -12, 10};
    int repeat = 1, firstTime = 1, wantedNumber = 0;
    char choice[100];
    // Urmeaza un algoritm pentru user-friendly interaction. In cerinta nu era decat "Utilizatorul poate să adauge numere de mai multe ori". :)
    do
    {
        if (firstTime)
        {
            puts("\nExercitiul 3\nAvem urmatorul array: ");
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

            if (firstTime)
            {
                printf("Intai, hai sa sortam lista pentru a cauta mai rapid, folosind cautarea binara:\n");
                quickSort(arr1, 0, 9, sizeof(int), compareInt); // acum incepe rezolvarea propriu-zisa...finally... mi-a luat prea mult partea de mai sus cu conditiile alea...
                firstTime = 0;
                displayIntArray(arr1, 10);
            }
            length = (int)(sizeof(arr1) / sizeof(int)); 
            int found = 0, position;
            for (int i = 0; i < length && !found; i++)
            {
                position = binarySearch(arr1, (size_t)(i + 1), 9, sizeof(int), compareInt, wantedNumber - arr1[i]);
                if (position != i && position != -1)
                {
                    printf("Am gasit cele 2 valori. Ele sunt: %d si %d.\n\n", arr1[i], wantedNumber - arr1[i]);
                    found = 1;
                }
            }
            if (!found)
                printf("Nu am gasit 2 valori care adunate sa dea %d.\n\n", wantedNumber);
        }
    } while (repeat);
#endif

// EXERCITIUL 4
#if EXERCITIUL_4 == 1
    printf("\nExercitiul 4\nAvem o lista de alergatori, sa se sorteze dupa timp si sa se afiseze cu locul pe care s-au clasat.\n"
           "Lista este:\n");

    Alergator list[10] = {
        {"George", 10.22f},
        {"Ana", 8.75f},
        {"Liviu", 7.3f},
        {"Robert", 7.5f},
        {"Ilinca", 7.8f},
        {"Darius", 7.2f},
        {"Raffael", 7.3f},
        {"Teodora", 7.8f},
        {"Matei", 7.8f},
        {"Eugen", 11.f}};
    for (int i = 0; i < (int)(sizeof(list) / sizeof(Alergator)); i++)
        printf("Alergatorul %d - Nume: %s ; Timp: %.2f\n", i + 1, list[i].name, list[i].time);
    puts("");

    mergeSort(list, 0, sizeof(list) / sizeof(Alergator) - 1, sizeof(Alergator), compareTime);

    int placement = 1;
    for (int i = 0; i < 10; i++)
    {
        if (i < 10 - 1)
        {
            if (list[i].time == list[i + 1].time)
            {
                printf("Locul %d: ", placement);
                placement++;
                float value = list[i].time;
                while (list[i].time == value)
                {
                    if (list[i + 1].time != value)
                        printf("%s ", list[i].name);
                    else
                        printf("%s, ", list[i].name);
                    i++;
                }
                printf("(egalitate)\n");
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
    /*
        Radix sort vrea sa sorteze (by default) un array cu numere naturale dupa cifre, de la cea mai mica unitate de cifra pana la cea mai mare sau invers (cum doresti). In primul rand, ai nevoie sa parcurgi tot array-ul
        si sa aflii cea mai mare valoare ca sa stii cea mai mare unitate de cifra (unitati,zecimale,sute,mii,s.a.m.d.). Algoritmul functioneaza in felul urmator:
        - in functia principala ai un for care merge doar dupa puterile lui 10^i, unde i este unitatea cifrei, incepand cu 10^0. Pentru fiecare putere de-a lui 10, se apeleaza o alta functie: countSort(array,length)
        - in countSort se creeaza un array numit output si unul count(care e de frecventa). Output este un vector in care, in functie de numarul de aparitii al cifrei curente din count, se pun elementele din
        array-ul principal in ordinea crescatoare. Ultimul pas este ca se copiaza output peste array-ul principal.
        - se repeta asta pana cand s-a trecut peste numarul maxim al unitatilor de cifre.
    */
    printf("\nExercitiul 5\nSa se implementeze radixSort.\nArray inainte de sortare: ");
    int arr2[4] = {812, 321, 421, 565};
    displayIntArray(arr2, sizeof(arr2) / sizeof(int));
    radixSort(arr2, sizeof(arr2) / sizeof(int));
    printf("Array dupa sortare: ");
    displayIntArray(arr2, sizeof(arr2) / sizeof(int));
#endif
}