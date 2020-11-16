/*
Casper Andersen
cand20@student.aau.dk
a313a
Software
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rool_multiple_dies(int, int(*));
int lower_section(int, int, int(*), int(*));
int led_efter_ens(int, int, int(*), int(*));
int ComAndRemove(int, int, int(*), int(*), int(*));

int main()
{
    srand(time(NULL));
    
    int n = 0;
    int upper[6];
    int total_upper = 0;
    int lower[9];
    int *lw = lower;
    int total_lower = 0;
    int pos;
    int a= 0;
    int i, num;
    
    while (n < 5)
    {
        printf("\nhvor mange terninger vil du spille med? (antalet skal vaere 5 eller over)");
        scanf(" %d", &n);
    }
    
    int teringer[n];    
    int *t = teringer;

/*upper sections*/
/*her tager vi alle dem hvor vi bare skal finde en slags af hver tal på terningen
til det bruger vi blot to forloops til at tælle op til 6*/
    for (pos = 0; pos < 6; pos++)
    {
        rool_multiple_dies(n, t);

        for (i=0; i < n; i++)
        {
            if (teringer[i] == (pos + 1))
            {
                a = a + teringer[i]; 
            }
        }

        upper[pos] = a;

        printf("\n%d'ere     = %d           ", pos + 1, upper[pos]);
        for (i=0; i < n; i++)
        {
            printf(" %d", teringer[i]);
        }
        printf("\n");
        a = 0;  
    }

    for (pos = 0; pos < 6; pos++)
    {
        total_upper = total_upper + upper[pos];
    }

    printf("\nScore     = %d\n", total_upper);
    /*her ser vi om der er opnået nok point til at få bonusen*/
    if (total_upper >= 63)
    {
        printf("Bonus opnået\n");
        total_upper = total_upper + 50;
        printf("Første section score = %d\n", total_upper);
    }
    else
    {
        printf("Bonus ikke opnået\n");
        printf("Første section score = %d\n", total_upper);
    }
/*upper section end*/

/*lower section*/
/*her vi bruger en for loop til  at holde styr på hvor langt vi er nået i den her del af spillet
det bliver så sendt til funktion lower_section, hvor efter resultatet bliver printet af det skridt
vi er på og det til hørende terninger og til sidst regner vi den totale score ud*/
    for (num = 0; num < 9; num++)
    {   
        printf("\n");
        rool_multiple_dies(n, teringer);
        lower_section(n, num, t, &*lw);

        for (i = 0; i < n; i++)
        {
            printf(" %d", *(teringer + i));
        }
        total_lower = total_lower + lower[num];
    }

    total_lower = total_lower + total_upper;

    printf("\nTotal score: %d", total_lower);

    printf("\n\n");
    return 0;
}


/*her laver vi de forskellige dele til den anden del af spillet*/
int lower_section(int n, int num, int *teringer, int *lw_arr)
{
    int pair1[2], *p1 = pair1;
    int pair2[2], *p2 = pair2;
    int three[3], *p3 = three;
    int four[4],  *p4 = four;
    int small_straight[5], *ss = small_straight;
    int large_straight[5], *ls = large_straight;
    int yatze[5], *ptrYatze = yatze;       
    int total = 0;
    int pos;
    int length;
    int i;
    int j;


    switch (num)
    {   
        /*her bruger vi en funkrtion led_efter_ens som den bruger 
        til at finde det højste tal som der er flere af*/
        case 0:

            length = sizeof(pair1)/sizeof(pair1[0]);
            led_efter_ens(length, n, p1, teringer);
            for(i = 0; i < length; i++)
            {
                total = total + *(p1+i);
            }
            *(lw_arr + num) = total;
            printf("Et par  =  %d            ", total);
        break;

        case 1:

            length = sizeof(pair1)/sizeof(pair1[0]);
            led_efter_ens(length, n, p1, teringer);
            
            for(i = 0; i < length; i++)
            {
                total = total + *(p1+i);
            }

            if (pair1[0] != 0)
            {
                /*hvis vi finder noget for det første par køre vi en funktion som søger for
                vi ikke finder det samme til den næste del*/
                length = sizeof(pair2)/sizeof(pair2[0]);
                ComAndRemove(n, length, teringer, p1, p2); 
            }

            if(pair1[0] == 0 || pair2[0] == 0)
            {
                total = 0;
            } 
            else
            {
                for(i = 0; i < length; i++)
                {
                    total = total + *(p2+i);
                }
                
            }
            

            *(lw_arr + num) = total;
            printf("To par  =  %d            ", total);
        break;

        case 2:

            length = sizeof(three)/sizeof(three[0]);
            led_efter_ens(length, n, p3, teringer);

            for(i = 0; i < length; i++)
            {
                total = total + *(p3+i);
            }

            *(lw_arr + num) = total;
            printf("Tre ens  =  %d            ", total);
        break;

        case 3:

            length = sizeof(four)/sizeof(four[0]);
            led_efter_ens(length, n, p4, teringer);

            for(i = 0; i < length; i++)
            {
                total = total + *(p4+i);
            }

            *(lw_arr + num) = total;
            printf("Fire ens  =  %d            ", total);
        break;

        case 4:
            pos = 0;
            length = sizeof(small_straight)/sizeof(small_straight[0]);
            for (i = 1; i <= 5; i++)
            {
                for(j = 0; j < n; j++)
                {
                    if (*(teringer + j) == i)
                    {
                        small_straight[pos] = *(teringer + j);
                        
                        pos++;
                        j = n;
                    }
                }
            }
            if (pos != length)
            {
                for(i = 0; i < length; i++)
                {
                    total = 0;
                }
            }
            else
            {
                for(i = 0; i < length; i++)
                {
                    total = total + *(ss+i);
                }
            }
            *(lw_arr + num) = total;
            printf("Small straight  =  %d            ", total);
        break;

        case 5:

            pos = 0;
            length = sizeof(large_straight)/sizeof(large_straight[0]);
            for (i = 2; i <= 6; i++)
            {
                for(j = 0; j < n; j++)
                {
                    if (*(teringer + j) == i)
                    {
                        large_straight[pos] = *(teringer + j);
                        pos++;
                        j = n;
                    }
                }
            }
            if (pos != length)
            {
                for(i = 0; i < length; i++)
                {
                    total = 0;
                }
            }
            else
            {
                for(i = 0; i < length; i++)
                {
                    total = total + *(ls+i);
                }
            }
            *(lw_arr + num) = total;
            printf("Large straight  =  %d            ", total);
        break;

        case 6:

            length = sizeof(three)/sizeof(three[0]);
            led_efter_ens(length, n, p3, teringer);
           
            for(i = 0; i < length; i++)
            {
                total = total + *(p3+i);
            }

            if (three[0] != 0)
            {
                length = sizeof(pair2)/sizeof(pair2[0]);
                ComAndRemove(n, length, teringer, p3, p2); 
            }
            
            if(three[0] == 0|| pair2[0] == 0)
            {
                total = 0;
            } 
            else
            {
                for(i = 0; i < length; i++)
                {
                    total = total + *(p2+i);
                }
                
            }
            

            *(lw_arr + num) = total;
            printf("Fuld Hus  =  %d            ", total);
        break;

        case 7:

        for(i = 0; i < n; i++)
        {
            total = total + *(teringer +i);
        }
        
        *(lw_arr + num) = total;
        printf("Chancen  =  %d            ", total);

        break;
        
        case 8:

            length = sizeof(yatze)/sizeof(yatze[0]);
            led_efter_ens(length, n, ptrYatze, teringer);

            for(i = 0; i < n; i++)
            {
            total = total + *(teringer +i);
            }

            *(lw_arr + num) = total;
            printf("Yatzy  =  %d            ", total);
        break;
    }
   
   


}

/*her finder vi tal som vi allerede har brugt i vores forige array og fjerner
dem da de par ovs ikke må have de samme tal, her efter sender den så kopien af terning 
arrayet vider til led_efter_ens*/
int ComAndRemove(int n, int length, int *teringer, int *com, int *arr)
{
    
    int i;
    int terning_copy[n];
    int *pTern = terning_copy;

    for (i = 0; i < n; i++)
    {
        terning_copy[i] = *(teringer + i);
        if (terning_copy[i] == *(com + 1))
        {
            terning_copy[i] = 0;
        }
        
    }
    led_efter_ens(length, n, arr, pTern);
    
}

/*her bruger vi længende af vores array og tering arrayet til at finde to tre eller fem ens*/
int led_efter_ens(int length, int n, int *arr, int *teringer)
{
    int i; 
    int l = 0;
    int pos; 
    int t[n];

    for (i = 0; i < n; i++)
    {
        t[i] = *(teringer + i);
    } 
    
    for (i = 6; i >= 1; i--)
    {
        for (pos = 0; pos < n; pos++)
        {

            if (t[pos] == i)
            {
                *(arr + l) = *(teringer + pos);
                t[pos] = 0;
                l++;
                if(l == length)
                {
                    pos = n;
                }
            }
            
        }

        if (l == length)
        {
            break;
        }
        else if (l != length)
        {
            l = 0;
        }
    }

    if (*(arr + 0) != *(arr + length -1))
    {
        for(l=0;l<length;l++)
        {
            *(arr + l) = 0;
        }
    }    
    
}

int rool_multiple_dies(int n, int *teringer)
{
    int pos;

    for (pos = 0; pos < n; pos++)
    {
        *(teringer + pos) = (rand() % 6) +1;

    }
}