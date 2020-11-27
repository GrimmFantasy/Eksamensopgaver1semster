#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct kamp{
    char ugedag[4];
    char dato[5];
    char kl[5];
    char hold1[4];
    char hold2[4];
    int score1;
    int score2;
    int tilskuer;
}kamp;

typedef struct hold{
    char holdNavn[4];
    int point;
    int scoretMaal;
    int modstannerMaal;
}hold;

void read_file(kamp(*), FILE(*));
void create_team(hold(*), kamp(*));
void filter_team(hold(*), char(*), int(*));

int main(){
    kamp kampArr[128];
    hold holdArr[14];
    FILE *fp = fopen("kampe-2019-2020.txt", "r");
    
    if (fp == NULL){
        printf("Could not read from file\n");
        return EXIT_FAILURE;
    }

    printf("Reading file and gatering data.\n");
    read_file(kampArr, fp);
    printf("Creating struct for each team\n");
    create_team(holdArr, kampArr);
    printf("Starting score keeping\n\n");

    return 0;
}

/*Vi læser filen og opsamler det relevente infomation*/
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
                    kampArr[j].ugedag[4] = '\0';
                    break;
                case 1:
                    strcpy(kampArr[j].dato,temp);
                    kampArr[j].dato[5] = '\0';
                    break;
                case 2:
                    strcpy(kampArr[j].kl, temp);
                    kampArr[j].kl[5] = '\0';
                    break;
                case 3:
                    strcpy(kampArr[j].hold1, temp);
                    kampArr[j].hold1[4] = '\0';
                    break;
                case 5:
                    strcpy(kampArr[j].hold2, temp);
                    kampArr[j].hold2[4] = '\0';
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

/*vi går ud fra at alle hold spiller både på ude bane og hjemme bane*/
void create_team(hold *holdArr, kamp *kampArr){
    
    int i;
    int j;
    
    for(i = 0, j = 7; i < 7; i++, j++){
        strcpy(holdArr[i].holdNavn, kampArr[i].hold1);
        strcpy(holdArr[j].holdNavn, kampArr[i].hold2);
    }
    
}
