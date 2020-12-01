#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct kamp{
    char ugedag[4];
    char dato[6];
    char kl[6];
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
void score_count(hold(*), kamp(*));
void search_for_team(int, hold(*), kamp(*));
void leard_bord(hold(*));

int main(){
    kamp kampArr[128];
    hold holdArr[14];
    FILE *fp = fopen("kampe-2019-2020.txt", "r");
    if (fp == NULL){
        printf("Could not read from file\n");
        return EXIT_FAILURE;
    }

    int i;
    int j = 0;

    for (i = 0; i < 14; i++)
    {
        holdArr[i].point = 0;
        holdArr[i].scoretMaal = 0;
        holdArr[i].modstannerMaal = 0;
    }
    
    holdArr[i].point = 0;

    printf("Reading file and gatering data.\n");
    read_file(kampArr, fp);
    printf("Creating struct for each team\n");
    create_team(holdArr, kampArr);
    printf("Starting score keeping\n\n");
    score_count(holdArr, kampArr);
    printf("Sorting teams by score\n");
    leard_bord(holdArr);

    /*her looper vi igennem fra bunden op, da vi har sotered det på den måde*/
    printf("Plads  Holdnavn Point Mål-af-hold Mål-mod-hold\n");
    for (i = 13; i > -1; i--)
    {
        j++;
        printf(" %d:      %s     %d       %d          %d\n", j, holdArr[i].holdNavn, holdArr[i].point, holdArr[i].scoretMaal, holdArr[i].modstannerMaal);
    }
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
                    kampArr[j].ugedag[3] = '\0';
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
                    kampArr[j].hold1[3] = '\0';
                    break;
                case 5:
                    strcpy(kampArr[j].hold2, temp);
                    kampArr[j].hold2[3] = '\0';
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

/*vi går ud fra at alle hold spiller både på ude bane og hjemme bane
Vi antager at alle holder har spillet i de 7 første kampe*/
void create_team(hold *holdArr, kamp *kampArr){
    
    int i;
    int j;
    
    for(i = 0, j = 7; i < 7; i++, j++){
        strcpy(holdArr[i].holdNavn, kampArr[i].hold1);
        strcpy(holdArr[j].holdNavn, kampArr[i].hold2);
    }
    
}

/*her køre man i gennem alle kampen og optælle point i gennem seachs for team*/
void score_count(hold *holdArr, kamp *kampArr){
    
    int i;
    int j;
    
    for(i = 0; i < 128; i++){
        /*printf("\n       Date     kl        Team       Score    Tilskuer\n");
        printf("%s   ", kampArr[i].ugedag);
        printf("%s   ", kampArr[i].dato);
        printf("%s   ", kampArr[i].kl);
        printf("%s  -  ", kampArr[i].hold1);
        printf("%s   ", kampArr[i].hold2);
        printf("%d  -  ", kampArr[i].score1);
        printf("%d   ", kampArr[i].score2);
        printf("%d\n", kampArr[i].tilskuer);*/
        search_for_team(i, holdArr, kampArr);
    }
}

/*matcher holdene med deres score og tæller score*/
void search_for_team(int pos, hold *holdArr, kamp *kampArr){
    
    int i;
    
    for ( i = 0; i < 14; i++)
    {
        
        if (strcmp(kampArr[pos].hold1, holdArr[i].holdNavn) == 0){
            
            holdArr[i].scoretMaal = holdArr[i].scoretMaal + kampArr[pos].score1;
            holdArr[i].modstannerMaal = holdArr[i].modstannerMaal + kampArr[pos].score2;

            if(kampArr[pos].score1 > kampArr[pos].score2){
                holdArr[i].point = holdArr[i].point + 3;
            }
            if(kampArr[pos].score1 == kampArr[pos].score2){
                holdArr[i].point = holdArr[i].point + 1;
            }
            else{
                break;
            }
            
        }
    }

    for ( i = 0; i < 14; i++)
    {
        if (strcmp(kampArr[pos].hold2, holdArr[i].holdNavn) == 0){
            holdArr[i].scoretMaal = holdArr[i].scoretMaal + kampArr[pos].score2;
            holdArr[i].modstannerMaal = holdArr[i].modstannerMaal + kampArr[pos].score1;

            if(kampArr[pos].score2 > kampArr[pos].score1){
                holdArr[i].point = holdArr[i].point + 3;
            }
            if(kampArr[pos].score2 == kampArr[pos].score1){
                holdArr[i].point = holdArr[i].point + 1;
            }
            break;
        }
    }
}

/*Bruger en simple sotering algorime til at plasere det højste nederest og det lavest*
øvers*/
void leard_bord(hold *holdArr){
    int i, j;
    hold temp;
    for (j = 0; j < 14; j++)
    {
        for (i = 0; i < 14; i++)
        {
            if(holdArr[i].point > holdArr[i+1].point && i + 1 != 14){
                
                temp = holdArr[i];
                holdArr[i] = holdArr[i+1];
                holdArr[i+1] = temp;
            }
            if(holdArr[i].point == holdArr[i+1].point && i + 1 != 14){
                
                if(holdArr[i].scoretMaal > holdArr[i+1].scoretMaal){
                
                temp = holdArr[i];
                holdArr[i] = holdArr[i+1];
                holdArr[i+1] = temp;
                }
            }
            

            
        }
    }
        
}