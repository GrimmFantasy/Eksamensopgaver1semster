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
int ComAndRemove(int, int, int, int(*));

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

    printf("Score     = %d\n", total_upper);

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
    for (num = 0; num < 9; num++)
    {   
        printf("\n");
        rool_multiple_dies(n, teringer);
        lower_section(n, num, t, &*lw);
        printf("Et par  =  %d            ", lower[num]);
        for (i = 0; i < n; i++)
        {
            printf(" %d", *(teringer + i));
        }
    }
    return 0;
}

int lower_section(int n, int num, int *teringer, int *lw_arr)
{
    int pair1[2], *p1 = pair1,
        pair2[2], *p2 = pair2,
        three[3], *p3 = three,
        four[4],  *p4 = four,
        small_straight[5], *ss = small_straight,
        large_straight[5], *ls = large_straight,
        chance[n],          
        total = 0, i;
    
    
    switch (num)
    {
        case 0:
            led_efter_ens(2, n, p1, teringer);
            for(i = 0; i < 2; i++)
            {
                total = total + *(p1+i);
            }
            *(lw_arr + num) = total;
        break;

        case 1:
            led_efter_ens(2, n, p1, teringer);

        default:
        break;
    }
   
   


}
int ComAndRemove(int n, int teringer, int com, int *arr)
{
    int terning_copy[n];
    for (i = 0; i < n; i++)
    {
        terning_copy[i] = *(teringer + i)
        
    }
    
}
int led_efter_ens(int length, int n, int *arr, int *teringer)
{
    int i, 
        l = 0,
        pos, 
        t[n];

    for (i = 0; i < n; i++)
    {
        t[i] = *(teringer + i);
    } 
    
    for (i = 6; i > 1; i--)
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