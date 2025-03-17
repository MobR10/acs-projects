#include <stdio.h>
#include <stdlib.h>

void fibonacciIterativ(int numarTermeni)
{
    if (numarTermeni <= 2)
        puts("Bai frate, introdu mai mult de 2 termeni");
    else
    {
        int prev = 1, current = 1, next;
        printf("%d, %d, ", 1, 1);
        for (int i = 2; i < numarTermeni; i++)
        {
            next = prev + current;
            prev = current;
            current = next;
            if (i == numarTermeni)
                printf("%d", next);
            else
                printf("%d, ", next);
        }
    }
}

int fibonacciRecursiv(int numarTermeni)
{
    if(numarTermeni<=1){
       printf("%d, ",numarTermeni);
       return numarTermeni; 
    }
    else
    {
        int s=fibonacciRecursiv(numarTermeni-1)+fibonacciRecursiv(numarTermeni-2);
        printf("%d, ",s);
    }
}

int main()
{
    //fibonacciIterativ(30);
    fibonacciRecursiv(30);
    puts("c");
}