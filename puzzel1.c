#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 256

char grid[SIZE][SIZE]={0},word[SIZE][SIZE]={0};
int row,col;

void getInput();
int input_validity(char *,int);
int validate();

int main(){

    getInput();
    int i = validate();
    printf("%d %d\n",row,col);
    return 0;
}

void getInput(){
    char line[SIZE]= {0};
    int pointer = 0;

    //printf("Grid: \n");

    while (scanf("%[^\n]%*c",line) != 0){
        strcat(grid[pointer],line);
        //printf("%s\n",grid[pointer]);
        pointer++;
    }

    scanf("%*c",line);

    pointer = 0;
    //printf("Word: \n");

    while (scanf("%[^\n]%*c",line) != 0){
        strcat(word[pointer],line);
        //printf("%s\n",word[pointer]);
        pointer++;
    }

    return ;
}

int input_validity(char puzzle[],int len){
    for(int j=0;j<len;j++){
            if (isalpha(puzzle[j]) || puzzle[j]=='#' || puzzle[j] == '*' ){
                continue;
            }
            else{
                return 0;
            }
            }
        return 1;
}

int validate(){
    int len;
    col = strlen(grid[0]);

    do{
        len = strlen(grid[row]);
        int sts = input_validity(grid[row],len);
        if (!sts){
            printf("INVALID INPUT\n");
            return sts;
        }

        row++;
    }
    while (len > 0);

    return 1;
}
