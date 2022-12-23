#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 256

char grid[SIZE][SIZE]={0},word[SIZE][SIZE]={0};                                          // Store the Puzzele Grid and Words in 2D array
int row,col,wordcount,rowPointer=0,colPointer=0,colAvalable=0,rowAvalable=0,impossible=0;
_Bool available[SIZE];                                                                   // To track a word is available of used to fill the grid


typedef struct ___{
    /*
        match      : Store the word that matched to a particular blank in the grid.
        index      : Index of the words in available list.
        possibility: Store the value of possibility that word match to particular blank.
    */
    char match[SIZE];
    int index;
    int possibility;
}matchwords;

typedef struct _{
    /*
        pointer  : Indicate how many elements in the wordlist
        wordlist : Store array of matchwords objects
    */
    int pointer;
    matchwords wordlist[SIZE];
}words;

typedef struct __{
    /*
        x        : Store the position of the col no.
        y        : Store the position of the row no.
        len      : Store the length of the blank.
        wordmatch: Store the all possible words match to the length as objects of matchwords.
    */
    int x;
    int y;
    int len;
    int blankPointer;
    matchwords wordmatch[SIZE];
}blanks;

words wordList[SIZE];  // word array. This is used to store words that have similar length. Position of the object is equal tot the length of the word.
blanks rowBlank[SIZE]; // blanks array. This is used to store row blanks with its details.
blanks colBlank[SIZE]; // blanks array. This is used to store column blanks with its details.

_Bool addToGrid(int,int,char*,int,int);             // Used to add the words to grid column wise.
_Bool checkToGrid(int,int,char*,int,int);             // Used to add the words to grid row wise.
_Bool checkHash(int,int,_Bool,int*,blanks *,char); // Used to get length of blanks with its position.
void deleteElement(int,matchwords*);
int findCharacter(int,int,int,int,char*);
_Bool fillOnePossible(blanks *,int);               // Used to fill the blanks that have only one possible value.
void getInput();                                   // Used to get user input as grid and words.
void getWordLength();                              // Used to find the length of each word in the array.
_Bool input_validity(char *,int);                  // Used to check whether they are characters other than #,* and letters.
_Bool increaseProbability(blanks*,int);
_Bool matchWords();                                // Used to match the word to blanks by considering there length.
void printBlanks();                                // Used to print the row and column blank objects.
void printGrid();                                  // used to print the grid.
void printWords();                                 // used to print the word object in the word list.
_Bool validate();                                  // Used to validate user input.
void walkThroughGrid();                            // Used to go through the grid and find the blanks.

int main(){
    /*
        main function

    */
    getInput();
    if (validate()){
        getWordLength();
        //printWords();
        walkThroughGrid();
        //printBlanks();
        if(matchWords()){
             //printBlanks();
            _Bool y = fillOnePossible(&rowBlank[0],1);
            _Bool x = fillOnePossible(&colBlank[0],0);
            if (!((impossible>0) & x & y)){                 // Check whether grid can fill or not.
                //printGrid();
            //}else{
                printf("IMPOSSIBLE\n");
                return 0;
            }
            //printf("%d %d\n\n",rowAvalable,colAvalable);
            /*if ((rowAvalable+colAvalable)<1){
                    return 0;
            }*/
            //printGrid();
            //printBlanks();
            //printf("fil\n");
            increaseProbability(&rowBlank[0],1);
            //printBlanks();
            //printf("row\n");
            increaseProbability(&colBlank[0],0);
            //printGrid();
            //printBlanks();
            //printf("prob--\n");
            int i = 0;
            while (rowAvalable+colAvalable){
                //printf("%d\n",rowAvalable+colAvalable);
                printGrid();
                printBlanks();
                //printf("\n%d\n",i);
                if (i>15){
                    break;
                }
                _Bool y = fillOnePossible(&rowBlank[0],1);
                _Bool x = fillOnePossible(&colBlank[0],0);
                increaseProbability(&rowBlank[0],1);
                increaseProbability(&colBlank[0],0);
                i++;
            }
            printGrid();
            printf("%d %d\n",i,rowAvalable+colAvalable);
        }
    }
    return 0;
}

//TODO: both functions can merge with rc value.
_Bool addToGrid(int x,int y,char match[],int len,int rc){
    /*
        Input:
            x    : column no.
            y    : row no.
            match: word add to grid to fill.
            len  : length of the word.
        Output:
            bool : Possible to fill or not.
        Function:
            Fill the grid by going column wise.if there is a letter already in the grid and its not match with
            the words character that fill to that position return 1, else return 1.
    */
    //printf("%d %d %d %s\n",x,y,len,match);
    char check;

    for (int i=0;i<len;i++){
        /*if (rc){
            check = grid[y][x+i]; // Row
        }else{
            check = grid[y+i][x]; //Col
        }
        //printf("%c-%d ",grid[y+i][x],i);
        if (isalpha(check)){
            if (check == match[i]){
                continue;
            }else{
                //printf("----%c %c-----\n",grid[y+i][x],match[i]);
                impossible = 100;
                return 1;
            }
        }*/
        if (rc){
            grid[y][x+i] = match[i]; // Row
        }else{
            grid[y+i][x] = match[i]; // Col
        }

    }
    //printf("\n");
    return 0;
}

_Bool checkToGrid(int x,int y,char match[],int len,int rc){
    /*
        Input:
            x    : column no.
            y    : row no.
            match: word add to grid to fill.
            len  : length of the word.
        Output:
            bool : Possible to fill or not.
        Function:
            Fill the grid by going row wise.if there is a letter already in the grid and its not match with
            the words character that fill to that position return 1, else return 1.
    */
    //printf("%d %d %d %s\n",x,y,len,match);
    char check;

    for (int i=0;i<len;i++){
        if (rc){
            check = grid[y][x+i]; // Row
        }else{
            check = grid[y+i][x]; //Col
        }
        //printf("%c-%d ",grid[y+i][x],i);
        if (isalpha(check)){
            if (check == match[i]){
                continue;
            }else{
                //printf("----%c %c-----\n",grid[y+i][x],match[i]);
                impossible = 100;
                return 1;
            }
        }
    }
    addToGrid(x,y,match,len,rc);
    //printf("\n");
    return 0;
}

_Bool checkHash(int i,int j,_Bool sts,int *Point,blanks* Blank,char rc){
    /*
        Input:
            i     : row no
            j     : col no
            sts   : If its not the first blank space in that blank 0, else 1.
            *Point: index of the blank list (rowBlank/colBlank).
            Blank : memory address of first element in blanks array to add the object (rowBlank/colBlank).
            rc    : to indicate whether its row or blank
        Output:
            _Bool : return the sts
        Function:
            Go though the grid and check position on the grid whether it is # or alpha. If its
            count the length of the blank and store it with the position of it it blanks arrays.
    */

    int Pointer = *Point;
    if (grid[i][j] == '#' | isalpha(grid[i][j])){
        if (sts){
            (Blank+Pointer)->len = (Blank+Pointer)->len + 1;  // If this blanks is not the first blank in space continue countinue.
        }else{
            (Blank+Pointer)->len = (Blank+Pointer)->len + 1;  // Else get the position of the blank and store it in blank array
            (Blank+Pointer)->x = j;                           // while indication blank is start by changing sts to 1.
            (Blank+Pointer)->y = i;
            sts = 1;
        }

        // TODO: Check col or row when they are not equal.
        // TODO: check r and c are correct.   Note: Corrected it by changing row and col
        if (((j+1)== col) & (rc == 'c')) {               // Check whether is it the last position of the row.
            sts = 0;
            Pointer++;                                   // If it is move the pointer to next position and break the counting.
        }
        if (((i+1)== row) & (rc == 'r')) {               // Check whether is it the last position of the col.
            sts = 0;
            Pointer++;                                   // If it is move the pointer to next position and break the counting.
        }
    }else{
        if (sts){
            // TODO: Bug: Pointer will jump even if its a start. Not even its end of the blank. It will be at least no of row or columns. Check can this reduced.
            // Maybe can use a variable like sts.
            Pointer++;                                    // Jump the pointer and end the counting blank length when * is founded.
        }
        sts = 0;                                          // Change sts to 0 to indicate blank is not stated.
    }
    *Point = Pointer;                                     // pass the value of pointer to col pointer or row pointer.
    return sts;
}


void deleteElement(int i,matchwords *arr){
    for (int j=i;j<5;j++){
        //TODO: Find another way to do this.
        //printf("--%s\n",((arr+j)->match));
        strcpy(((arr+j)->match), ((arr+j+1)->match));
        (arr+j)->index = (arr+j+1)->index;
        (arr+j)->possibility = (arr+j+1)->possibility;
    }
    return;
}

int findCharacter(int x,int y,int len,int rc,char text[]){
    char c;
    int possibility=0;

    for (int i=0;i<len;i++){
        if (rc){
            c = grid[y][x+i];
        }else{
            c = grid[y+i][x];
        }
        //printf("%c-% c",c,text[i]);
        if (isalpha(c)){
            if (c==text[i]){
                possibility += (100/len);
            }else{
                //printf("-1 (%d %d)%s",x,y,text);
                return -1;
            }
        }
    }
    return possibility;
}

_Bool fillOnePossible(blanks *Blank,int r){
    /*
        Input:
            blanks: memory address of first element of blank array
            r     : Indicate row or column. If row r = 1, else r = 0.
        Output:
            _Bool : Return 0 if its successfully word is added to grid without conflict, else return 1.
        Function:
            If go thorough the blank array and find if there is only one possible match to that blank fill it.
    */

    int index;
    for (int i=0;i<SIZE;i++){
        impossible = impossible+(Blank+i)->blankPointer;                    // Sum the available possibilities to fill the grid. If there is no
        if ((Blank+i)->blankPointer == 1){                                // matches for the hole grid this will be 0.
            index = ((Blank+i)->wordmatch)->index;                        // If there is only one match
            if (available[index] == 0){                                   // and that word is not used by other blank to fill
                //if (r == 1){                                              // fill that word in the blank for the grid.
                    if (checkToGrid((Blank+i)->x,(Blank+i)->y,((Blank+i)->wordmatch)->match,(Blank+i)->len,r)){
                        ((Blank+i)->wordmatch)->possibility = 100;        // Indicate that blank is filled with best match
                        return 0;                                         // If successfully filled that blank without conflict return 0.
                    }
                    available[index] = 1;
                    rowAvalable-=1;
                    //printf("--%d\n",rowAvalable);                             // Indicated that word is used to filled and no longer available.
                /*}else{
                    if (checkToGrid((Blank+i)->x,(Blank+i)->y,((Blank+i)->wordmatch)->match,(Blank+i)->len,0)){
                        ((Blank+i)->wordmatch)->possibility = 100;
                        return 0;
                    }
                    available[index] = 1;
                    colAvalable-=1;
                    //printf("--%d\n",rowAvalable);
                }*/
                // Note: Tow lines are moved to 212-213 and 218-219.
            }else{
                //TODO: impossible = 0; is removed. Check whether its affected to further modifications.
            }
        }
    }
    return 1;
}

void getInput(){
    /*
        Function:
            get user input and store them in grid and word array. Get user input until enter blank new line.
    */

    char line[SIZE]= {0};
    int pointer = 0;

    while (scanf("%[^\n]%*c",line) != 0){                 // Loop until get user enter new line.
        strcat(grid[pointer],line);                       // Copy user input string to grid.
        pointer++;                                        // Increase the pointer to store next line.
    }

    scanf("%*c",line);                                    // Get new line

    pointer = 0;

    while (scanf("%[^\n]%*c",line) != 0){
        strcpy(word[pointer],line);
        pointer++;
    }

    wordcount = pointer;                                 // Get no of words.

    return ;
}

void getWordLength(){
    /*
        Function:
            Iterate trough the word list and get length of words. The words have same length are stored in words type array with
            corresponding length. Index of the word is the length of the word.
        EX: - cat, dog, fish
            wordlist = [0:[],0:[],0:[],2:['cat',''dog'],1:['fish']]
    */

    for (int i=0;i<wordcount;i++){                                // Iterate all words
        int len = strlen(word[i]);                                // get length
        int point = (wordList+len)->pointer;
        (wordList+len)->pointer = point + 1;                      // Increase the pointer always when adding a new word.
        //printf("%d\n",(wordList+len)->pointer);  //Note: Word pointer
        strcpy(((wordList+len)->wordlist[point]).match,word[i]);
        ((wordList+len)->wordlist[point]).index = i;              // Store the index of the word in the matchword object.
    }
    return;
}

_Bool input_validity(char puzzle[],int len){
    /*
        Input:
            puzzle: word to check
            len   : length of the word
        OutPut:
            _Bool : If valid input return 1, else 0.
        Function:
            Iterate through grid and check whether it contain invalid character other than #,* and letters.
    */

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

_Bool increaseProbability(blanks *Blank, int r){
    int c=10;
    for (int i=0;i<SIZE;i++){
        int pointer = (Blank+i)->blankPointer;
        if (pointer>1){
            for (int j=0;j<pointer;j++){
                int possibility = (((Blank+i)->wordmatch)+j)->possibility;
                //TODO: If possibility > 90 get that value and stop oteration.
                int index = (((Blank+i)->wordmatch)+j)->index;
                /*if (available[index]){
                    printf("--%d %s",pointer,(((Blank+i)->wordmatch)+j)->match);
                    (Blank+i)->blankPointer -=1;
                    deleteElement(j,(Blank+i)->wordmatch);
                //}else{*/
                    if (strlen((((Blank+i)->wordmatch)+j)->match)>0){
                        c = findCharacter((Blank+i)->x,(Blank+i)->y,(Blank+i)->len,r, (((Blank+i)->wordmatch)+j)->match);
                    }
                //}
                //printf("%d %p %d %p\n",c,(Blank+i)->wordmatch,i,(Blank+i)->wordmatch+1);
                if (c<0){
                    //printf("before: %d ",(Blank+i)->blankPointer);
                    (Blank+i)->blankPointer -=1;
                    //printf("after: %d ",(Blank+i)->blankPointer);
                    deleteElement(j,(Blank+i)->wordmatch);
                    c = 10;
                    //printf("delete %d \n",(Blank+i)->blankPointer);
                }
            }
        }
    }
    return 1;
}

_Bool validate(){
    /*
        Output:
            _Bool : Return 1 if there are invalid character in the grid, else 0.
    */

    //TODO: What if column entered are not equal.
    int len;
    col = strlen(grid[0]);                           // Get the no of columns in the grid

    do{
        len = strlen(grid[row]);
        _Bool sts = input_validity(grid[row],len);   // Check the validity of the row.
        if (!sts){
            printf("INVALID INPUT\n");               // If invalid row, indicate and break.
            return sts;
        }

        row++;
    }
    while (len > 0);                                 // Iterate until end of the row.

    row--;                                           // Row no is increase than one.So decreased it.

    return 1;
}

void printGrid(){
    /*
        Function:
            Print the grid.
    */

    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            printf("%c",grid[i][j]);
        }
        printf("\n");
    }
    return;
}

void printBlanks(){
    /*
        Function:
            Print the elements in row blank or col blank.
    */

    int i;
    for (i=0;i<20;i++){                                           // Note: 10 is just to get first 10 elements. Its can be changed.
        //printf("x: %d y:%d len:%d pointer:%d\n",(colBlank+i)->x,(colBlank+i)->y,(colBlank+i)->len,(colBlank+i)->blankPointer);
        printf("x: %d y:%d len:%d pointer:%d\n",(rowBlank+i)->x,(rowBlank+i)->y,(rowBlank+i)->len,(rowBlank+i)->blankPointer);
    }
    return;
}

void printWords(){
    /*
        Function:
            print the words in wordList.
    */

    int i;
    for (i=0;i<10;i++){                                          // Note: 10 is just to get first 10 elements. Its can be changed.
        for (int j=0;j<(wordList+i)->pointer;j++){
            printf("%s ",((wordList+i)->wordlist[j]).match);
        }
        printf("\n");
    }
    return;
}

void walkThroughGrid(){
    /*
        Function:
            Iterate through grid and get the length of blanks and their position.
    */

    _Bool rowsts = 0,colsts=0;                         // Store the status of the function return.
    int iterate;

    if (row>=col){
        iterate = row;
        //printf("row--%d %d",row,col);
    }else{
        iterate = col;
        //printf("col-%d %d",row,col);
    }

    //TODO: What if row and col are not equal?
    for (int i=0;i<iterate;i++){
        for (int j=0;j<col;j++){
            rowsts = checkHash(i,j,rowsts,&rowPointer,&rowBlank[0],'c');
            colsts = checkHash(j,i,colsts,&colPointer,&colBlank[0],'r');
        }
    }
    return;
}

_Bool matchWords(){
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
            //for (j=0;j<(wordList+rowlen)->pointer;j++){
                //printf("%d %s %d\n",rowlen,(wordList+rowlen)->wordlist[j],j);
                //strcpy(((rowBlank+i)->wordmatch[j]).match,(wordList+rowlen)->wordlist[j]);
            memcpy((rowBlank+i)->wordmatch,(wordList+rowlen)->wordlist,sizeof((wordList+rowlen)->wordlist));
            //}
            (rowBlank+i)->blankPointer = (wordList+rowlen)->pointer;
            //printf("%d\n",(rowBlank+i)->balnkPointer);
        }
        if (collen>1){
            colAvalable++;
            //for (j=0;j<(wordList+collen)->pointer;j++){
                //printf("%d %s %d\n",collen,(wordList+collen)->wordlist[j],j);
                //strcpy(((colBlank+i)->wordmatch[j]).match,(wordList+collen)->wordlist[j]);
            memcpy((colBlank+i)->wordmatch,(wordList+collen)->wordlist,sizeof((wordList+rowlen)->wordlist));
            //}
            (colBlank+i)->blankPointer =(wordList+collen)->pointer;
            //printf("%d\n",(colBlank+i)->balnkPointer);
        }
    }

    //printf("%d %d %d\n",rowAvalable,colAvalable,wordcount);
    if ((rowAvalable+colAvalable) < wordcount){
        printf("IMPOSSIBLE\n");
        return 0;
    }
    return 1;
}
