/*
    Se cere sa se scrie un program C care sa simuleze partial functionarea
    un cos de cumparaturi...
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FISIER_INTRARE "intrare.txt"
#define FISIER_PRODUSE "produse.dat"

typedef struct{
        char producator[50];
        int stoc;
        float pret;
    }Informatii;

typedef struct{
    char numeProdus[50];
    int cantitate;
    Informatii varianta[20];
}Produs;

// SIMULARE OBIECTE DIN PROGRAMAREA ORIENTATA PE OBIECT
void produs(Produs *produs, char numeProdus[],int cantitate,Informatii varianta[])
{
        strcpy(produs->numeProdus,numeProdus);
        produs->cantitate=cantitate;
        for(int i=0;i<cantitate;i++)
            {
                strcpy(produs->varianta[i].producator,varianta[i].producator);
                produs->varianta[i].stoc=varianta[i].stoc;
                produs->varianta[i].pret=varianta[i].pret;
            }
    }

// CREAM SI NOI NISTE PRODUSE IN MAGAZIN CA SA AVEM CE SA VERIFICAM
void init(Produs produse[],int cantitate)
{
    FILE *f;
    if((f=fopen(FISIER_PRODUSE,"wb"))==NULL)
        {
            puts("Nu s-a putut deschide fisierul"
            FISIER_PRODUSE);
            exit(1);
        }
    // SCRIEM IN FISIER PRODUSELE
    fwrite(produse,sizeof(Produs),(size_t)cantitate,f);
    fclose(f);
}

void citire(Produs produse[],int *n)
{
    printf("Cate produse? ");
    do{
      scanf("%d",n);
      if((*n)<=0||(*n)>5)
        puts("Introdu un numar natural nenul cel mult 5: ");  
    }while((*n)<=0||(*n)>5);
    
    getchar();
    for(int i=0;i<(*n);i++)
        {
            char numeProdus[50];
            int variante;
            printf("Introdu numele produsului: ");
            gets(numeProdus);
            printf("Introdu cate variante ale produsului sa fie:");
            do{
                scanf("%d",&variante);
                if(variante<=0||variante>3)
                    puts("Te rog sa introduci un numar natural nenul cel mult 3: ");
            }while(variante<=0||variante>3);
            getchar();
            Informatii info[3];
            printf("Acum introdu %d feluri diferite de %s:\n",variante,numeProdus);
            for(int j=0;j<variante;j++)
            {
                char producator[50];
                int stoc;
                float pret;
                printf("Varianta %d:\nProducator: ",j+1);
                gets(producator);
                strcpy(info[j].producator,producator);
                printf("Stoc: ");
                scanf("%d",&stoc);
                info[j].stoc=stoc;
                printf("Pret: ");
                scanf("%f",&pret);
                info[j].pret=pret;
                getchar();
            }
            produs(&produse[i],numeProdus,variante,info);            
        }
    init(produse,*n);
}

int main()
{
    Produs produse[5];
    int nr_produse;

    citire(produse,&nr_produse);

    FILE *f;
    if((f=fopen(FISIER_PRODUSE,"rb"))==NULL)
        {
            puts("Eroare deschidere citire fisier cu produse!");
            exit(1);
        }
    printf("\n==============AFISARE PRODUSE==============\n");
    for(int i=0;i<nr_produse;i++)
    {
        Produs p;
        fread(&p,sizeof(Produs),1,f);
        printf("Produsul numarul %d:{\n",i+1);
        printf("Nume produs: %s\nTipuri de %s: %d\n",p.numeProdus,p.numeProdus,p.cantitate);
        for(int j=0;j<p.cantitate;j++)
            {
                printf("Tipul %d:{\nProducator: %s\nStoc: %d\nPret: %.2f\n}",j+1,p.varianta[j].producator,p.varianta[j].stoc,p.varianta[j].pret);
            }
        printf("\n");
    }

    return 0;
}