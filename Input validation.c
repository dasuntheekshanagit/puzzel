#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 4
//INPUTTING PUZZLE AND CHECKING
/*int main() {
	char puzzle[16],line[16];
	for(int i=0;i<4;i++) {
		scanf("%s",line);
		for(int j=0;j<4;j++){
            if (isalpha(line[j]) || line[j]=='#' || line[j] == '*' )
                *(puzzle+4*i+j) = line[j];
            else{
                printf("INVALID INPUT");
                return 0;
            }
	}
	}
    //printing puzzle
	for(int i = 0; i<16; i++){
        printf("%c ",puzzle[i]);
        if (i%4 == 3)
            printf("\n");
	}

    return 0;
}*/

int input_validity(char puzzle[]){
    int len = strlen(puzzle);
    for(int j=0;j<len;j++){
            if (isalpha(puzzle[j]) || puzzle[j]=='#' || puzzle[j] == '*' ){
                continue;
            }
            else{
                printf("INVALID INPUT");
                return 0;
            }
            }
        return 1;
}

int main(){
    char puzzle[16] = "####AB1D****#*#*";
    int validation = input_validity(puzzle);
    return 0;
}

