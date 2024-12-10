#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{

    char s[40];
    int linie;

} Comp;

int functie(int v[], size_t n, int w[], size_t m, int rez[], size_t *p)
{
    *p = 0;
    int ok = 0;
    for (size_t i = 0; i < n; i++)
        if (v[i] > 0)
        {
            ok = 1;
            rez[*p] = i;
            (*p)++;
        }
    for (size_t i = 0; i < m; i++)
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

void init()
{
    FILE *f;
    if ((f = fopen("fisier.dat", "wb")) == NULL)
    {
        puts("ERROR init(): nu s-a putut deschide fisierul!");
        exit(1);
    }
    int a[100] = {1, -3, -1, 4, 0, 6, 7,0,-13,-1,0,5,0,0,0,0,-1,-2};
    fwrite(a, sizeof(int), 100, f);
    fclose(f);
}
int main()
{
    Comp t[20];
    FILE *fb;
    FILE *rezultat;
    int v[20], w[20], rez[40];
    size_t n, m, p, tCount = 0;

    init();
    printf("Introduceti numarul de elemente al primului vector: ");
    scanf("%lld", &n);
    printf("Introduceti numarul de elemente al celui de-al doilea vector: ");
    scanf("%lld", &m);

    if ((fb = fopen("fisier.dat", "rb")) == NULL)
    {
        puts(("Nu s-a putut deschide fisierul binar"));
        exit(1);
    }
    fread(v, sizeof(int), n, fb);
    fread(w, sizeof(int), m, fb);

    for (size_t i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
    for (size_t i = 0; i < m; i++)
        printf("%d ", w[i]);

    if (functie(v, n, w, m, rez, &p))
    {
        printf("\n VECTORUL REZULTANT: ");
        for(size_t i=0;i<p;i++)
            printf("%d ",rez[i]);
        printf("\n");
        unsigned int nr;
        printf("Introduceti cu cate fisiere doriti sa lucrati: ");
        scanf("%u", &nr);

        int ok = 0;

        for (unsigned i = 0; i < nr; i++)
        {
            printf("Introduceti numele fisierului %d:", i + 1);
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

                for (size_t j = 0; j < p; j++)
                {
                    fgets(sir, 100, f);
                }
                for (size_t i = 0; i < p; i++)
                {
                    aux[poz] = sir[rez[i]];
                    poz++;
                }
                aux[poz] = '\0';
                strcpy(t[tCount].s, aux);
                t[tCount].linie = p;
                tCount++;
                ok = 1;
            }
        }
        if (ok)
        {
            if ((rezultat = fopen("rezultat.dat", "wb")) == NULL)
            {
                puts("Nu s-a putut deschide fisierul rezultat");
                exit(1);
            }
            fwrite(t, sizeof(Comp), tCount, rezultat);
        }
    }
}