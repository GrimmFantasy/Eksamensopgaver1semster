/*
Casper Andersen
cand20@student.aau.dk
a313a
Software
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*Her opretter prototyper af det funktion vi f�r brug for,
jeg f�ler at man kunne undlade og bruge do_next_op da jeg man kan  g�re det mere over skuligt med 2*/
void scan_data(char(*), double(*));
void do_next_op(char(*), double(*), double(*));
void run_calculator(char(*));

int main()
{
    /*Vi starter med at oprette en char som vi s�tter til at v�re a*/
    char running = 'a';
    /*Grunden til at vi g�re det er s� vi har en variable
    s� programmet kun k�re indtil vi trykker p� q*/
    while(running != 'q')
    {
        /*vi laver en pointer til charen s� vi kan �ndre p� den i vores program*/
        run_calculator(&running);
    }
    return 0;
}

/*dette er hoved funktion til lommeregnern som g�r at scan_data og do_next_op kan tale sammen*/
void run_calculator(char *run)
{
    /*vi opretter  de tre variabler som vi skal bruge i vores program*/
    char oprator;
    double hojreOprand,
           akkumulator;
    /*her beder vi bruger om at indtaste en oprator, og hvis det vil en oprand*/
    printf("Enter operator, and an optional operand:");
    /*dette bliver opsamlede gennem scan_data funktion*/
    scan_data(&oprator, &hojreOprand);
    /*her �ndre vi vores char, som tjekker om den skal stoppe, til opratoren*/
    *run = oprator;
    /*dette er blot s� det ikke st�r p� samme linje*/
    printf("\n");

    /*efter vi har f�et opsmaled vores v�rdier k�re vi do_next_op,
    som ser hvilken regne stykke den skal lave*/
    do_next_op(&oprator,&hojreOprand,&akkumulator);
    /*her efter printer vi resultatet*/
     printf("The current result is %lf\n", akkumulator);

    /*alt dette bliver s� gjordt indtil bruger indtaster q*/

}
void scan_data(char *opr, double *hop){
    /*i denne funktion scanner og sender det tilbage til run_calculator*/
    double temp;
    char   op;

    scanf(" %c", &op);
    /*her tjekker vi hvilken oprator det er, og hvis den opfylder kravet,
    scanner vi efter opranden
    denne ide fik jeg fra en fra min nuværende gruppe ved navn Mads*/
    if ( op == '+' && '-' && '*' && '/' && '^')
    {
        scanf( " %lf", &temp);
        *hop = temp;
    }
    /*og til sidst sender vi dem tilbage*/
    *opr = op;

}

void do_next_op(char *opr, double *tmp, double *aku)
{
    /*I denne funktion tjekker gennem en switch case hvilken oprandran det er og laver det regne stykke der til h�re den
    og s� sender vi det tilbage til run_calculation*/
    switch(*opr)
    {

    case '+':
        *aku = *aku + *tmp;
        break;

    case '-':
        *aku = *aku - *tmp;
        break;

    case '*':
        *aku = *aku * *tmp;
        break;

    case '/':
        /*ved nogle af dem som denne tjekker vi om det er muligt at lave renge stykket*/
        if (*tmp == 0 && *aku == 0)
        {
            printf("CAN NOT DIVIDE WITH 0\n");
            break;
        }
        else
        {
            *aku = *aku / *tmp;
            break;
        }

    case '^':
        *aku = pow(*aku, *tmp);
        break;

    case '#':
        if (*aku <= 0)
        {
            printf("ERROR CAN NOT GET SQUARROOT OF A NIGATIV NUMBER\n");
            break;
        }
        else
        {
            *aku = sqrt(*aku);
            break;
        }

    case '%':
        *aku = *aku / *tmp;
        break;

    case '!':
        if (*aku == 0)
        {
            printf("CAN NOT DIVIDE WITH 0\n");
            break;
        }
        else
        {
            *aku = 1 / *aku;
            break;
        }

    case 'q':
        break;
    }

}


