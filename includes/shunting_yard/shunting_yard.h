#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
#include <cstring>
#include <vector>
#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"
#include "../token/childtokens.h"
#include "../token/token.h"

using namespace std;

class shunting_yard
{
    public:
        shunting_yard(){}
        shunting_yard(vector<string> things) //basic constructor handles EVERYTHING
        {
            condition = things;
            tokenize();
            turn_into_postfix();

        }

        Queue<Token *> get_postfix (){return postfix;} //this will give over the postfix stuff

        void turn_into_postfix(); //only called in ctor

        void tokenize(); //this i really only call in constrcture so?? no args needed?
        void print_queue(); //testingggggggggg


    private:
        Stack<Token *> rlstack; //holds relationals, logicals, and parentheses
        Queue<Token *> postfix; //will hold solutions and tokenstrs, this is what we will pass to rpn
        vector<string> condition; // this will be passed in or somehow i fill this (it will always be passed in)
        vector <Token* > tokenized; // this will hold tokenized results of condition (the vectorstr we pass in)

};






#endif