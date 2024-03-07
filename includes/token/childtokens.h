#ifndef CHILDTOKENS_H
#define CHILDTOKENS_H
#include <cstring>
#include <iostream>
#include "token.h"
#include <vector>


class Logical : public Token
{
    public:
    Logical (){}
    Logical (string oper) : Token (oper, TokenType::LOGICAL)
    {
        _string = oper;
        if (oper == "and")
        {
            precedence = 3;
        }
        else
        {
            precedence = 2;
        }
        
    }
    int get_precedence(){return precedence;}
    string get_string(){return _string;}
    
    friend ostream& operator<<(ostream& os, const Logical& logical) {
    os << "Logical Token: " << logical._string;
    return os;
    }
        
    private:
        int precedence;
        string _string;
    


};

class Relational : public Token
{
    public:
        Relational () {}
        Relational (string relate) : Token(relate, TokenType::RELATIONAL)
        {
            _string = relate;
        }
        int get_precedence(){return precedence;}
        string get_string(){return _string;}
        friend ostream& operator<<(ostream& os, const Relational& relational) {
        os << "Relational Token: " << relational._string;
        return os;
        } 
    private: 
        int type;
        int precedence = 4;
        string _string;

};

class TokenStr : public Token
{

    public:
        TokenStr(){}
        TokenStr(string tokenstr) : Token (tokenstr, TokenType::TOKENSTR)
        {
            _string = tokenstr;
        }
        virtual int get_precedence()
        {
        cout << "this is calling Tokenstr" << endl;
        return 0;
        }
        string get_string(){return _string;}
        friend ostream& operator<<(ostream& os, const TokenStr& tokenStr) {
        os << "TokenStr: " << tokenStr._string;
        return os;
        }
    private:
        int type;
        string _string;
        int precedence = 0;


};

class RParen : public Token
{

    public:
        RParen(){}
        RParen(string rparen) : Token (rparen, TokenType::RPAREN)
        {
            _string = rparen;
        }
        int get_precedence()
        {
            return precedence;
        }
        string get_string(){return _string;}
        friend ostream& operator<<(ostream& os, const RParen& RParen) {
        os << "RParen: " << RParen._string;
        return os;
        }
    private:
        int type;
        string _string;
        int precedence = 1;

};

class LParen : public Token
{

    public:
        LParen(){}
        LParen(string lparen) : Token (lparen, TokenType::LPAREN)
        {
            _string = lparen;
        }

        int get_precedence()
        {
            return precedence;
        }
        string get_string(){return _string;}
        friend ostream& operator<<(ostream& os, const LParen& LParen) {
        os << "LParen: " << LParen._string;
        return os;
        }
    private:
        int type;
        string _string;
        int precedence = 1;
};



class Solution: public Token
{
    public:
        Solution () {}
        Solution(vector<long> recnos) : Token(recnos)
        {
            records = recnos;
        }

        friend ostream& operator<<(ostream& os, const Solution& Solution) {
        os << "Solution: " << endl;
        for (int i = 0; i < Solution.records.size(); i++)
        {
            os << Solution.records[i] << " ";
        }
        os << endl;
        return os;
        }
        void set_records(vector<long> recnos)
        {
            for (int i = 0; i < recnos.size(); i++)
            {
                records.push_back(recnos[i]);
            }
        }
        vector<long> get_records()
        {
            return records;
        }


    private:
        vector<long> records;
};



#endif