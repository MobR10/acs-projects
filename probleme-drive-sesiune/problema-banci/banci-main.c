/*
    LINK PROBLEMA: https://drive.google.com/drive/folders/1mgqIIkUzDtEcTsVToa0VqFxMn57ElctD
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 3
typedef struct
{
    char nume[50];
    float debit, credit;
    int codClient;
} Client;

/*PUNCTUL a)*/ int codMaxim(Client vector[], int length)
{
    int maxim = vector[0].codClient;
    for (int i = 1; i < length; i++)
        if (vector[i].codClient > maxim)
            maxim = vector[i].codClient;
    return maxim;
}

void sortCrescDupaNume(Client v[], int length)
{
    for (int i = 0; i < length - 1; i++)
        for (int j = i + 1; j < length; j++)
            if (strcmp(v[i].nume, v[j].nume) > 0)
            {
                Client aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
}
// rez1, rez2 si rez3 sunt vectorii cu clientii doar primei banci, clientii comuni si, respectiv, clientii doar ai bancii 2!
// ALOGRITM DE FORMA INTERCLASARE, DOAR CA CREEZ 3 VECTORI
/*PUNCTUL b)*/ void functie(Client banca1[], int length1, Client banca2[], int length2, Client rez1[], int *rezLength1, Client rez2[], int *rezLength2, Client rez3[], int *rezLength3)
{
    sortCrescDupaNume(banca1, length1);
    sortCrescDupaNume(banca2, length2);

    int i = 0, j = 0;
    while (i < length1 && j < length2)
    {
        if (strcmp(banca1[i].nume, banca2[j].nume) < 0)
        {
            rez1[*rezLength1] = banca1[i];
            (*rezLength1)++;
            i++;
        }
        else if (strcmp(banca1[i].nume, banca2[j].nume) > 0)
        {
            rez3[*rezLength3] = banca2[j];
            (*rezLength3)++;
            j++;
        }
        else
        {
            rez2[*rezLength2] = banca2[j];
            rez2[*rezLength2].debit += banca1[i].debit;
            rez2[*rezLength2].credit += banca1[i].credit;
            (*rezLength2)++;
            i++;
            j++;
        }
    }
    while(i<length1)
    {
        rez1[*rezLength1] = banca1[i];
        (*rezLength1)++;
        i++;
    }
    while(j<length2)
    {
        rez3[*rezLength3] = banca2[j];
        (*rezLength3)++;
        j++;
    }
}

#if DEBUG == 1 || DEBUG == 2 || DEBUG == 3
void afiseazaClienti(Client v[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("Clientul numarul %d:\n", i + 1);
        printf("Nume: %s\n", v[i].nume);
        printf("Debit: %.2f\n", v[i].debit);
        printf("Credit: %.2f\n", v[i].credit);
        printf("Cod client: %d\n", v[i].codClient);
    }
    puts("");
}
#endif
/*PUNCTUL c)*/ int main()
{
    Client banca1[10], banca2[10],rez1[10],rez2[10],rez3[10];
    int length1 = 0, length2 = 0,rezLength1=0,rezLength2=0,rezLength3=0;
    //====================
    // CITIRE FISIERE banca1.txt SI banca2.txt
    // IN ENUNT NU APARE SI FELUL IN CARE SUNT STRUCTURATE FISIERELE TEXT, ASTFEL CA VOI CONSIDERA CA INFORMATIILE DESPRE CLIENTI SUNT SCRISE DIRECT CATE UNA PE FIECARE LINIE!
    //====================
    FILE *f1, *f2;
    if ((f1 = fopen("banca1.txt", "rt")) == NULL)
    {
        puts("Nu s-a putut deschide fisierul banca1.txt pentru citire");
        exit(1);
    }
    if ((f2 = fopen("banca2.txt", "rt")) == NULL)
    {
        puts("Nu s-a putut deschide fisierul banca2.txt pentru citire");
        exit(1);
    }

    {
        char nume[50],c;
        float debit, credit;
        int codClient;
        while (!feof(f1))
        {
            fgets(nume, 50, f1);
            nume[strlen(nume) - 1] = '\0';
            fscanf(f1, "%f", &debit);
            fscanf(f1, "%f", &credit);
            fscanf(f1, "%d", &codClient);
            fscanf(f1,"%c", &c);
            strcpy(banca1[length1].nume, nume);
            banca1[length1].debit = debit;
            banca1[length1].credit = credit;
            banca1[length1].codClient = codClient;
            length1++;
        }
        fclose(f1);
        while (!feof(f2))
        {
            fgets(nume, 50, f2);
            nume[strlen(nume) - 1] = '\0';
            fscanf(f2, "%f", &debit);
            fscanf(f2, "%f", &credit);
            fscanf(f2, "%d", &codClient);
            fscanf(f2,"%c", &c);
            strcpy(banca2[length2].nume, nume);
            banca2[length2].debit = debit;
            banca2[length2].credit = credit;
            banca2[length2].codClient = codClient;
            length2++;
        }
        fclose(f2);
    }

#if DEBUG == 1
    puts("AFISARE IMEDIAT DUPA CITIREA FISIERELOR");
    puts("BANCA 1:");
    afiseazaClienti(banca1, length1);
    puts("BANCA 2:");
    afiseazaClienti(banca2, length2);
#endif

int cmax = codMaxim(banca2, length2);


functie(banca1,length1,banca2,length2,rez1,&rezLength1,rez2,&rezLength2,rez3,&rezLength3);

#if DEBUG == 2
    puts("REZ 1:");
    afiseazaClienti(rez1, rezLength1);
    puts("REZ 2:");
    afiseazaClienti(rez2, rezLength2);
    puts("REZ 3:");
    afiseazaClienti(rez3, rezLength3);
#endif

// CREARE FISIERUL BINAR
    FILE *fisierBinar;
    if((fisierBinar=fopen("fisierBinar.dat","wb"))==NULL)
    {
        puts("Eroare la crearea fisierului binar.");
        exit(1);
    }
    if(rezLength1>0)
    fwrite(rez1,sizeof(Client),rezLength1,fisierBinar);
    if(rezLength2>0)
    fwrite(rez2,sizeof(Client),rezLength2,fisierBinar);
    for(int i=0;i<length1;i++)
        banca1[i].codClient=cmax+i+1;
    fwrite(banca1,sizeof(Client),length1,fisierBinar);
    fclose(fisierBinar);

    printf("Numarul total de clienti din fisierul binar este: %d", rezLength1+rezLength2+length1);

    #if DEBUG == 3
    fisierBinar=fopen("fisierBinar.dat","rb");

    if(rezLength1>0)
    fread(rez1,sizeof(Client),rezLength1,fisierBinar);

    if(rezLength2>0)
    fread(rez2,sizeof(Client),rezLength2,fisierBinar);

    for(int i=0;i<length1;i++)
        banca1[i].codClient=cmax+i+1;
    fread(banca1,sizeof(Client),length1,fisierBinar);

    fclose(fisierBinar);
    puts("");
    afiseazaClienti(rez1,rezLength1);
    afiseazaClienti(rez2,rezLength2);
    afiseazaClienti(banca1,length1);
    #endif
    return 0;
}