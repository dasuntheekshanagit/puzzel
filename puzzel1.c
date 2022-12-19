#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256
#define FILES 3

void getFile(int);

int main(){
    int fileCount;

    for (fileCount=1;fileCount<=FILES;fileCount++){
        getFile(fileCount);
    }
    return 0;
}

void getFile(int i){
    char puzzelFile[SIZE]="puzzel",wordFile[SIZE]="word",no[2];

    itoa(i,no,10);

    strcat(puzzelFile,no);
    strcat(puzzelFile,".txt");

    strcat(wordFile,no);
    strcat(wordFile,".txt");
    printf("Puzzle: %s\n",puzzelFile);
    printf("Words:  %s\n",wordFile);

    return;
}
