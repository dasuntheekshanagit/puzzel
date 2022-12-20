#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 256

char grid[SIZE][SIZE]={0},word[SIZE][SIZE]={0};
int row,col,wordcount;

typedef struct _{
    /*
        This words ttpe has pointer and wordlist array. pointer indicate the last updated index of the wordlist.
    */
    int pointer;
    char wordlist[SIZE][SIZE];
}words;

words wordList[SIZE]={0,{0}};

void getInput();
void getWordLength();
int input_validity(char *,int);
int validate();

int main(){

    getInput();
    int i = validate();
    printf("%d %d\n",row,col);
    printf("%d\n",wordcount);
    getWordLength();
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
        strcpy(word[pointer],line);
        //printf("%s\n",word[pointer]);
        pointer++;
    }

    wordcount = pointer;

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

    row--;
    return 1;
}

void getWordLength(){
    /*
        This function itarate trough the word list and get length of words. The they are stored in words type array with corresponding length.
        Ex: cat, dog, fish
        wordlist = [0:[],0:[],0:[],2:['cat',''dog'],1:['fish']]
    */
    for (int i=0;i<wordcount;i++){
        //printf("%s ",word[i]);
        int len = strlen(word[i]);
        int point = (wordList+len)->pointer;
        (wordList+len)->pointer = point + 1;
        strcpy((wordList+len)->wordlist[point],word[i]);
        printf("%p %d %s\n",wordList+len,(wordList+len)->pointer,(wordList+len)->wordlist[point-1]);
    }
    return;
}
