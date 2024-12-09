#include <stdio.h>
#include <string.h>

typedef struct {

    char firma[20],produs[20];
    int cantitate;
}Informatie;

int main(){

    int n;
    printf("Scrieti cate firme vreti sa cititi: ");
    scanf("%d",&n);
    char aux=getchar();

    Informatie v[6];

    for(int i=0;i<n;i++)
        {
            printf("Firma numarul %d:\n",i+1);
            printf("Numele: ");
            gets(v[i].firma);
            printf("Produs: ");
            gets(v[i].produs);
            printf("Cantitate: ");
            scanf("%d",&v[i].cantitate);
            aux=getchar();
        }

        // printf("============AFISARE===========\n");
        // for(int i=0;i<n;i++)
        // {
        //     printf("Firma numarul %d:\n",i+1);
        //     printf("Numele: %s\n",v[i].firma);
        //     printf("Produs: %s\n",v[i].produs);
        //     printf("Cantitate: %d\n====================\n",v[i].cantitate);
        // }
        char produs[20];
        printf("Ce produs cautati sa aiba cea mai mare cantitate?\n");
        gets(produs);
        int max=0,ok=0;
        char firma_mare[20];
        for(int i=0;i<n;i++)
        {
             if(strcmp(v[i].produs,produs)==0) 
                {   ok=1; 
                    if(max<v[i].cantitate)
                    {
                        max=v[i].cantitate;
                        strcpy(firma_mare,v[i].firma);

                    }
                        
                }
        }
        if(ok) printf("Firma cu cea mai mare cantitate de %s este %s.\n",produs,firma_mare);
        else  printf("Nu exista acest produs");
           

}