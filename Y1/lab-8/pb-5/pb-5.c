#include <stdio.h>
#include <string.h>

typedef struct
{
    char nume;
    union alegere
    {
        int raza;
        struct ceva
        {
            int lungime, latime;
        } dimensiuni;
    }tip;

} Fig_geom;



int main()
{
    char aux;
    Fig_geom fig;
    printf("Introduceti o litera dintre urmatoarele pentru a selecta tipul figurii geometrice:\nCerc(c)\nPatrat(p)\nDreptunghi(d)\n:");
    do{
        char s[2];
        gets(s);
        if(strlen(s)==1)
           { fig.nume=s[0];
        if(fig.nume!='c'&&fig.nume!='C'&&fig.nume!='p'&&fig.nume!='P'&&fig.nume!='d'&&fig.nume!='D')
            printf("Introduceti strict acele litere!\n:");
           }
        else printf("Hai ma, pe bune? Incerci sa-mi strici programul? Good luck next time!\nIntroduceti strict acele litere!\n:");
    }while(fig.nume!='c'&&fig.nume!='C'&&fig.nume!='p'&&fig.nume!='P'&&fig.nume!='d'&&fig.nume!='D');

    if('A'<=fig.nume && fig.nume<='Z') 
        fig.nume+=32;
    
    switch(fig.nume){
        case 'c': 
        printf("Introduceti raza: ");
        scanf("%d",&fig.tip.raza) ;
        int raza=fig.tip.raza;
        printf("Figura geometrica: Cerc\nCircumferinta: %.2f\nArie: %.2f",2*3.14*raza,raza*raza*3.14);
        break;
        case 'p':
        printf("Introduceti latura: ");
        scanf("%d",&fig.tip.dimensiuni.latime);
        fig.tip.dimensiuni.lungime=fig.tip.dimensiuni.latime;
        int latura=fig.tip.dimensiuni.latime;
        printf("Figura geometrica: Patrat\nPerimetru: %d\nArie: %d",4*latura,latura*latura);
        break;
        case 'd':
        printf("Introduceti latimea: ");
        scanf("%d",&fig.tip.dimensiuni.latime);
        printf("Introduceti lungimea: ");
        scanf("%d",&fig.tip.dimensiuni.lungime);
        int latime=fig.tip.dimensiuni.latime,lungime=fig.tip.dimensiuni.lungime;
        printf("Figura geometrica: Dreptunghi\nPerimetru: %d\nArie: %d",2*(latime+lungime),lungime*latime);
        break;
            }

}