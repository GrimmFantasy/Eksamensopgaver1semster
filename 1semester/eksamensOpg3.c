#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct kamp{
    char ugedag[3];
    char dato[4];
    char kl[4];
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

void read_file(kamp(*), FILE(*));
int main(){
    kamp kampArr[128] /*= malloc(128*sizeof(struct kamp))*/;
    hold holdArr[14];
    FILE *fp = fopen("kampe-2019-2020.txt", "r");
    
    if (fp == NULL){
        printf("Could not read from file\n");
        return EXIT_FAILURE;
    }

    printf("Reading file and gatering data.\n");
    read_file(kampArr, fp);
    
    return 0;
}

/**/
void read_file(kamp *kampArr, FILE *fp){
    char temp[10];
    int i;
    int j;
    for(j = 0; j < 128; j++){
        
        
        for (i = 0; i < 10; i++)
        {
            fscanf(fp, " %s ", temp);
            
            switch (i)
            {
                case 0:
                    
                    strcpy(kampArr[j].ugedag, temp);    
                    break;
                case 1:
                    strcpy(kampArr[j].dato,temp);
                    break;
                case 2:
                    strcpy(kampArr[j].kl, temp);
                    break;
                case 3:
                    strcpy(kampArr[j].hold1, temp);
                    break;
                case 5:
                    strcpy(kampArr[j].hold2, temp);
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
}
