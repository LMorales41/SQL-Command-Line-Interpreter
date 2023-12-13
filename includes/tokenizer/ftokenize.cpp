#include "ftokenize.h"

FTokenizer::FTokenizer(char* fname)
{

    STokenizer s;
    _stk = s;
    _pos = 0;
    _blockPos = 0;
    _more = true;
}

Token FTokenizer::next_token()
{
    Token t;
    return t;
}
bool FTokenizer::more()
{
    return true;
}        //returns the current value of _more
int FTokenizer::pos(){
    return 1;
}          //returns the value of _pos
int FTokenizer::block_pos()
{
    return 1;
}    //returns the value of _blockPos
FTokenizer& operator >> (FTokenizer& f, Token& t)
{

    return f;
}

bool FTokenizer::get_new_block()
{
    return true;
} //gets the new block from the file