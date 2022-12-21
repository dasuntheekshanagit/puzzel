#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 256

char grid[SIZE][SIZE]={0},word[SIZE][SIZE]={0};
int row,col,wordcount,rowPointer=0,colPointer=0,colAvalable=0,rowAvalable=0;

typedef struct _{
    /*
        This words type has pointer and wordlist array. pointer indicate the last updated index of the wordlist.
    */
    int pointer;
    char wordlist[SIZE][SIZE];
}words;

typedef struct ___{
    char match[SIZE];
    int posibility;
}matchwords;

typedef struct __{
    int x;
    int y;
    int len;
    int blankPointer;
    //char wordmatch[SIZE][SIZE];
    matchwords wordmatch[SIZE];
}blanks;

words wordList[SIZE]={0,{0}};
blanks rowBlank[SIZE];
blanks colBlank[SIZE];

_Bool checkHash(int,int,_Bool,int*,blanks *,char);
void getInput();
void getWordLength();
_Bool input_validity(char *,int);
void matchWords();
void printWords();
void printBlanks();
_Bool validate();
void walkThroughGrid();

int main(){

    getInput();
    _Bool i = validate();
    //printf("%d %d\n",row,col);
    //printf("%d\n",wordcount);
    if (i){
        getWordLength();
        //printWords();
        walkThroughGrid();
        //printBlanks();
        matchWords();
        printBlanks();
    }
    return 0;
}

_Bool checkHash(int i,int j,_Bool sts,int *Point,blanks* Blank,char rc){
    int Pointer = *Point;
    if (grid[i][j] == '#'){
        if (sts){
            (Blank+Pointer)->len = (Blank+Pointer)->len + 1;
        }else{
            (Blank+Pointer)->len = (Blank+Pointer)->len + 1;
            (Blank+Pointer)->x = j;
            (Blank+Pointer)->y = i;
            sts = 1;
        }
        //printf("%d %d\n",i,j);
        //TODO: Check col or row when they are not equal
        if (((j+1)== row) & (rc == 'c')) {
            //printf("--x:%d y:%d len:%d %d\n",(Blank+Pointer)->x,(Blank+Pointer)->y,(Blank+Pointer)->len,Pointer);
            sts = 0;
            Pointer++;
        }
        if (((i+1)== col) & (rc == 'r')) {
            //printf("--x:%d y:%d len:%d %d\n",(Blank+Pointer)->x,(Blank+Pointer)->y,(Blank+Pointer)->len,Pointer);
            sts = 0;
            Pointer++;
        }
    }else{
        if (sts){
            //printf("x:%d y:%d len:%d %d\n",(Blank+Pointer)->x,(Blank+Pointer)->y,(Blank+Pointer)->len,Pointer);
            Pointer++;
        }
        sts = 0;
        //len = 0;
    }
    *Point = Pointer;
    //printf("%d\n",*Point);
    return sts;
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
    }
    return;
}

_Bool input_validity(char puzzle[],int len){
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

_Bool validate(){
    int len;
    col = strlen(grid[0]);

    do{
        len = strlen(grid[row]);
        _Bool sts = input_validity(grid[row],len);
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

void printWords(){
    int i;
    for (i=0;i<10;i++){
        for (int j=0;j<(wordList+i)->pointer;j++){
            printf("%s ",(wordList+i)->wordlist[j]);
        }
        printf("\n");
    }
    return;
}

void printBlanks(){
    int i;
    for (i=0;i<10;i++){
        //printf("x: %d y:%d len:%d pointer:%d\n",(colBlank+i)->x,(colBlank+i)->y,(colBlank+i)->len,(colBlank+i)->blankPointer);
        printf("x: %d y:%d len:%d pointer:%d\n",(rowBlank+i)->x,(rowBlank+i)->y,(rowBlank+i)->len,(rowBlank+i)->blankPointer);
    }
    return;
}

void walkThroughGrid(){
    _Bool rowsts = 0,colsts=0;
    int len=0;
    //TODO: What if row and col are not equal?
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            rowsts = checkHash(i,j,rowsts,&rowPointer,&rowBlank[0],'c');
            colsts = checkHash(j,i,colsts,&colPointer,&colBlank[0],row);
        }
    }
    return;
}

void matchWords(){
    int limit;

    if (rowPointer>colPointer){
        limit = rowPointer;
    }else{
        limit = colPointer;
    }

    for (int i=0;i<limit;i++){
        int rowlen = (rowBlank+i)->len,j;
        int collen = (colBlank+i)->len;
        //printf("row:%d col:%d\n",rowlen,collen);
        if (rowlen>1){
            rowAvalable++;
            for (j=0;j<(wordList+rowlen)->pointer;j++){
                printf("%d %s %d\n",rowlen,(wordList+rowlen)->wordlist[j],j);
                strcpy(((rowBlank+i)->wordmatch[j]).match,(wordList+rowlen)->wordlist[j]);
            }
            (rowBlank+i)->blankPointer = (wordList+rowlen)->pointer;
            //printf("%d\n",(rowBlank+i)->balnkPointer);
        }
        if (collen>1){
            colAvalable++;
            for (j=0;j<(wordList+collen)->pointer;j++){
                printf("%d %s %d\n",collen,(wordList+collen)->wordlist[j],j);
                strcpy(((colBlank+i)->wordmatch[j]).match,(wordList+collen)->wordlist[j]);
            }
            (colBlank+i)->blankPointer =(wordList+collen)->pointer;
            //printf("%d\n",(colBlank+i)->balnkPointer);
        }
    }

    printf("%d %d\n",rowAvalable,colAvalable);
    return;
}
