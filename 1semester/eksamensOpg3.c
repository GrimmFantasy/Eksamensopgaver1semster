#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct kamp{
    char ugedag[3];
    int dato[4];
    int kl[4];
    char hold1[3];
    char hold2[3];
    int score1;
    int score2;
    int tilskuer;
}kamp;

typedef struct hold{
    char holdNavn[3];
    int point;
    int scoretMaal;
    int modstannerMaal;
}hold;


int main(){
    kamp kampArr[128] /*= malloc(128*sizeof(struct kamp))*/;
    hold holdArr[14];
    char temp[10];
    int i;
    int j;
    FILE *fp = fopen("kampe-2019-2020.txt", "r");
    
    for(j = 0; j < 1; j++){
        
        
        for (i = 0; i < 10; i++)
        {
            fscanf(fp, " %s ", temp);
            
            switch (i)
            {
                case 0:
                    kampArr[j].ugedag[0] = temp[0];
                    printf("%s\n", kampArr[j].ugedag);
                    break;
                case 1:
                    *kampArr[j].dato = temp;
                    break;
                case 2:
                    *kampArr[j].kl = temp;
                    break;
                case 3:
                    *kampArr[j].hold1 = temp;
                    break;
                case 5:
                    *kampArr[j].hold2 = temp;
                    break;
                case 6:
                    kampArr[j].score1 = atoi(temp);
                    break;
                case 8:
                    kampArr[j].score2 = atoi(temp);
                    break;
                case 9:
                    kampArr[j].tilskuer = atoi(temp);
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

