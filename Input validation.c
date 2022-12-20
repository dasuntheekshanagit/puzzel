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
    char puzzle[16] = "*****#**####*#**";
    /*
        ****    ****
        *#**    *F**
        ####    GLUE
        *#**    *Y**

    */
    char words[4][4] = {"GLUE", "FLY"};
     // Declare the two-dimensional array
    char puzzle_2d[4][4];

    // Iterate over the elements of puzzle and assign them to the elements of words
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            puzzle_2d[i][j] = puzzle[i * 4 + j];
        }
    }

    // Print the two-dimensional array
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%c ", puzzle_2d[i][j]);
        }
        printf("\n");
    }
    // Initialize counters for the number of # along the vertical and horizontal axis
    int vertical_count = 0;
    int horizontal_count = 0;

    // Initialize variables to store the maximum number of # in each row and column
    int row_max[4] = {0};
    int col_max[4] = {0};

    // Iterate over the elements of the array and count the # characters
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (puzzle_2d[i][j] == '#') {
                vertical_count++;
                row_max[i]++;
                col_max[j]++;
            }
            if (puzzle_2d[j][i] == '#') {
                horizontal_count++;
            }
        }
    }

    // Print the results
    printf("Number of # along the vertical axis: %d\n", vertical_count);
    printf("Number of # along the horizontal axis: %d\n", horizontal_count);
    printf("Maximum number of # in each row: %d %d %d %d\n", row_max[0], row_max[1], row_max[2], row_max[3]);
    printf("Maximum number of # in each column: %d %d %d %d\n", col_max[0], col_max[1], col_max[2], col_max[3]);

    return 0;
}

