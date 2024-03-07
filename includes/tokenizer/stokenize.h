#ifndef stokenize_h
#define stokenize_h
#include <cstring>
#include "constants.h"
#include "../token/token.h"
#include "state_machine_functions.h"
using namespace std;


class STokenizer
{
public:
    STokenizer(); ////
    STokenizer(char str[]);
    bool done();            //true: there are no more tokens
    bool more();            //true: there are more tokens
    //

    //---------------
    //extract one token (very similar to the way cin >> works)
    friend STokenizer& operator >> (STokenizer& s, Token& t);

    //set a new string as the input string
    void set_string(char str[]);


private:
    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)



    bool get_token(int& start_state, string& token);
    void make_table(int _table[][MAX_COLUMNS]);
    void make_table2(int _table[][MAX_COLUMNS]); //table for 
    static int _table[MAX_ROWS][MAX_COLUMNS];

    //extract the longest string that match
    //     one of the acceptable token types

    //---------------------------------
    char _buffer[MAX_BUFFER];       //input string
    int _pos;                       //current position in the string
    bool _done;
};

#endif