/*
Exercitiul 3. 
Lista de produse celebre care folosesc C:
- DirectX, OpenGL contin cod de C
- Windows a folosit si C pentru kernel
- MySQL e scris si el partial in C
- Microcontrollers si automatizari sunt programate cu C
- Dintre sistemele de operare, UNIX folosise C si apoi a mai fost folosit partial pentru dezvoltarea sistemelor de operare, precum 
GNU/Linux, Windows sau MacOS
- GIT e programat in C! (amazing)
- Winamp are cod de C
- VLC, cel mai tare media player, e programat in C :D
*/


// Exercitiul 4.
#include <stdio.h>
#include <string.h>

typedef struct{
    char nume[50],prenume[100],oras[50],liceu[100],hobbys[5][50];
    int numarHobbys;
}Persoana;

void printLastName(Persoana persoana)
{
    printf("Nume: %s\n",persoana.nume);
}
void printFirstName(Persoana persoana)
{
    printf("Prenume: %s\n",persoana.prenume);
}
void printCity(Persoana persoana)
{
    printf("Oras: %s\n",persoana.oras);
}
void printHighschool(Persoana persoana)
{
    printf("Liceu: %s\n",persoana.liceu);
}
void printHobbys(Persoana persoana)
{
    for(int i=0;i<persoana.numarHobbys;i++)
        printf("%d. %s\n",i+1,persoana.hobbys[i]);
    puts("");
}

void sorteazaCrescatorHobbys(Persoana *persoana){
    for(int i=0;i<persoana->numarHobbys-1;i++)
        for(int j=i+1;j<persoana->numarHobbys;j++)
            if(strcmp(persoana->hobbys[i],persoana->hobbys[j])>0)
                {
                char aux[50];
                strcpy(aux,persoana->hobbys[i]);
                strcpy(persoana->hobbys[i],persoana->hobbys[j]);
                strcpy(persoana->hobbys[j],aux);
                }
}

int main(){

    Persoana persoana;
    strcpy(persoana.nume,"");
    strcpy(persoana.prenume,"");
    strcpy(persoana.oras,"");
    strcpy(persoana.liceu,"\"\"\n");
    persoana.numarHobbys=4;
    strcpy(persoana.hobbys[0],"");
    strcpy(persoana.hobbys[1],"");
    strcpy(persoana.hobbys[2],"");
    strcpy(persoana.hobbys[3],"");

    printLastName(persoana);
    printFirstName(persoana);
    printCity(persoana);
    printHighschool(persoana);
    puts("Hobby-uri inainte de orodonare alfabetica:");
    printHobbys(persoana);
    sorteazaCrescatorHobbys(&persoana);
    puts("Hobby-uri dupa ordonare:");
    printHobbys(persoana);

}

// Exercitiul 5
/*
    ALGORITM DE GATIT 5 SNITELE DE PUI CRUNCHY
    struct Bol {
        union varianta{
            numarOua
            kilogrameFulgiDePorumb
            kilogrameFaina
        }
    }

    Bol bolOua,bolFaina,bolFulgi;
    bolOua.varianta.numarOua=6
    bolOua.varianta.kilogrameFulgiDePorumb=0.5
    bolOua.varianta.kilogrameFaina=0.5

    adaugaSare(bolFaina)
    adaugaPiper(bolFaina)
    adaugaBoiaDulce(bolFaina)
    amestecaFaina()

    amestecaOua()
    zdrobesteFulgi()

    puneTigaiePeAragaz()
    pornesteFocul()
    regleazaFocMediu()
    executa
    {
        adaugaUlei(tigaie)
    }pana cand esteBaltaDecentaDeUlei = 1

    contor=1
    cat timp sniteleRamase > 0 executa
    {
        trecePuiPrinFaina()
        trecePuiPrinOu()
        trecePuiPrinFulgi()
        asazaPuiInTigaie()
        daca spatiuTigaie = 0 sau sniteleRamase=0 atunci
        {
            cat timp sniteleNotGoldenBrown = 1 executa
            {
            asteapta(60s)
            intoarceSnitele()
            daca sniteleNotGoldenBrown = 1 atunci{
            asteapta(60s)
            } 
            puneSniteleInFarfurie()  
        }
        sniteleRamase= sniteleRamase - 1
    }
    iaFurculitaSiCutit()
    puneBautura()
    Mananca()
    enjoy()
*/