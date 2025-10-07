#include <stdio.h>
#include <stdlib.h>

// EX 1
void fibonacciIterativ(int numarTermeni)
{
    if (numarTermeni < 2)
        puts("Bai frate, introdu mai mult de 2 termeni");
    else
    {
        int prev = 0, current = 1, next;
        if (numarTermeni == 2)
            printf("%d, %d", prev, current);
        else
            printf("%d, %d, ", prev, current);
        for (int i = 2; i < numarTermeni; i++)
        {
            next = prev + current;
            prev = current;
            current = next;
            if (i == numarTermeni - 1)
                printf("%d", next);
            else
                printf("%d, ", next);
        }
    }
}

void fibonacciRecursive(int n)
{
    static int counter = 1, prev = 0, current = 1;
    if (n < 2)
        puts("Frate, trebuie sa introduci un parametru mai mare decat 2.");
    else if (counter == n)
    {
        printf("%d", current);
    }
    else if (counter == 1 && n == 2)
    {
        printf("%d, %d", prev, current);
    }
    else if (counter == 1)
    {
        printf("%d, %d, ", prev, current);
        int next = prev + current;
        prev = current;
        current = next;
        counter += 2;
        fibonacciRecursive(n);
    }
    else
    {
        printf("%d, ", current);
        int next = prev + current;
        prev = current;
        current = next;
        counter++;
        fibonacciRecursive(n);
    }
}

// EX2
void hanoi(int disk, char *source, char *dest, char *aux)
{
    static int counter = 1;
    if (disk == 1)
    {
        printf("%d: move disk %d from %s to  %s\n", counter, disk, source, dest);
        counter++;
    }
    else
    {
        hanoi(disk - 1, source, aux, dest);
        printf("%d: move disk %d from %s to  %s\n", counter, disk, source, dest);
        counter++;
        hanoi(disk - 1, aux, dest, source);
    }
}

// EX 3
void displayArrayRecursive(int v[], int n)
{
    if (n == 1)
        printf("%d ", v[n - 1]);
    else
    {
        displayArrayRecursive(v, n - 1);
        printf("%d ", v[n - 1]);
    }
}

// EXERCITIUL 5

int check3x3(int array[9][9], int row, int column)
{
    for (int i = row - row % 3; i < row - row % 3 + 3; i++)
        for (int j = column - column % 3; j < column - column % 3 + 3; j++)
        {
            if (array[i][j] == array[row][column] && row != i && column != j)
            {
                return 0;
            }
        }
    return 1;
}
int validate(int array[9][9], int row, int column)
{
    // check row
    for (int j = 0; j < 9; j++)
        if (array[row][column] == array[row][j] && column != j)
            return 0;
    // check column
    for (int i = 0; i < 9; i++)
        if (array[row][column] == array[i][column] && row != i)
            return 0;
    // check 3x3
    if (!check3x3(array, row, column))
        return 0;
    return 1;
}
int solution(int array[9][9])
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(array[i][j]==0||!validate(array,i,j))
                return 0;
    return 1;
}
void display(int array[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            printf("%d ", array[i][j]);
        puts("");
    }
}
void solveSudoku(int array[9][9], int row, int column)
{
        for (int i = row; i < 9; i++)
            for (int j = column; j < 9; j++)
            {
                if (array[i][j] == 0)
                {
                    for(int k=1;k<=10;k++)
                    {
                        if(solution(array))
                                {
                                    return;
                                }
                        array[i][j] = k;
                        if (validate(array, i, j)&&k<10)
                        {
                            solveSudoku(array,i,0);
                        }
                        else if(k>=9)
                        {
                            array[i][j]=0;
                            return;
                        }
                    }  
                }
            }
}
int main()
{
    // EXERCITIUL 1
    printf("EXERCITIUL 1\nAfisare primii 30 de termeni din sirul lui Fibonacci\nIterativ: ");
    fibonacciIterativ(30);
    printf("\nRecursiv: ");
    fibonacciRecursive(30);
    puts("");
    // EXERCITIUL 2
    printf("\nEXERCITIUL 2\nTurnul din hanoi cu 6 discuri\n");
    hanoi(6, "source", "dest", "aux");
    // EXERCITIUL 3
    printf("\nEXERCITIUL 3\nAfisare vector [1,2,3,4,5] recursiv: ");
    int v[5] = {1, 2, 3, 4, 5};
    displayArrayRecursive(v, 5);
    puts("");
    // EXERCITIUL 4
    /*
        Explic divide et impera unui copil de 5 ani: avem 6 mere de diferite dimensiuni fiecare, aranjate aleatoriu pe masa. Noi vrem sa le aranjam de la cel mai mic la cel mai mare. Alegem metoda numita "divide et impera".
        La dispozitia noastra avem bucati de carton pe care le vom folosi ca pe niste pereti. Ca sa ordonam merele, incepem prin a pune cate un carton in mijlocul fiecarui set de mere, unde primul set sunt 
        cele 6 mere ale noastre, astfel incat ajungem sa avem cate un singur mar cuprins intre 2 cartoane sau care are un carton ori in stanga, ori in dreapta lui (adica e primul sau ultimul mar din sirul de mere). 
        Mai pe scurt, vom plasa primul carton dupa al 3-lea mar, apoi vom plasa un carton dupa al 2-lea mar si inca unul dupa al 5-lea mar. Acum avem zone cu un mar si zone cu 2 mere. Ordonam merele din zonele de cate 2 mere.
        Acum ridicam peretele de dupa marul 2 si marul 5 si ordonam din nou cele doua zone cu mere. Ca ultim pas, ridicam ultimul carton, 
        adica cel care a fost plasat primul, si acum ordonam cele doua zone cu mere. Gata, acum avem toate cele 6 mere ordonate crescator dupa marimea lor.
    */
    printf("\nEXERCITIUL 4\nExplic unui copil de 5 ani divide et impera:\n"
    "Avem 6 mere de diferite dimensiuni fiecare, aranjate aleatoriu pe masa. Noi vrem sa le aranjam de la cel mai mic la cel mai mare. Alegem metoda numita \"divide et impera\". "
    "La dispozitia noastra avem bucati de carton pe care le vom folosi ca pe niste pereti. Ca sa ordonam merele, incepem prin a pune cate un carton in mijlocul fiecarui set de mere, unde primul set sunt "
    "cele 6 mere ale noastre, astfel incat ajungem sa avem "
    "cate un singur mar cuprins intre 2 cartoane sau care are un carton ori in stanga, ori in dreapta lui (adica e primul sau ultimul mar din sirul de mere). Mai pe scurt, vom plasa primul carton dupa al 3-lea "
    "mar, apoi vom plasa un carton dupa al 2-lea mar si inca unul dupa al 5-lea mar. Acum avem zone cu un mar si zone cu 2 mere. Ordonam merele din zonele de cate 2 mere. Acum ridicam peretele de dupa marul 2 si marul 5 "
    "si ordonam din nou cele doua zone cu mere. Ca ultim pas, ridicam ultimul carton, adica cel care a fost plasat primul, si acum ordonam cele doua zone cu mere. Gata, acum avem toate cele 6 mere ordonate crescator dupa "
    "marimea lor.\n"
    );
    // EXERCITIUL 5
    printf("\nEXERCITIUL 5\nRezolvare sudoku folosind backtracking\n");
    int array[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 8},
        {1, 8, 0, 0, 0, 2, 3, 0, 0},
        {0, 6, 0, 0, 5, 7, 0, 0, 1},
        {0, 7, 0, 9, 6, 0, 0, 0, 0},
        {0, 9, 0, 7, 0, 4, 0, 1, 0},
        {0, 0, 0, 0, 8, 1, 0, 4, 0},
        {6, 0, 0, 2, 4, 0, 0, 8, 0},
        {0, 0, 4, 5, 0, 0, 0, 9, 3},
        {5, 0, 0, 0, 0, 0, 0, 0, 0}};

    // int array[9][9] = {  //solutie
    //     {7, 4, 2, 6, 1, 3, 9, 5, 8},
    //     {1, 8, 5, 4, 9, 2, 3, 6, 7},
    //     {9, 6, 3, 8, 5, 7, 4, 2, 1},
    //     {4, 7, 1, 9, 6, 5, 8, 3, 2},
    //     {3, 9, 8, 7, 2, 4, 5, 1, 6},
    //     {2, 5, 6, 3, 8, 1, 7, 4, 9},
    //     {6, 3, 7, 2, 4, 9, 1, 8, 5},
    //     {8, 1, 4, 5, 7, 6, 2, 9, 3},
    //     {5, 2, 9, 1, 3, 8, 6, 7, 4}};
    printf("\nMatricea initiala:\n");
    display(array);
    solveSudoku(array, 0, 0);
    printf("\nMatricea dupa rezolvare:\n");
    display(array);
    // EXERCITIUL 6
    /*
    Tail Recursion este o functie a carei ultime instructiuni este un autoapel, doar ca acel autoapel nu trebuie sa fie insotit de alti parametri transmisi
    la randul lor autoapelului respectiv. Acest lucru ajuta compilatorul la eficienta.
    */
   printf("\nEXERCITIUL 6:\n"
    "Tail Recursion este o functie a carei ultime instructiuni este un autoapel, doar ca acel autoapel nu trebuie sa fie insotit de alti parametri transmisi "
    "la randul lor autoapelului respectiv. Acest lucru ajuta compilatorul la eficienta."
    );
    return 0;
}