#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {

    char nume[20],produs[20];
    int cantitate;

}Firma;
int main() 
{
    // Firma firma[4];
    // int length;

    // printf("Introduceti un numar natural: ");
    // scanf("%d",&length);

    // printf("Acum introduceti %d firme:\n",length);
    // for(int i=0; i<length; i++)
    // {
    //     printf("*Firma numarul %d*\n",i+1);
    //     printf("Nume: "); scanf("%s",firma[i].nume);
    //     printf("Produs: "); scanf("%s",firma[i].produs);
    //     printf("Cantitate: "); scanf("%d",&firma[i].cantitate);
    // }  

    // printf("\n");
    // for(int i=0;i<length;i++)
    //     {
    //         printf("Firma numarul %d:\n",i+1);
    //         printf("Nume: %s\n",firma[i].nume); 
    //         printf("Produs: %s\n",firma[i].produs); 
    //         printf("Cantitate: %d\n",firma[i].cantitate); 
            
    //     }

    // char a,b,s[10],p[10];
    // int  m,n,o;
    // float f;

    // scanf("%s",s);
    // scanf("%s",p);
    // printf(
    // "======"
    // "\n1%s"
    // "\n1%s"
    // "\n====="
    // ,s,p);

    // scanf("%c",&a);
    // fflush(stdin);
    // scanf("%c",&b);

    // scanf("%s",s);
    // printf(
    // "======"
    // "\n1%c"
    // "\n1%c"
    // "\n====="
    // "\n%s"
    // ,a,b,s);

    // scanf("%d",&m);
    // scanf("%c",&a);
    // scanf("%f",&f);

    // printf(
    //     "===="
    //     "\n|%d|"
    //     "\n|%c|"
    //     "\n|%f|"
    //     "\n====",m,a,f
    // );

    char a,b,c,s[10],p[10];

    a=getchar();
    b=getchar();
    gets(s);
    c=getchar();

    printf
    (
    "|%c|"
    "\n|%c|"
    "\n|%s|"
    "\n|%c|"
    
    ,a,b,s,c);
    

    
    


}