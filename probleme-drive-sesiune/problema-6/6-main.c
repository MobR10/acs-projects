/*
    LINK PROBLEMA: https://drive.google.com/drive/folders/1mgqIIkUzDtEcTsVToa0VqFxMn57ElctD
    FOLOSESTE-TE DE VARIABILA DEBUG PENTRU VERIFIFCARE
    ATENTIE LA VARIABILA PENTRU NUMARUL DE COMPONENTE PENTRU PERSOANE, DACA SCHIMBI NUMARUL SI RULEZI PROGRAMUL CU DEBUG PE ON, APAR PROBLEME IN FISIERUL BINAR
    DACA IGNORI TOATE DEFINE-URILE SI LOCURILE UNDE APAR "#IF ... #ENDIF", ATUNCI AIA E REZOLVAREA PROBLEMEI LA EXAMEN
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMAR_COMPONENTE_DIN_FISIERUL_BINAR 4
#define CREARE_FISIER_BINAR 0
#define DEBUG 0

typedef struct
{
    char nume[50];
    int varsta;
    char informatie[50];
} Persoana;

#if DEBUG == 1
void creareFisierBinar()
{
    FILE *f;
    if ((f = fopen("fisierBinar.dat", "wb")) == NULL)
    {
        puts("Eroare creare fisier binar");
        exit(1);
    }
    Persoana persoane[NUMAR_COMPONENTE_DIN_FISIERUL_BINAR];
    printf("Introdu %d persoane: \n", NUMAR_COMPONENTE_DIN_FISIERUL_BINAR);
    for (int i = 0; i < NUMAR_COMPONENTE_DIN_FISIERUL_BINAR; i++)
    {
        printf("Persoana cu numarul %d:\n", i + 1);
        printf("Introdu numele persoanei (maxim 50 caractere pls!): ");
        fgets(persoane[i].nume, 50, stdin);
        persoane[i].nume[strlen(persoane[i].nume) - 1] = '\0';
        printf("Introdu varsta persoanei: ");
        scanf("%d", &persoane[i].varsta);
        getchar();
        strcpy(persoane[i].informatie, "");
    }
    fwrite(persoane, sizeof(Persoana), NUMAR_COMPONENTE_DIN_FISIERUL_BINAR, f);
    fclose(f);
}

void initPersoane()
{
    FILE *f;
    if ((f = fopen("fisierBinar.dat", "rb")) == NULL)
    {
        puts("Eroare la deschiderea fisierului binar pentru citire in functia de initializare!");
        exit(1);
    }
    Persoana persoane[NUMAR_COMPONENTE_DIN_FISIERUL_BINAR];
    fread(persoane, sizeof(Persoana), NUMAR_COMPONENTE_DIN_FISIERUL_BINAR, f);
    for (int i = 0; i < NUMAR_COMPONENTE_DIN_FISIERUL_BINAR; i++)
        strcpy(persoane[i].informatie, "");
    fclose(f);
    if ((f = fopen("fisierBinar.dat", "wb")) == NULL)
    {
        puts("Eroare la deschiderea fisierului binar pentru scriere in functia de initializare!");
        exit(1);
    }
    fwrite(persoane, sizeof(Persoana), NUMAR_COMPONENTE_DIN_FISIERUL_BINAR, f);
    fclose(f);
}
#endif

int functie(int v[], int lungime)
{
    for (int i = lungime - 1; i >= 0; i--)
    {
        int ok = 1;
        for (int j = lungime; j >= 0; j--)
        {
            if (v[i] == v[j] && i != j)
            {
                ok = 0;
                j = 0;
            }
        }
        if (ok == 1 && v[i] < 0)
            return -v[i];
        else if (ok)
        {
            return v[i];
        }
    }
    return -1;
}

int main()
{
#if CREARE_FISIER_BINAR == 1
    creareFisierBinar();
#endif

#if DEBUG == 1
    initPersoane();
#endif

    FILE *fisierText, *fisierBinar;
    if ((fisierText = fopen("fisierText.txt", "r")) == NULL)
    {
        puts("Eroare la deschiderea fisierului text pentru citire");
        exit(1);
    }
    if ((fisierBinar = fopen("fisierBinar.dat", "rb+")) == NULL)
    {
        puts("Eroare la deschiderea fisierului binar pentru citire");
        exit(1);
    }

#if DEBUG == 1
    puts("AFISARE PERSOANE:");
    Persoana persoane[NUMAR_COMPONENTE_DIN_FISIERUL_BINAR];
    fread(persoane, sizeof(Persoana), NUMAR_COMPONENTE_DIN_FISIERUL_BINAR, fisierBinar);
    for (int i = 0; i < NUMAR_COMPONENTE_DIN_FISIERUL_BINAR; i++)
    {
        printf("Persoana numarul %d:\n", i + 1);
        printf("Nume: %s\n", persoane[i].nume);
        printf("Varsta: %d\n", persoane[i].varsta);
        printf("Informatie: %s\n\n", persoane[i].informatie);
    }
    fseek(fisierBinar, 0L, SEEK_SET);
#endif

    int v[10], lungime, numarPersoane;
    fseek(fisierBinar, 0L, SEEK_END);
    numarPersoane = (int)(ftell(fisierBinar) / sizeof(Persoana));
    while (!feof(fisierText))
    {
        fscanf(fisierText, "%d", &lungime);
        for (int i = 0; i < lungime; i++)
            fscanf(fisierText, "%d", &v[i]);
        int valoare = functie(v, lungime);

#if DEBUG == 1
        puts("\nAFISARE VECTORI DE NUMERE SI VALOAREA RETURNATA DE FUNCTIE:");
        for (int i = 0; i < lungime; i++)
            printf("%d ", v[i]);
        printf("\nValoarea returnata de functie: %d\n", valoare);
#endif

        fseek(fisierBinar, (long)((valoare - 1) * sizeof(Persoana)), SEEK_SET);
        if (valoare > numarPersoane)
        {
#if DEBUG == 1
            puts("Valoarea trece peste limita fisierului.");
#endif
        }
        else
        {
            Persoana persoana;
            fread(&persoana, sizeof(Persoana), 1, fisierBinar);
            if (strcmp(persoana.nume + strlen(persoana.nume) - 2, "in") == 0 && strchr(persoana.nume, 'c') != 0 && persoana.varsta == 18)
                strcpy(persoana.informatie, "verificat");

#if DEBUG == 1
            printf("\nPERSOANA CURENTA DE LA POZITIA %d:\n", valoare);
            printf("NUME: %s\n", persoana.nume);
            printf("VARSTA: %d\n", persoana.varsta);
            printf("INFORMATIE: %s\n", persoana.informatie);
#endif

            fseek(fisierBinar, (long)((valoare - 1) * sizeof(Persoana)), SEEK_SET);
            fwrite(&persoana, sizeof(Persoana), 1, fisierBinar);
        }
    }

    fclose(fisierBinar);
    fclose(fisierText);

#if DEBUG == 1
    if ((fisierBinar = fopen("fisierBinar.dat", "rb")) == NULL)
    {
        puts("Eroare la deschiderea fisierului binar pentru citire");
        exit(1);
    }
    fread(persoane, sizeof(Persoana), NUMAR_COMPONENTE_DIN_FISIERUL_BINAR, fisierBinar);
    puts("\nAFISARE PERSOANE:");
    for (int i = 0; i < NUMAR_COMPONENTE_DIN_FISIERUL_BINAR; i++)
    {
        printf("Persoana numarul %d:\n", i + 1);
        printf("Nume: %s\n", persoane[i].nume);
        printf("Varsta: %d\n", persoane[i].varsta);
        printf("Informatie: %s\n\n", persoane[i].informatie);
    }
    fclose(fisierBinar);
#endif

return 0;
}