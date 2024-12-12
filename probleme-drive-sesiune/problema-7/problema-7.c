#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FISIER_INTRARE "date_intrare.dat"
#define FISIER_IESIRE "rezultat.dat"

typedef struct
{

    char sir[40];
    int linie;

} Structura;

int functie(int v[], int n, int w[], int m, int rez[], int *p)
{
    *p = 0;
    int ok = 0;
    for (int i = 0; i < n; i++)
        if (v[i] > 0)
        {
            ok = 1;
            rez[*p] = i;
            (*p)++;
        }
    for (int i = 0; i < m; i++)
        if (w[i] == 0)
        {
            ok = 1;
            rez[*p] = i;
            (*p)++;
        }
    if (ok)
        return 1;
    else
        return 0;
}

// CREAM UN FISIER CA SA AVEM DE UNDE CITI CHESTII (FOR VERIFICATION PURPOSES)
void init()
{
    FILE *f;
    if ((f = fopen(FISIER_INTRARE, "wb")) == NULL)
    {
        puts("ERROR init(): nu s-a putut deschide fisierul date_intrare.dat!");
        exit(1);
    }
    int vectorAux[100] = {1, -3, -1, 4, 0, 6, 7, 0, -13, -1, 0, 5, 0, 0, 0, 0, -1, -2, 1, 2, 10, 120, 31, -13, -23, 0, -2, 0, 1, -54, 0, 0};
    fwrite(vectorAux, sizeof(int), 100, f);
    fclose(f);
}

int main()
{
    Structura vectorStructura[20];
    FILE *fisierIntrare;
    FILE *fisierRezultat;
    int vector1[20], vector2[20], vectorRezultat[40];
    int vector1Count, vector2Count, vectorRezultatCount, vectorStructuraCount = 0;
    init();
    printf("Introduceti numarul de elemente al primului vector: ");
    scanf("%d", &vector1Count);
    printf("Introduceti numarul de elemente al celui de-al doilea vector: ");
    scanf("%d", &vector2Count);

    if ((fisierIntrare = fopen(FISIER_INTRARE, "rb")) == NULL)
    {
        puts("Nu s-a putut deschide fisierul binar"
        FISIER_INTRARE);
        exit(1);
    }
    fread(vector1, sizeof(int), (size_t)vector1Count, fisierIntrare);
    fread(vector2, sizeof(int), (size_t)vector2Count, fisierIntrare);
    fclose(fisierIntrare);

    for (int i = 0; i < vector1Count; i++)
        printf("%d ", vector1[i]);
    printf("\n");
    for (int i = 0; i < vector2Count; i++)
        printf("%d ", vector2[i]);

    if (functie(vector1, vector1Count, vector2, vector2Count, vectorRezultat, &vectorRezultatCount))
    {
        printf("\nVECTORUL REZULTAT: ");
        for (int i = 0; i < vectorRezultatCount; i++)
            printf("%d ", vectorRezultat[i]);

        printf("\nNumar de elemente din vectorul rezultat: %d\n", vectorRezultatCount);
        unsigned int numarFisiere;
        printf("Introduceti cu cate fisiere doriti sa lucrati: ");
        scanf("%u", &numarFisiere);

        int ok = 0;

        for (unsigned i = 0; i < numarFisiere; i++)
        {
            printf("Introduceti numele fisierului %d: ", i + 1);
            char nume[20];
            scanf("%s", nume);
            if (strcmp(nume, "quit") == 0)
                exit(0);
            FILE *f;
            if ((f = fopen(nume, "r")) == NULL)
            {
                puts("Fisierul nu exista, incearca din nou: ");
                i--;
            }
            else
            {

                char aux[100] = "", sir[100];
                int poz = 0;

                for (int j = 0; j < vectorRezultatCount; j++)
                {
                    fgets(sir, 100, f);
                    sir[strlen(sir) - 1] = '\0';
                }
                for (int i = 0; i < vectorRezultatCount; i++)
                {
                    aux[poz] = sir[vectorRezultat[i]];
                    poz++;
                }
                aux[poz] = '\0';
                strcpy(vectorStructura[vectorStructuraCount].sir, aux);
                vectorStructura[vectorStructuraCount].linie = vectorRezultatCount;
                vectorStructuraCount++;
                ok = 1;
                fclose(f);
            }
        }
        if (ok)
        {
            if ((fisierRezultat = fopen(FISIER_IESIRE, "wb")) == NULL)
            {
                puts("Nu s-a putut deschide fisierul rezultat");
                exit(1);
            }
            fwrite(vectorStructura, sizeof(Structura), vectorStructuraCount, fisierRezultat);
            fclose(fisierRezultat);

            fisierRezultat = fopen(FISIER_IESIRE, "rb");
            for (int i = 0; i < vectorStructuraCount; i++)
            {
                Structura c;
                fread(&c, sizeof(Structura), 1, fisierRezultat);
                printf("Sir: %s\n", c.sir);
                printf("Linie: %d\n", c.linie);
            }
            fclose(fisierRezultat);
        }
    }
}