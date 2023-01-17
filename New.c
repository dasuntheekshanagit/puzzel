#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
char grid[4][5] = {"*#**","####","*#**","****"};

char words[4][4] ={"FLY","GLUE"};
int placed[20];
int num_of_words;



/*
    determines whether a given word from the words array can be placed on the crossword grid
    starting at position (row, col)
*/
int can_change(int row,int col,int word)
{
     int len = strlen(words[word]);

    if(placed[word] ==1)
        return 0;
     int k=0;

    int horizontal =1;
    int vertical = 2;
    for(k=0;k<len;k++)
    {
        if((grid[row+k][col] != '#' && grid[row+k][col] != words[word][k]))
            horizontal =0;

        if((grid[row][col+k] != '#' && grid[row][col+k]!=words[word][k]))
            vertical = 0;
    }
    //It returns 0 if the word cannot be placed, 1 if the word can be placed horizontally, and 2 if the word can be placed vertically.
    return horizontal+vertical;

}

/*
    places a given word from the words array on the crossword grid starting at position
    (row, col) with the orientation specified by the orientation variable
*/
void place_word( int row,int col,int orientation,int word)
{
    int k=0;
    int len = strlen(words[word]);
    for(k=0;k<len;k++)
    {
        if(orientation == 1)
          grid[row+k][col] = words[word][k];
        else
          grid[row][col+k] = words[word][k];
    }
    placed[word] = 1;

}
/*
    removes a given word from the crossword grid.
    It sets all the characters on the grid that were occupied by the word to the default '#' character.
*/
void restore_to_default( int row,int col,int orientation,int word)
{

    int k=0;
    int len = strlen(words[word]);
    for(k=0;k<len;k++)
    {
        if(orientation == 1)
          grid[row+k][col] = '#';
        else
          grid[row][col+k] = '#';
    }
    placed[word] = 0;

}

/*
a recursive function that tries to place all the words in the words array on the
crossword grid starting at position (row, col). It calls the can_change, place_word,
and restore_to_default functions to determine whether a word can be placed at a given
position and to actually place or remove the word.
*/

void fill_puzzle(int row,int col)
{
    //checks if the current row index is 4. If it is, the function returns without doing anything, as it has reached the end of the grid.
   if(row==4)
       return;


    int k;
    /*
        This for loop iterates through all the words in the words array. If it finds a word that has not been
        placed on the grid yet, it breaks out of the loop.
    */
     for(k=0;k<num_of_words;k++)
        if(placed[k] == 0)
         break;

    //checks if all the words in the words array have been placed on the grid. If they have, it prints the resulting crossword grid and returns.
     if(k==num_of_words)
     {
         for(row=0;row<4;row++)
            printf("%s\n",grid[row]);
         return;
     }

    /*
    checks if the current position on the grid is not an empty cell ('*').
    If it is not, the function tries to place each word in the words array that has not been placed yet,
    one by one, at that position.
    */

   if(grid[row][col] != '*')
   {
    // The function iterates through all the words in the words array that have not been placed yet.
      int change;
      for(k=0;k<num_of_words;k++)
      {
          //determine whether a particular word can be placed at the current position
         if((change=can_change(row,col,k))!=0)
         {
                place_word(row,col,change,k);
                int next_col = col+1;
                int next_row = next_col==4?row+1:row;
                fill_puzzle(next_row,next_col%4);
                restore_to_default(row,col,change,k);
            if(change==3)
             {
        /*
        If the current word can be placed both horizontally and vertically,
        the function places the word horizontally and calls the fill_puzzle function recursively
        */
                place_word(row,col,1,k);
                int next_col = col+1;
                int next_row = next_col==4?row+1:row;
                fill_puzzle(next_row,next_col%4);
                restore_to_default(row,col,1,k);
             }
         }
   }
   //if no word can be placed at the current position, move to the next position
       if(k==num_of_words)
           {
            int next_col = col+1;
                int next_row = next_col==4?row+1:row;
                fill_puzzle(next_row,next_col%4);
       }
   }

   //if the current position on the grid is an empty cell ('*'), move to the next position
   else{
                int next_col = col+1;
                int next_row = next_col==4?row+1:row;
                fill_puzzle(next_row,next_col%4);
   }

}





int main() {


    int row,k;

    row=0;

    num_of_words = 2;
    //memset(placed,0,num_of_words*sizeof(int));
    fill_puzzle(0,0);



    return 0;
}


