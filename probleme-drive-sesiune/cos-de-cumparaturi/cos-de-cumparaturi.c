/*
    Se cere sa se scrie un program C care sa simuleze partial functionarea
    un cos de cumparaturi...
    https://drive.google.com/drive/folders/1mgqIIkUzDtEcTsVToa0VqFxMn57ElctD
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define FISIER_LISTA "lista-cumparaturi.txt"
#define FISIER_PRODUSE "produse.dat"
#define FISIER_BON "bon.dat"

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

// SUPLIMENTAR !!!! NU E IN CERINTA
//==================================================
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

void citire(int *numarTipProduse)
{
    TipProdus tipProdus[5];
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
//==================================================

// PUNCTUL a)
//++++++++++++++++++++++++++++++++++++++++++++
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
//++++++++++++++++++++++++++++++++++++++++++++

// PUNCTUL b)
//++++++++++++++++++++++++++++++++++++++++++++
Produs* cauta_produs(char denumire[],int cantitateDorita,TipProdus tipProdus[],int numarTipProduse)
{
    Produs *produs=NULL;
    for(int i=0;i<numarTipProduse;i++)
        {
            if(stricmp(denumire,tipProdus[i].numeProdus)==0)
                {
                    sortProduseDupaCantitate(&tipProdus[i]);
                    float pretMinim=99999;
                    for(int j=tipProdus[i].numarProduse-1;j>=0;j--)
                    {
                        if(cantitateDorita<=tipProdus[i].produs[j].stoc&&tipProdus[i].produs[j].pret<pretMinim)
                            {
                                pretMinim=tipProdus[i].produs[j].pret;
                                produs=&tipProdus[i].produs[j];
                            }
                    }
                }
        }
    return produs;
}
//++++++++++++++++++++++++++++++++++++++++++++

int main()
{
    int numarTipProduse;
    TipProdus tipProdus[5];
    // SUPLIMENTAR !! NU APARE IN CERINTA!
    //==================================================
    /*
    PRODUSE.DAT ESTE FISIERUL CU INFORMATIILE DESPRE PRODUSELE DIN MAGAZIN. DEJA ARE PRODUSELE INAUNTRU, NU E NEVOIE SA CITESTI DE LA 0, DECAT DACA VREI! RECOMAND COPIEREA FISIERULUI INAINTE DE ASTA!
    AICI E ZONA DE INITIALIZARE A PRODUSELOR DIN MAGAZIN. LA EXAMEN NU VEI AVEA NICIUN FISIER CU DATE DIN CARE SA PREIEI INFORMATIA CARE TI SE CERE IN ENUNT, CI TU TREBUIE SA REZOLVI CA SI CAND ELE AR EXISTA, DAR FARA SA COMPILEZI, EVIDENT, PENTRU CA ITI VA DA ORICUM EROARE
    DACA NU II DAI NISTE DATE SA PRELUCREZE. IN CEL MAI FERICIT CAZ, DACA TERMINI ALGORITMUL SI MAI AI TIMP, POTI FACE SCURT NISTE DATE DE INTRARE CA SA PROBEZI CORECTITUDINEA REZULTATULUI, DAR NU PIERDE TIMPUL PE ASA CEVA, CA NICI MACAR NU SE PUNCTEAZA COMPILAREA!!!
    IN EXAMEN NU TREBUIE COMPILAT PROGRAMUL, CI CONTEAZA SA SCRII CAT MAI CORECT SI LOGIC ALGORITMUL FARA A MAI COMPILA, DAR AICI POTI SA SI TESTEZI CUM MERGE PROGRAMUL!
    */

    // UNCOMMENT PENTRU A SCHIMBA LISTA DE PRODUSE DIN MAGAZIN (CITESTE FIECARE PRODUS DE LA TASTATURA)
    // citire(&numarTipProduse);

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
    //==================================================

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

    // PUNCTUL C) 
    FILE *fisierBon,*fisierLista;
    if((fisierBon=fopen(FISIER_BON,"wb"))==NULL)
        {
            puts("Eroare deschidere scriere fisier bon!");
            exit(1);
        }
    if((fisierLista=fopen(FISIER_LISTA,"rt"))==NULL)
        {
            puts("Eroare deschidere citire fisier lista-cumparaturi!");
            exit(1);
        }
    float total=0.;
    int counter=0;
    while(!feof(fisierLista))
    {
        Produs *produs;
        char nume[50],*p,*q,sir[100];
        int cantitateDorita;
        strcpy(nume,"");
        fgets(sir,100,fisierLista);
        if(!feof(fisierLista))
        sir[strlen(sir)-1]='\0'; // pentru ca fgets pune si ENTER-ul in sir. dar la ultimul rand nu mai exista ENTER, deci as pierde ultimul caracter din ultimul rand!
        p=strtok(sir," ");
        q=p;
        q=strtok(NULL," ");
        while(q)
        {
            if(('a'<=p[0]&&p[0]<='z') ||('A'<=p[0] && p[0]<='Z'))
                {
                    strcat(nume,p);
                    if(!('0'<=q[0]&&q[0]<='9'))
                    strcat(nume," ");
                    
                }
            if('0'<=q[0]&&q[0]<='9')
                cantitateDorita=atoi(q);
            p=q;
            q=strtok(NULL," ");
        }
        produs=cauta_produs(nume,cantitateDorita,tipProdus,numarTipProduse);
        if(produs)
        {
            int parteIntreaga=(int)floor(cantitateDorita*produs->pret);
            int parteFractionara=(int)(ceil(cantitateDorita*produs->pret)-floor(cantitateDorita*produs->pret));
            counter++;   
            total+=(float)(cantitateDorita*(produs->pret));
            fwrite(nume,sizeof(char),strlen(nume),fisierBon);
            fwrite(" ",sizeof(char),1,fisierBon);
            fwrite(produs->producator,sizeof(char),strlen(produs->producator),fisierBon);
            fwrite(" ",sizeof(char),1,fisierBon);
            fwrite(&cantitateDorita,sizeof(int),1,fisierBon);
            fwrite(" ",sizeof(char),1,fisierBon);
            fwrite(&parteIntreaga,sizeof(int),1,fisierBon);
            fwrite(",",sizeof(char),1,fisierBon);
            fwrite(&parteFractionara,sizeof(int),1,fisierBon);
            fwrite("\n",sizeof(char),1,fisierBon);

        }
        else
        {
            printf("Magazinul nu are destul %s sau nu are deloc. Doriti sa mai continuati cumparaturile sau nu? (Y/N)",nume);
            char c;
            c=getchar();
            getchar();
            switch(c){
                case 'N': 
                puts("La revedere!");
                while(!feof(fisierLista))
                {
                    fgetc(fisierLista);
                }
                getchar();
                break;
                case 'n':
                puts("La revedere!");
                while(!feof(fisierLista))
                {
                    fgetc(fisierLista);
                }
                getchar();
                break;
                case 'Y': break;
                case 'y': break;
                default: puts("Introduceti doar \"Y\" sau \"N\"!"); c=getchar();
            }
        }
        
    }
    fwrite(&total,sizeof(float),1,fisierBon);
    fclose(fisierBon);
    fclose(fisierLista);
    
    fisierBon=fopen(FISIER_BON,"rb");
    for(int i=0;i<counter;i++)
    {
        char s[200];
        fgets(s,200,fisierBon);
        s[strlen(s)-1]='\0';
        puts(s);
    }
        float tot;
        fread(&tot,sizeof(float),1,fisierBon);
        printf("%.2f",tot);
    
    fclose(fisierBon);
    return 0;
}