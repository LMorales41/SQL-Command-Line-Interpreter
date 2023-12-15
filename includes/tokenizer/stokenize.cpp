#include "stokenize.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer(){
    _pos = 0;
    _buffer[0] = 't';
    _buffer[1] = 'e';
    _buffer[2] = 's';
    _buffer[3] = 't'; //dummy values since this operator is not called in original stokenizer test
    make_table2(_table);
    _done = false; // done value for more and done

}
STokenizer::STokenizer(char str[]){
    int i =0;
    while (str[i]!= '\0')
    {
        _buffer[i] = str[i]; //copies char by char
        i++;
    }
    _buffer[i] = str[i]; //must copy null char at end
    make_table2(_table); //initialize table
    _pos = 0;
    _done = false;
}
bool STokenizer::done()
{   
 return _done;
}           //true: there are no more tokens
bool STokenizer::more()
{
 return !_done;
}            //true: there are more tokens
//

//---------------
//extract one token (very similar to the way cin >> works)
STokenizer& operator >> (STokenizer& s, Token& t)
{
    //get token gets called
    int start_state = 0;
    string tok = ""; //intialize two variables to be used by get token and token constructor
    int type = 0;
    if (s._buffer[s._pos] == '\0') //happens before get token call or else final character not grabbed
    {
        s._done = true; //done once null character is found
        //s._pos++;
        return s;
    }
    //call get token
    s.get_token(start_state, tok);
    //cout << s._buffer[s._pos] << endl;
    t = Token (tok, start_state); //sets the values retrieved from get_token to token
    return s;
}

//set a new string as the input string
void STokenizer::set_string(char str[])
{
    int i = 0;
    while (str[i] != '\0') //set string character by character
    {
        _buffer[i] = str[i];
        i++;
    }
    _buffer[i] = str[i]; //copy null value at the end
}


//create table for all the tokens we will recognize
//                      (e.g. doubles, words, etc.)
void STokenizer::make_table2(int _table[][MAX_COLUMNS])
{
    init_table(_table); 
    //fail states/not success states
    mark_fail(_table, 0);
    

    //success states
    mark_success(_table, 1);
    mark_success(_table, 2);
    mark_success(_table, 3);
    mark_success(_table, 4);
    mark_success(_table, 10);
    mark_success(_table, 20);
    mark_success(_table, 30);
    mark_success(_table, 31);
    //mark_success(_table, 30);
    //what state each char will lead to
    mark_cells (0, _table, ALFA, 1);
    mark_cells(0, _table, DIGITS, 2);
    mark_cells(1, _table, ALFA, 1);
    mark_cells(2, _table, DIGITS, 2);
    mark_cells(0, _table, PUNC, 3);
    mark_cells(3, _table, PUNC, 3);
    mark_cells(0, _table, SPACES, 4);
    mark_cells(4, _table, SPACES, 4);
    mark_cells (0, _table, OTHER, 10 );
    mark_cells (10, _table, OTHER, 10);
    mark_cells(0, _table, OPERATORS, 20);
    mark_cells(20, _table, OPERATORS, 20);
    char quotes = '"';
    char singlequote = '\'';
    char period = '.';
    char hyphen = '-';
    mark_cell (0, _table, quotes, 30);
    mark_cells (30, _table, ALFA, 30);
    mark_cells(30, _table, SPACES, 30);
    mark_cell (30, _table, period, 30);
    mark_cells(30, _table, DIGITS, 30);
    mark_cell (30, _table, singlequote, 30);
    mark_cell (30, _table, hyphen, 30);
    // mark_cell (31, _table, quotes, 30);




}
void STokenizer::make_table(int _table[][MAX_COLUMNS])
{
    init_table(_table); 
    //fail states/not success states
    mark_fail(_table, 0);
    mark_fail (_table, 5); 

    //success states
    mark_success(_table, 1);
    mark_success(_table, 2);
    mark_success(_table, 3);
    mark_success(_table,4);
    mark_success(_table, 6);

    
    //what state each char will lead to
    mark_cells (0, _table, ALFA, 1);
    mark_cells (0, _table, DIGITS, 2);
    mark_cells (0, _table, SPACES, 3);
    mark_cells (0, _table,PUNC, 4);
    mark_cells (1, _table, ALFA, 1);
    mark_cells (2, _table, DIGITS, 2);
    char period = '.'; //turned into period variable
                       //directly inserting '.' did not play well with function
    mark_cell (2, _table, period, 5);
    mark_cells (5, _table, DIGITS, 6);
    mark_cells (6, _table, DIGITS, 6);
    mark_cells (3, _table, SPACES, 3);
    mark_cells(4, _table, PUNC, 4);

}

//extract the longest string that match
//     one of the acceptable token types
bool STokenizer::get_token(int& start_state, string& token)
{
    //use an iterator instead of pos and make pos what last_succes was?

    char* walker = _buffer + _pos;
    start_state = 0;
    int row;
    int column;
    int last_success;
    int success;
    string holder = "";

    //add a holder string 
    //cout<<"start pos:"<<_pos<<endl; 
    //cout<<"start char: "<<_buffer[_pos]<<endl; 
    
    //cout<<_buffer[_pos]<<endl;
    while (row != -1 && *walker != '\0')
    {

        // ROW = STATE // row = [THIS IS ROW][THIS IS COLUMN]
        row = start_state; //row is same thing as start_state
        column = *walker; //column is same thing as *walker
        // row/column not necessary, just for easier reading

        holder += *walker; //add character to holder every time
        row = _table[row][column]; // set row(the state) to wherever the char takes me to



        //cout << "table:" <<_table[row][column] << endl;
        //cout << success << endl;

        //cout <<"row:"<< row << endl;
        //cout << "column" << column << endl;
        //cout<<"char: "<<_buffer[_pos]<<endl; 
        //cout<<"state: "<<row<<endl; 
    
        if (is_success(_table, row))
        {
            //cout << *walker << "=" << _buffer[_pos] << endl;
            //cout << column << endl;


            start_state = row; // will return a start_state for outputting data type in t._type;
            token = holder;
            last_success = _pos; //position is one to the right of our last success

            //cout<<"token: "<<token<<endl; 
            //cout << "success state reached @  position:" << _pos << endl;
        }


        //_pos++;
        //cout<<"char: "<<_buffer[_pos]<<endl; 


        _pos++;
        walker++; //increase walker and pos by 1 each time to go through the string
    }
    _pos = last_success + 1; //moves pos after a fail

    //cout<<"last char: "<<_buffer[_pos]<<endl; 
    if (_pos==0)// pos only does not move when an unknown character is read
    //this will thus only return false during this exception and then move pos by 1 to skip that char
    {
        _pos++;

        return false;
    }
    else {

        return true;
    }
    return true;
}
//---------------------------------