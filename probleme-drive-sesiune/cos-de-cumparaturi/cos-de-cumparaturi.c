/*
    Se cere sa se scrie un program C care sa simuleze partial functionarea
    un cos de cumparaturi...
    https://drive.google.com/drive/folders/1mgqIIkUzDtEcTsVToa0VqFxMn57ElctD
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FISIER_INTRARE "intrare.txt"
#define FISIER_PRODUSE "produse.dat"

typedef struct
{
    char producator[50];
    int stoc;
    float pret;
} Produs;

typedef struct
{
    char numeProdus[50];
    int numarProduse;
    Produs produs[20];
} TipProdus;

// SIMULARE OBIECTE DIN POO
void constructTipProdus(TipProdus *tipProdus, char numeProdus[], int numarProduse, Produs produs[])
{
    strcpy(tipProdus->numeProdus, numeProdus);
    tipProdus->numarProduse = numarProduse;
    for (int i = 0; i < numarProduse; i++)
    {
        strcpy(tipProdus->produs[i].producator, produs[i].producator);
        tipProdus->produs[i].stoc = produs[i].stoc;
        tipProdus->produs[i].pret = produs[i].pret;
    }
}

// CREAM SI NOI NISTE PRODUSE IN MAGAZIN CA SA AVEM CE SA VERIFICAM
void init(TipProdus tipProdus[], int numarTipProduse)
{
    FILE *f;
    if ((f = fopen(FISIER_PRODUSE, "wb")) == NULL)
    {
        puts("Eroare deschidere fisier " FISIER_PRODUSE " in functia init() ");
        exit(1);
    }
    // SCRIEM IN FISIER PRODUSELE
    fwrite(tipProdus, sizeof(TipProdus), (size_t)numarTipProduse, f);
    fclose(f);
}

void citire(TipProdus tipProdus[], int *numarTipProduse)
{
    printf("Cate tipuri de produse? ");
    do
    {
        scanf("%d", numarTipProduse);
        if ((*numarTipProduse) <= 0 || (*numarTipProduse) > 5)
            puts("Introdu un numar natural nenul cel mult 5: ");
    } while ((*numarTipProduse) <= 0 || (*numarTipProduse) > 5);

    getchar();
    for (int i = 0; i < (*numarTipProduse); i++)
    {
        char numeProdus[50];
        int numarProduse;
        printf("Introdu numele tipului de produs: ");
        gets(numeProdus);
        printf("Introdu cate variante ale produsului sa fie:");
        do
        {
            scanf("%d", &numarProduse);
            if (numarProduse <= 0 || numarProduse > 3)
                puts("Te rog sa introduci un numar natural nenul cel mult 3: ");
        } while (numarProduse <= 0 || numarProduse > 3);
        getchar();
        Produs produs[3];
        printf("Acum introdu %d variante diferite de %s:\n", numarProduse, numeProdus);
        for (int j = 0; j < numarProduse; j++)
        {
            char producator[50];
            int stoc;
            float pret;
            printf("Varianta %d:\nProducator: ", j + 1);
            gets(producator);
            strcpy(produs[j].producator, producator);
            printf("Stoc: ");
            scanf("%d", &stoc);
            produs[j].stoc = stoc;
            printf("Pret: ");
            scanf("%f", &pret);
            produs[j].pret = pret;
            getchar();
        }
        constructTipProdus(&tipProdus[i], numeProdus, numarProduse, produs);
    }
    init(tipProdus, *numarTipProduse);
}

void sortProduseDupaCantitate(TipProdus *tipProdus)
{
    Produs *produs = tipProdus->produs;
    for (int i = 0; i < tipProdus->numarProduse - 1; i++)
    {
        for (int j = i + 1; j < tipProdus->numarProduse; j++)
        {
            if (produs[i].stoc > produs[j].stoc)
            {
                Produs aux = produs[i];
                produs[i] = produs[j];
                produs[j] = aux;
            }
        }
    }
}

int main()

{
    int numarTipProduse;
    TipProdus tipProdus[5];
    /*
    PRODUSE.DAT ESTE FISIERUL CU INFORMATIILE DESPRE PRODUSELE DIN MAGAZIN. DEJA ARE PRODUSELE INAUNTRU, NU E NEVOIE SA CITITI DE LA 0, DECAT DACA VREI! RECOMAND COPIEREA FISIERULUI INAINTE DE ASTA!
    AICI E ZONA DE INITIALIZARE A PRODUSELOR DIN MAGAZIN. LA EXAMEN NU VEI AVEA NICIUN FISIER CU DATE DIN CARE SA PREIEI INFORMATIA CARE TI SE CERE IN ENUNT, CI TU TREBUIE SA REZOLVI CA SI CAND ELE AR EXISTA, DAR FARA SA COMPILEZI, EVIDENT, PENTRU CA ITI VA DA ORICUM EROARE
    DACA NU II DAI NISTE DATE SA PRELUCREZE. IN CEL MAI FERICIT CAZ, DACA TERMINI ALGORITMUL SI MAI AI TIMP, POTI DA FACE SCURT NISTE DATE DE INTRARE CA SA PROBEZI CORECTITUDINEA REZULTATULUI, DAR NU PIERDE TIMPUL PE ASA CEVA, CA NICI MACAR NU SE PUNCTEAZA COMPILAREA!!!
    IN EXAMEN NU TREBUIE COMPILAT PROGRAMUL, CI CONTEAZA SA SCRII CAT MAI CORECT SI LOGIC ALGORITMUL FARA A MAI COMPILA, DAR ACUM POTI SA SI TESTEZI CUM MERGE PROGRAMUL!
    */

    // UNCOMMENT PENTRU A SCHIMBA LISTA DE PRODUSE DIN MAGAZIN (CITESTE FIECARE PRODUS DE LA TASTATURA
    // citire(tipProdus,&numarTipProduse);

    // CITIRE PRODUSE DIN PRODUSE.DAT SI AMPLASAREA LOR IN VECTORUL CU PRODUSE
    FILE *f;
    if ((f = fopen(FISIER_PRODUSE, "rb")) == NULL)
    {
        puts("Eroare deschidere citire fisier cu produse!");
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    numarTipProduse = ftell(f) / sizeof(TipProdus);
    fseek(f, 0, SEEK_SET);
    fread(tipProdus, sizeof(TipProdus), numarTipProduse, f);
    fclose(f);

    // FOR TESTING PURPOSES ONLY, DACA NU AFISEAZA CORECT DUPA O NOUA CITIRE, IT'S YOUR FAULT!
     printf("\n==============AFISARE PRODUSE==============\n");
     for(int i=0;i<numarTipProduse;i++)
     {
         printf("Produsul numarul %d:{\n",i+1);
         printf("Nume produs: %s\nTipuri de %s: %d\n",tipProdus[i].numeProdus,tipProdus[i].numeProdus,tipProdus[i].numarProduse);
         for(int j=0;j<tipProdus[i].numarProduse;j++)
             {
                 printf("Tipul %d:{\nProducator: %s\nStoc: %d\nPret: %.2f\n}",j+1,tipProdus[i].produs[j].producator,tipProdus[i].produs[j].stoc,tipProdus[i].produs[j].pret);
             }
         printf("\n");
     }

    return 0;
}