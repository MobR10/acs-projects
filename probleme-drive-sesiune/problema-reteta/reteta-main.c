#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CHESTII DE DEBUG
#define DEBUG 0
#define CREEAZA_CAMARA 0
//===============

// ASTA NU E DEBUG
typedef struct
{
    char denumire[50];
    float cantitate;
} Ingredient;
//================

// MORE DEBUG
#if DEBUG == 1
void afiseazaLista(Ingredient v[], int lungime)
{
    for (int i = 0; i < lungime; i++)
    {
        printf("Ingredientul %d:\nDenumire: %s\n", i + 1, v[i].denumire);
        printf("Cantitate: %.2f\n", v[i].cantitate);
    }
}

void afiseazaCamara()
{
    FILE *camara;
    if ((camara = fopen("camara.dat", "rb")) == NULL)
    {
        puts("Eroare la creearea fisierului camara.dat in functia creeazaCamara");
        exit(1);
    }
    puts("\nafiseazaCamara()\n");
    Ingredient lista[15];
    int lungime;
    fseek(camara, 0L, SEEK_END);
    lungime = (int)(ftell(camara) / (long)sizeof(Ingredient));
    fseek(camara, 0L, SEEK_SET);
    fread(lista, sizeof(Ingredient), (size_t)lungime, camara);
    afiseazaLista(lista, lungime);
    fclose(camara);
    puts("\nSFARSIT\n");
}
#endif

#if CREEAZA_CAMARA == 1
void creeazaCamara()
{
    FILE *camara;
    if ((camara = fopen("camara.dat", "wb")) == NULL)
    {
        puts("Eroare la creearea fisierului camara.dat in functia creeazaCamara");
        exit(1);
    }

    puts("\ncreeazaCamara()\n");
    Ingredient lista[15];
    char denumire[50], aux[50], c;
    float cantitate;
    int j = 1, lungime, pos;
    while (j)
    {
        printf("Ingredientul %d: ", j);
        if ((c = getchar()) == '-')
        {
            getchar();
            j = 0;
        }
        else
        {
            scanf("%s", denumire);
            scanf("%f", &cantitate);
            getchar();
            strcpy(aux, denumire);
            strcpy(denumire + 1, aux);
            denumire[0] = c;

            if ((pos = esteInLista(lista, lungime, denumire)) != -1)
            {
                lista[pos].cantitate += cantitate;
            }
            else
            {
                strcpy(lista[lungime].denumire, denumire);
                lista[lungime].cantitate = cantitate;
                lungime++;
            }
            j++;
        }
    }
    fwrite(lista, sizeof(Ingredient), lungime, camara);
    fclose(camara);
    puts("\nSFARSIT APEL\n");
}
#endif
//========================

int esteInLista(Ingredient lista[15], int lungime, char *denumire)
{
    for (int i = 0; i < lungime; i++)
        if (strcmp(lista[i].denumire, denumire) == 0)
            return i;
    return -1;
}

void citesteReteteTastatura(Ingredient lista[], int *lungime)
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
    printf("\nAcum introduceti ingredientele fiecarei retete dupa formatul <denumire> <cantitate>.\n"
           "Daca doriti sa introduceti mai multe ingrediente, apasati doar <ENTER> la final, fara spatii.\n"
           "Daca doriti sa introduceti mai multe retete, le despartiti printr-un '-'\n");
    int i, j, pos;
    char denumire[50], aux[50], c;
    float cantitate;
    for (i = 0; i < numarRetete; i++)
    {
        printf("Reteta numarul %d:\n", i + 1);
        j = 1;
        while (j)
        {
            printf("Ingredientul %d: ", j);
            if ((c = getchar()) == '-')
            {
                getchar();
                j = 0;
            }
            else
            {
                scanf("%s", denumire);
                scanf("%f", &cantitate);
                getchar();
                strcpy(aux, denumire);
                strcpy(denumire + 1, aux);
                denumire[0] = c;

                if ((pos = esteInLista(lista, *lungime, denumire)) != -1)
                {
                    lista[pos].cantitate += cantitate;
                }
                else
                {
                    strcpy(lista[*lungime].denumire, denumire);
                    lista[*lungime].cantitate = cantitate;
                    (*lungime)++;
                }

                j++;
            }
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
    *lungimeAvertizare = 0;
    *lungimeCumparaturi = 0;
    int pos, toateIngredientele = 1;
    for (int i = 0; i < lungimeNecesare; i++)
    {
        pos = esteInLista(listaCamara, lungimeCamara, listaNecesare[i].denumire);
        if (pos != -1 && listaCamara[pos].cantitate > listaNecesare[i].cantitate)
        {
            FILE *camara;
            if ((camara = fopen("camara.dat", "wb")) == NULL)
            {
                puts("Eroare la deschiderea fisierului camara.dat in 'functie'! (primul if)");
                exit(1);
            }
            listaCamara[pos].cantitate -= listaNecesare[i].cantitate;
            fwrite(listaCamara, sizeof(Ingredient), (size_t)lungimeCamara, camara);
            fclose(camara);
        }
        else if (pos != -1 && listaCamara[pos].cantitate == listaNecesare[i].cantitate)
        {
            FILE *camara;
            if ((camara = fopen("camara.dat", "wb")) == NULL)
            {
                puts("Eroare la deschiderea fisierului camara.dat in 'functie' (al doilea else if)!");
                exit(1);
            }
            strcpy(listaAvertizare[*lungimeAvertizare], listaCamara[pos].denumire);
            (*lungimeAvertizare)++;
            for (int j = pos; j < lungimeCamara - 1; j++)
                listaCamara[j] = listaCamara[j + 1];
            lungimeCamara--;
            fwrite(listaCamara, sizeof(Ingredient), (size_t)lungimeCamara, camara);
            fclose(camara);
        }
        else
        {
            listaCumparaturi[*lungimeCumparaturi] = listaNecesare[i];
            if (pos != 1)
                listaCumparaturi[*lungimeCumparaturi].cantitate = listaNecesare[i].cantitate - listaCamara[pos].cantitate;
            else
                listaCumparaturi[*lungimeCumparaturi].cantitate = listaNecesare[i].cantitate;
            (*lungimeCumparaturi)++;
            toateIngredientele = 0;
        }
    }
    return toateIngredientele;
}

int main()
{
#if CREEAZA_CAMARA == 1
    creeazaCamara();
#endif

#if DEBUG == 1
    afiseazaCamara();
#endif

    Ingredient listaCamara[15], listaNecesare[15], listaCumparaturi[15], recuperare[15];
    char listaAvertizare[15][50];
    int lungimeCamara, lungimeNecesare = 0, lungimeAvertizare, lungimeCumparaturi, lungimeRecuperare;

    // CITIRE RETETE (TASTATURA/FISIER TEXT)
    citesteReteteTastatura(listaNecesare, &lungimeNecesare);

#if DEBUG == 1
    puts("\nAFISARE INGREDIENTE NECESARE\n");
    afiseazaLista(listaNecesare, lungimeNecesare);
    puts("\nSFARSIT\n");
#endif

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
        fseek(camara, 0L, SEEK_SET);
        fread(listaCamara, sizeof(Ingredient), lungimeCamara, camara);

        //OPTIONAL (ignore it. e pt debug)
        fseek(camara, 0L, SEEK_SET);
        lungimeRecuperare = lungimeCamara;
        fread(recuperare, sizeof(Ingredient), lungimeRecuperare, camara);
    }
    fclose(camara);

    if (functie(listaCamara, lungimeCamara, listaNecesare, lungimeNecesare, listaAvertizare, &lungimeAvertizare, listaCumparaturi, &lungimeCumparaturi))
        printf("Bucatarul se poate apuca de meniu");
    else
        printf("Bucatarul nu are toate ingredientele");
    if (existaAvertizari(lungimeAvertizare))
        printf("Exista avertizari");

#if DEBUG == 1

    puts("\nAFISARE LISTA AVERTIZARE\n");
    for (int i = 0; i < lungimeAvertizare; i++)
        puts(listaAvertizare[i]);
    puts("\nSFARSIT\n");

    puts("\nAFISARE LISTA CUMPARATURI\n");
    afiseazaLista(listaCumparaturi, lungimeCumparaturi);
    puts("\nSFARSIT\n");

    puts("\nAFISARE CAMARA PENTRU A VEDEA DIFERENTELE\n");
    afiseazaCamara();
#endif

    // OPTIONAL (ignore this)
    camara = fopen("camara.dat", "wb");
    fwrite(recuperare, sizeof(Ingredient), lungimeRecuperare, camara);
    fclose(camara);

#if DEBUG == 1
    puts("REINITIALIZARE CAMARA SI AFISARE");
    afiseazaCamara();
#endif
}