#include "state_machine_functions.h"
//2d array [row][column] = { {1,2} , {2,3} }
//Fill all cells of the array with -1
void init_table(int _table[][MAX_COLUMNS]){
    for (int rows = 0; rows < MAX_ROWS; rows++)
    {
        for (int columns = 0; columns < MAX_COLUMNS; columns++)
        {
            _table[rows][columns] = -1;
        }
    }
}

//Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 1;
}

//Mark this state (row) with a 0 (fail)
// fail is bad name, fail is mid state/not yet completed state
void mark_fail(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 0;
}

//true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state)
{
    if (_table[state][0] == 1)
    {
        return true;
    }
    //unused rows can be -1
    // take into account

    return false;
}

//Mark a range of cells in the array. 
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state)
{ // include to, dont use less than identifier
    for (int i = from; i <= to; i++)
    {
        _table[row][i] = state;
    }
}

//Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state){
    const char* ptr = columns;
    while( *ptr != '\0')
    {
        _table[row][*ptr] = state;
        ptr++;
    }
}

//Mark this row and column
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state){
    table[row][column] = state;
}

//This can realistically be used on a small table
void print_table(int _table[][MAX_COLUMNS])
{
    // check specific mark_cell
    /*
    int row = 0; //edit as needed
    int column = 0; // edit as needed
    cout << _table[row][column] << endl;
    */


   //check wide range mark_cell
   /*
   int row = 0; // edit as needed
   int from = 1; // edit as needed
   int to = 10;// edit as needed
   for (int i = from; i <= to; i++)
   {
        cout << _table[row][i] << "\t";
        if (i % 10 == 0) // new line if 10 values are outputted (easier formatting?)
        {
            cout << endl;
        }
   }
   cout << endl;
    */

   /*
   //check string columns[] mark_cell
   int row = 0; // change as needed
   int format = 0;
   const char* check = ALFA; // change right side of = as needed for tests
   while (*check != '\0')
   {
        cout << _table[row][*check] << '\t';
        format++;
        check++;
        if (format % 5 == 0 )
        {
            cout << endl;
        }
   }
   cout << endl;
   */
  
  //print everything
  
    for (int i = 0; i < MAX_ROWS; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            cout << _table[i][j] <<  " ";
        }
        cout << endl;
    }
    

}

//show string s and mark this position on the string:
//hello world   pos: 7
//       ^
void show_string(char s[], int _pos)
{
    cout << endl;
    int i = 0;
    while (i != '\0') //print string
    {
        cout << s[i];
        i++;
    }
    cout << "   pos: " << _pos << endl; // print pos on same line as string
    cout << setw(_pos) << "^"; // after printing newline, jump to spot and mark with a '^' char
}