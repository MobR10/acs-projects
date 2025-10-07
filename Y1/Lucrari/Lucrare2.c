#include <stdio.h>
#include <string.h> // PENTRU FUNCTII DE PRELUCRARE SIRURI (EX: STRCPY())
#include <stdlib.h> // PENTRU FUNCTIA ATOI() DE TRECERE DIN SIR IN INTEGER

typedef struct
{
    int zi, luna, an;
} Data;

typedef struct
{
    char nume[30], locatie[30];
    int format_fizic;
    Data data;
} Eveniment;

void parseaza_eveniment(Eveniment v[], char a[][50], int length)
{
    for (int i = 0; i < length; i++)
    {
        char *p;
        p = strtok(a[i], ",");
        strcpy(v[i].nume, p);
        p = strtok(NULL, ",");
        strcpy(v[i].locatie, p);
        p = strtok(NULL, ",");
        v[i].format_fizic = p[0] - '0';

        // VARIANTA DE EXTRAGERE DATA CU FUNCTIA ATOI()
        // p=strtok(NULL,"/");
        // v[i].data.zi=atoi(p);
        // p=strtok(NULL,"/");
        // v[i].data.luna=atoi(p);
        // p=strtok(NULL,"/");
        // v[i].data.an=atoi(p);

        // VARIANTA DE EXTRAGERE DATA MANUAL (SE POATE FACE FUNCTIE SEPARATA, DACA NU STIAI DE ATOI, CA SA EVITI REPETAREA DE 3 ORI A ACELUIASI LUCRU)
        size_t j;
        p = strtok(NULL, "/");
        j = 0;
        v[i].data.zi = 0;
        while (j < strlen(p))
        {
            v[i].data.zi = v[i].data.zi * 10 + (p[j] - '0');
            j++;
        }
        p = strtok(NULL, "/");
        j = 0;
        v[i].data.luna = 0;
        while (j < strlen(p))
        {
            v[i].data.luna = v[i].data.luna * 10 + (p[j] - '0');
            j++;
        }
        p = strtok(NULL, "/");
        j = 0;
        v[i].data.an = 0;
        while (j < strlen(p))
        {
            v[i].data.an = v[i].data.an * 10 + (p[j] - '0');
            j++;
        }
    }
}

int numara_evenimente_online_impare(Eveniment v[], int n)
{
    int counter = 0;

    for (int i = 0; i < n; i++)
        if (v[i].format_fizic == 0 && v[i].data.luna % 2 == 1)
            counter++;

    return counter;
}

Eveniment cel_mai_apropiat_fizic(Eveniment v[], int length, Data data)
{
    Eveniment *event;
    event = NULL;
    int an_min = 999999, luna_min = 13, zi_min = 40;
    for (int i = 0; i < length; i++)
    {
        int val = abs(data.an - v[i].data.an);
        if (v[i].format_fizic == 1 && val < an_min)
        {
            an_min = val;
            event = &v[i];
        }
    }
    for (int i = 0; i < length; i++)
    {
        int val = abs(data.luna - v[i].data.luna);
        if (v[i].format_fizic == 1 && v[i].data.an == event->data.an && val < luna_min)
        {
            luna_min = val;
            event = &v[i];
        }
    }
    for (int i = 0; i < length; i++)
    {
        int val = abs(data.zi - v[i].data.zi);
        if (v[i].format_fizic == 1 && v[i].data.an == event->data.an && v[i].data.luna == event->data.luna && val < zi_min)
        {
            zi_min = val;
            event = &v[i];
        }
    }
    return *event;
}

int main()
{
    char a[10][50];
    Eveniment v[10];
    int n;

    printf("Introduceti un numar natural: ");
    scanf("%d", &n);

    printf("Acum introduceti %d siruri de forma '<nume>,<locatie>,<format_fizic>,<zi>/<luna>/<an>':\n", n);
    for (int i = 0; i < n; i++)
        scanf("%s", a[i]);

    parseaza_eveniment(v, a, n);

    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s,%s,%d,%d/%d/%d\n", v[i].nume, v[i].locatie, v[i].format_fizic, v[i].data.zi, v[i].data.luna, v[i].data.an);
    }

    printf("Numar de evenimente online in luni impare: %d\n", numara_evenimente_online_impare(v, n));
    Data data;
    data.zi = 13;
    data.luna = 11;
    data.an = 2024;
    Eveniment event = cel_mai_apropiat_fizic(v, n, data);

    printf("%s,%s,%d,%d/%d/%d", event.nume, event.locatie, event.format_fizic, event.data.zi, event.data.luna, event.data.an);
}