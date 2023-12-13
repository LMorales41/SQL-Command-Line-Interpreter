#ifndef token_h
#define token_h

#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

enum class TokenType
{
    LPAREN,
    RPAREN,
    LOGICAL,
    RELATIONAL,
    TOKENSTR
};

class Token
{

    public:
        Token (){}
        //Token(){_token = ""; _type = 0;}
        Token(string str, int stype){_token = str; _type = stype;}
        Token (vector<long> recnos){records = recnos;}
        Token(string str, TokenType t ){_token = str; ttype = t;}
        virtual int get_precedence()
        {
            cout << "this is calling base" << endl;
            return 0;
        }
        friend ostream& operator<<(ostream& os, const Token& token) {
        // os << "Base Token: " << token._token;
        // return os;
            os << token.token_str() << "          |" <<  token._token << "|";
            return os;
        }
        virtual string get_string(){return _token;}
        TokenType get_type (){return ttype;}
        virtual void set_records(vector<long> recnos ){ cout << "calling in Token" << endl;}
        virtual vector<long> get_records () 
        {
            cout << "calling in Token" << endl;
            vector <long > temp;
            return temp;
        }
            int type() const {return _type;} 
        string type_string() const {return _token;} // returns what the string says
        string token_str() const
        {
            string alfa = "ALFA";
            string digits = "DIGITS";
            string punc = "PUNC";
            string spaces = "SPACES";
            if (_type == 1)
            {
                return alfa;
            }
            else if (_type == 2 || _type == 6){
                return digits;
            }
            else if (_type == 4 || _type == 5)
            {
                return punc;

            }
            else if (_type == 3)
            {
                return spaces;
            }
            else {
                return "";
            }
        } // returns the numerical value of the string (397, etc)


    private:
    string _token = "";
    TokenType ttype;
    vector <long> records;
    int _type =0;
};

#endif