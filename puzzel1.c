#include <stdio.h>
#include <string.h>

#define SIZE 256

char grid[SIZE][SIZE]={0},word[SIZE][SIZE]={0};

void getInput();

int main(){

    getInput();

    return 0;
}

void getInput(){
    char line[SIZE]= {0};
    int pointer = 0;

    printf("Grid: \n");

    while (scanf("%[^\n]%*c",line) != 0){
        strcat(grid[pointer],line);
        //printf("%s\n",grid[pointer]);
        pointer++;
    }

    scanf("%*c",line);

    pointer = 0;
    printf("Word: \n");

    while (scanf("%[^\n]%*c",line) != 0){
        strcat(word[pointer],line);
        //printf("%s\n",word[pointer]);
        pointer++;
    }

    return ;
}
