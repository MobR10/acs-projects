#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// REZOLVARE PUNCT A
void functieA2(char *numeFisier, int linie, int numarLinii, FILE *fisierRezultat)
{
    FILE *fisier;
    if (!(fisier = fopen(numeFisier, "rt")))
    {
        printf("Nu exista fisierul %s", numeFisier);
    }
    else
    {
        int i = 1;
        char buffer[1000];
        while (i < linie && !feof(fisier))
        {
            fgets(buffer, 1000, fisier);
            i++;
        }
        i = 1;
        while (i <= numarLinii && !feof(fisier))
        {
            fgets(buffer, 1000, fisier);
            i++;
            char *c = &buffer[strlen(buffer) - 1];
            if (*c == '\n')
                *c = '\0';
            fprintf(fisierRezultat, "%s\n", buffer);
        }
        fclose(fisier);
    }
}

int functieA1()
{
    FILE *fisierCatalog, *fisierRezultat;

    if ((fisierRezultat = fopen("fisier-rezultat.txt", "wt")) == NULL)
    {
        puts("EROARE LA CREAREA FISIERULUI REZULTAT");
        exit(1);
    }
    if ((fisierCatalog = fopen("fisier-catalog.txt", "rt")) == NULL)
    {
        puts("Nu exista fisierul catalog");
        exit(1);
    }
    char numeFisier[100], fisiereDeschise[10][100];
    int length = 0;
    int linie, numarLinii;
    while (!feof(fisierCatalog))
    {
        fscanf(fisierCatalog, "%s", numeFisier);
        int ok = 1;
        for (int i = 0; i < length; i++)
        {
            if (strcmp(fisiereDeschise[i], numeFisier) == 0)
            {
                ok = 0;
                i = length;
            }
        }
        if (ok)
        {
            strcpy(fisiereDeschise[length], numeFisier);
            length++;
        }
        fscanf(fisierCatalog, "%d%d", &linie, &numarLinii);
        functieA2(numeFisier, linie, numarLinii, fisierRezultat);
    }
    return length;
}
// FINAL PUNCT A

// PUNCT B
#define CREEAZA_FISIERE_BINARE 0

typedef struct
{
    char cod[10];
    int punctaj;
} Activitate;
typedef struct
{
    char numeStudent[100], codActivitate[10];
    int numarParticipari;
} Participari;
typedef struct
{
    char numeStudent[100];
    int punctajTotal;
} Student;

// void citeste(void *lista, int *lungime, FILE *fisier)
// {   
//     printf("%d",(int)sizeof((*lista)[0]));
//     fseek(fisier, 0L, SEEK_END);
//     (*lungime) = (int)(ftell(fisier) / (long)sizeof((*lista)[0]));
//     fseek(fisier, 0L, SEEK_SET);
//     fread(*lista, sizeof(lista[0]), (size_t)(*lungime), fisier);
// }

#define citeste(lista, lungime, fisier) \
{\
fseek(fisier, 0L, SEEK_END);\
(lungime) = (int)(ftell(fisier) / (long)sizeof((lista)[0]));\
fseek(fisier, 0L, SEEK_SET);\
fread((lista), sizeof((lista)[0]), (size_t)lungime, fisier);\
}

void functieB(Student lista[10], int *lungime)
{
    FILE *fisierParticipari, *fisierActivitati;
    if ((fisierActivitati = fopen("fisier-activitati.dat", "rb")) == NULL)
    {
        puts("Nu exista fisierul binar cu activitati!");
        exit(1);
    }
    if ((fisierParticipari = fopen("fisier-participari.dat", "rb")) == NULL)
    {
        puts("Nu exista fisierul binar cu participari!");
        exit(1);
    }
    Activitate listaActivitate[10];
    int lungimeActivitati = 0;
    Participari listaParticipari[20];
    int lungimeParticipari;

    citeste(listaActivitate, lungimeActivitati, fisierActivitati);
    citeste(listaParticipari, lungimeParticipari, fisierParticipari);
    // citeste((Activitate *) listaActivitate, &lungimeActivitati, fisierActivitati);
    // citeste((Participari *) listaParticipari, &lungimeParticipari, fisierParticipari);

    fclose(fisierActivitati);
    fclose(fisierParticipari);

    for (int i = 0; i < lungimeParticipari; i++)
    {
        int ok = 0;
        for (int j = 0; j < *lungime; j++)
            if (strcmp(listaParticipari[i].numeStudent, lista[j].numeStudent) == 0)
            {
                ok = 1;
                for (int k = 0; k < lungimeActivitati; k++)
                    if (strcmp(listaParticipari[i].codActivitate, listaActivitate[k].cod) == 0)
                        lista[j].punctajTotal += listaActivitate[k].punctaj * listaParticipari[i].numarParticipari;
            }
        if (!ok)
        {
            strcpy(lista[*lungime].numeStudent, listaParticipari[i].numeStudent);
            for (int k = 0; k < lungimeActivitati; k++)
                if (strcmp(listaParticipari[i].codActivitate, listaActivitate[k].cod) == 0)
                    lista[*lungime].punctajTotal = listaActivitate[k].punctaj * listaParticipari[i].numarParticipari;
            (*lungime)++;
        }
    }
    FILE *fisierFinal;
    if ((fisierFinal = fopen("fisier-final.dat", "wb")) == NULL)
    {
        puts("Eroare la crearea fisierului final!");
        exit(1);
    }
    fread(lista, sizeof(Student), (size_t)*lungime, fisierFinal);
    fclose(fisierFinal);
}

#if CREEAZA_FISIERE_BINARE == 1
Activitate creeazaActivitate(char *cod, int punctaj)
{
    Activitate activitate;
    strcpy(activitate.cod, cod);
    activitate.punctaj = punctaj;
    return activitate;
}
Participari creeazaParticipare(char *numeStudent, char *codActivitate, int numarParticipari)
{
    Participari participare;
    strcpy(participare.numeStudent, numeStudent);
    strcpy(participare.codActivitate, codActivitate);
    participare.numarParticipari = numarParticipari;
    return participare;
}
void creeazaFisiereBinare()
{
    FILE *fisierActivitati, *fisierParticipari;
    if ((fisierActivitati = fopen("fisier-activitati.dat", "wb")) == NULL)
    {
        puts("Eroare la crearea fisierului binar cu activitati!");
        exit(1);
    }
    if ((fisierParticipari = fopen("fisier-participari.dat", "wb")) == NULL)
    {
        puts("Eroare la crearea fisierului binar cu participari!");
        exit(1);
    }

    Activitate l1[5];
    l1[0] = creeazaActivitate("01", 10);
    l1[1] = creeazaActivitate("02", 5);
    l1[2] = creeazaActivitate("03", 8);
    l1[3] = creeazaActivitate("04", 11);
    l1[4] = creeazaActivitate("05", 15);
    fwrite(l1, sizeof(Activitate), (size_t)5, fisierActivitati);
    fclose(fisierActivitati);

    Participari l2[7];
    l2[0] = creeazaParticipare("Gigel", "02", 5);
    l2[1] = creeazaParticipare("Ion", "05", 5);
    l2[2] = creeazaParticipare("Ana", "03", 2);
    l2[3] = creeazaParticipare("Gigel", "01", 2);
    fwrite(l2, sizeof(Participari), (size_t)4, fisierParticipari);
    fclose(fisierParticipari);
}
#endif
// FINAL PUNCT B

void afiseazaLista(Student lista[10], int lungime)
{
    for (int i = 0; i < lungime; i++)
    {
        printf("STUDENTUL NUMARUL %d\nNume student: %s\n", i + 1, lista[i].numeStudent);
        printf("Punctaj total: %d\n\n", lista[i].punctajTotal);
    }
}
int main()
{
    // MAIN PUNCT A
    //  CHESTIA ASTA STERGE FISIERUL REZULTAT, DACA EXISTA DEJA CAND INCEPE RULAREA PROGRAMULUI
    FILE *f;
    if ((f = fopen("fisier-rezultat.txt", "rt")))
    {
        fclose(f);
        remove("fisier-rezultat.txt");
    }
    int nr = functieA1();
    printf("\nNUMAR DE FISIERE ACCESATE: %d\n", nr);
// MAIN FINAL PUNCT A

// MAIN PUNCT B
#if CREEAZA_FISIERE_BINARE == 1
    creeazaFisiereBinare();
#endif
    Student lista[10];
    int lungime;
    functieB(lista, &lungime);
    afiseazaLista(lista, lungime);
    // MAIN FINAL PUNCT B
    return 0;
}