/*Douglas Nedza CS 370 Amos Confer
Target: GNU GCC Compiler
Purpose: This program inputs values for two static arrays and outputs the sum of the matrices
Process: This program uses functions and for loops to manipulate the array elements.
Inputs: The user will input the entries for the static matrices.
Output: This program outputs the sum of the matrices whose entries are input by the user.*/


#include <iostream>

using namespace std;

#define ROW 4
#define COL 3

typedef int intArray[ROW][COL];

void get_input(intArray a);
void output_matrix(intArray a);
void path_trace(intArray a);
void card_movement(intArray a);

/*Purpose: This function queries inputs from the user for a static matrix defined by global constant dimensions.
Process: This function uses a for loop to cycle through the matrix rows and columns.
Input: This function queries the user for (row)*(col) integer entries from the user.
Output: This function returns an array filled with user determined integer entries.*/
void get_input(intArray a)
{
    int i = 0, j = 0;
    cout<<"Enter the integers for the first "<<ROW<<" x "<<COL<<" matrix."<<endl;
    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            cin>>a[i][j];
        }
    }
}
/*Purpose: This function outputs the entries of a matrix organized by row and column
Process: This function uses a for loop to cycle through the matrix entries, printing all entries in a row before going to the next line.
Input: This function takes as input a matrix with integer entries.
Output: This function outputs the entries of a matrix in row column order.*/
void output_matrix(intArray a)
{
    int i = 0, j = 0;
    cout<<"Matrix Output."<<endl;
    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}

/* Purpose: This function outputs the ending path, which would correspond to the market connected to the path.
Process: This function uses a for loop that cycles through the columns of the relative change matrix, summing the path changes to map to the ending path
Input: This function takes as input the matrix, with integer entries
Output: This function outputs the ending path height
*/
void path_trace(intArray a)
{

    int col = 0, j = 0, path = 0, endpath = 0, beginpath = 0;
    cout<<"Input Current Column."<<endl;
    cin>>col;
    cout<<"Current Column "<<col<<endl;
    cout<<"Input Current Path."<<endl;
    cin>>path;
    cout<<"Current Path. "<<path<<endl;
    endpath = path;
    for( int i = col; i < COL; i++)
    {
        endpath = endpath + a[endpath][i];
    }
    cout<<" The ending path is "<<endpath<<"."<<endl;

    beginpath = path;
    if( col > 0 )
    {
        for( int i = ( col - 1 ); i > -1; i-- )
        {
            j = 0;
            while(beginpath != j + a[j][i] )
            {
                j++;
            }
            beginpath = j;
        }
    }
    cout<<"The beginning path is "<<beginpath<<"."<<endl;
}
/*
Purpose: This function inputs the relative path change matrix and a corresponding column number.  The function then increments the postition of
all integers in that column by one row, corresponding to the movement of a card by 1 path.
Process: Save the first entry (top), for loop to cycle through the rows. Place the saved value in the bottom entry (wrap the matrix).
Input: The relative path change integer matrix, integer representing the column to be modified
Output: Modifies the path matrix outside of the function
*/
void card_movement( intArray a, int col )
{
    int temp = a[0][col];
    for( int i = 0; i < (ROW - 1); i++ )
    {
        a[i][col] = a[i+1][col];
    }
    a[ROW - 1][col] = temp;

}


int main()
{
    int col = 0;
    intArray a;
    get_input(a);
    output_matrix(a);
    for(int i = 0; i < 5; i++)
    {
         path_trace(a);
    }
    cout<<"In which column did the card move?"<<endl;
    cin>>col;
    card_movement( a, col );
    output_matrix(a);


    return 0;
}
