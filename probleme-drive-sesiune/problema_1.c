#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct{

    char s[40];
    int linie;

}Comp;

int functie(int v[], int n,int w[], int m,int rez[], int *p)
{
    *p=0; int ok=0;
    for(int i=0;i<n;i++)
        if(v[i]>0)
            {
                ok=1;
                rez[*p]=i;
                (*p)++;
            }
    for(int i=0;i<m;i++)
        if(v[i]==0)
            {
                ok=1;
                rez[*p]=i;
                (*p)++;
            }
    if(ok)
    return 1;
    else return 0;
}
int main()
{
    Comp t[20];
    FILE *fb,*rezultat;
    int n,m,p,v[20],w[20],rez[40];
    

    printf("Introduceti numarul de elemente al primului vector: ");
    scanf("%d",&n);
    printf("Introduceti numarul de elemente al celui de-al doilea vector: ");
    scanf("%d",&m);

    if((fb=fopen("fisier.dat","rb"))==NULL)
        {
            puts(("Nu s-a putut deschide fisierul binar"));
            exit(1);
        }
    fread(v,sizeof(int),n,fb);
    fread(w,sizeof(int),m,fb);

    for(int i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
    for(int i=0;i<m;i++)
        printf("%d ",w[i]);

    if(functie(v,n,w,m,rez,&p))
        {
            unsigned int nr;
            printf("Introduceti cu cate fisiere doriti sa lucrati: ");
            scanf("%u",&nr);
            
            for(int i=0;i<nr;i++)
            {
                printf("Introduceti numele fisierului %d:",i+1);
                char nume[20];
                scanf("%s",nume);
                FILE *f;
                if((f=fopen(nume,"r"))==NULL)
                    {
                        puts("Fisierul nu exista, incearca din nou: ");
                        i--;
                    }
                else
                {
                    char aux[40]="";
                    for(int i=0;i<p;i++)
                        {
                            
                        }
                }
            }
            
        }
   
}