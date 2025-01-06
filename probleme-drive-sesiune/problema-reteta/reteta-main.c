#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

typedef struct
{
    char denumire[50];
    float cantitate;
} Ingredient;

int esteInLista(Ingredient lista[15], int lungime, char *denumire)
{
    for (int i = 0; i < lungime; i++)
        if (strcmp(lista[i].denumire, denumire) == 0)
            return i;
    return -1;
}
void citesteRetete(Ingredient lista[], int *lungime)
{
    // CITIRE DE LA TASTATURA
    int numarRetete;
    *lungime = 0;
    printf("Cate retete doriti sa introduceti? (nr. nat. nenul <5):");
    do
    {
        scanf("%d", &numarRetete);
        getchar();
        if (numarRetete <= 0 || numarRetete >= 5)
            printf("Introduceti un numar natural nenul mai mic decat 5!");
    } while (numarRetete <= 0 || numarRetete >= 5);
    printf("Acum introduceti ingredientele fiecarei retete dupa formatul <denumire> <cantitate>.\n"
           "Daca doriti sa introduceti mai multe ingrediente, apasati doar <ENTER> la final, fara spatii.\n"
           "Daca doriti sa introduceti mai multe retete, le despartiti printr-un '-'\n");
    int i, j, pos;
    char denumire[50], temp[50];
    float cantitate;
    for (i = 0; i < numarRetete; i++)
    {
        printf("Reteta numarul %d:\n", i + 1);
        j = 1;
        while (j)
        {
            printf("Ingredientul %d: ", j);
            scanf("%s", denumire);
            scanf("%f", &cantitate);
            if ((pos = esteInLista(lista, *lungime, denumire)) != -1)
                lista[pos].cantitate += cantitate;
            else
            {
                strcpy(lista[*lungime].denumire, denumire);
                lista[*lungime].cantitate = cantitate;
                (*lungime)++;
            }
            int ok = 1;
            do
            {
                gets(temp);
                getchar();
                puts(temp);
            } while (strlen(temp) != 1);
        }
    }
}

int existaAvertizari(int lungime)
{
    if (lungime)
        return 1;
    return 0;
}

int functie(Ingredient listaCamara[15], int lungimeCamara, Ingredient listaNecesare[15], int lungimeNecesare, char listaAvertizare[][50], int *lungimeAvertizare, Ingredient listaCumparaturi[15], int *lungimeCumparaturi)
{
    FILE *camara;
    if ((camara = fopen("camara.dat", "wb")) == NULL)
    {
        puts("Eroare la deschiderea fisierului camara.dat in 'functie'!");
        exit(1);
    }
    *lungimeAvertizare = 0;
    *lungimeCumparaturi = 0;
    int pos, toateIngredientele = 1;
    for (int i = 0; i < lungimeNecesare; i++)
    {
        pos = esteInLista(listaCamara, lungimeCamara, listaNecesare[i].denumire);
        if (pos != 1 && listaCamara[pos].cantitate > listaNecesare[i].cantitate)
        {
            listaCamara[pos].cantitate -= listaNecesare[i].cantitate;
            fwrite(listaCamara, sizeof(Ingredient), (long)lungimeCamara, camara);
            fseek(camara, 0L, SEEK_SET);
        }
        else if (pos != 1 && listaCamara[pos].cantitate == listaNecesare[i].cantitate)
        {
            for (int j = pos; j < lungimeCamara - 1; j++)
                listaCamara[j] = listaCamara[j + 1];
            lungimeCamara--;
            fwrite(listaCamara, sizeof(Ingredient), (long)lungimeCamara, camara);
            fseek(camara, 0L, SEEK_SET);
            strcpy(listaAvertizare[*lungimeAvertizare], listaCamara[pos].denumire);
            (*lungimeAvertizare)++;
        }
        else
        {
            listaCumparaturi[*lungimeCumparaturi] = listaNecesare[i];
            (*lungimeCumparaturi)++;
            toateIngredientele = 0;
        }
    }
    fclose(camara);
    return toateIngredientele;
}

#if DEBUG == 1
void afiseazaLista(Ingredient v[], int lungime)
{
    for (int i = 0; i < lungime; i++)
    {
        printf("Denumire: %s\n", v[i].denumire);
        printf("Cantitate: %f\n", v[i].cantitate);
    }
}
#endif

int main()
{
    // AFLAM CATE INGREDIENTE EXISTA SI LE PUNEM INTR-UN ARRAY
    Ingredient listaCamara[15], listaNecesare[15], listaCumparaturi[15];
    char listaAvertizare[15][50];
    int lungimeCamara, lungimeNecesare = 0, lungimeAvertizare, lungimeCumparaturi;

    citesteRetete(listaNecesare, &lungimeNecesare);

    FILE *camara;
    if ((camara = fopen("camara.dat", "rb")) == NULL)
    {
        puts("Eroare la deschiderea camarii!");
        exit(1);
    }
    else
    {
        fseek(camara, 0L, SEEK_END);
        lungimeCamara = (int)(ftell(camara) / sizeof(Ingredient));
        fread(listaCamara, sizeof(Ingredient), lungimeCamara, camara);
    }

    if (functie(listaCamara, lungimeCamara, listaNecesare, lungimeNecesare, listaAvertizare, &lungimeAvertizare, listaCumparaturi, &lungimeCumparaturi))
        printf("Bucatarul se poate apuca de meniu");
    if (existaAvertizari(lungimeAvertizare))
        printf("Exista avertizari");
}