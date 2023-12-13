#include "shunting_yard.h"

void shunting_yard::tokenize() //please ancestors forgive me for this one
{
    Token* temp;
    string check;
    for (int i = 0; i < condition.size(); i++)
    { 
        //"my, cat, ate, a, fish"
        check = condition[i];
        if (check == "and" || check == "or")
        {
            temp = new Logical(check);
            tokenized.push_back(temp);
        }
        else if (check == ">" || check == "<" || check == "=" || check == ">=" || check == "<=")
        {
            temp = new Relational(check);
            tokenized.push_back(temp);
        }
        else if (check == "(")
        {
            temp = new LParen(check);
            tokenized.push_back(temp);
        }
        else if (check == ")")
        {
            temp = new RParen(check);
            tokenized.push_back(temp);
        }
        else
        {
            temp = new TokenStr(check);
            tokenized.push_back(temp);
        }
    }
}



void shunting_yard::turn_into_postfix() //please
{
    Token* temp;
    Token* temp2;
    //cout << "size: "<< tokenized.size() << endl;
    for (int i = 0; i < tokenized.size(); i++)
    {
        temp = tokenized[i];
        //cout << "handling this token: " << temp->get_string() << endl;
        //cout << endl;
        if (temp->get_type() == TokenType::TOKENSTR )
        {
            //cout << "recognizes token as a tokenstr" << endl;
            //cout << endl;
            postfix.push(temp);
        }
        else
        {
            //cout << "recognizes token as a not tokenstr" << endl;
            //cout << endl;
            if (rlstack.empty() == true)
            {
                //cout << "pushes onto an empty stack" << endl;
                //cout << endl;
                rlstack.push(temp);
            }
            else if (temp->get_type() == TokenType::LPAREN)
            {
                //cout << "recognizes it received a lparen" << endl;
                //cout << endl;
                rlstack.push(temp);
            }
            else if (temp->get_type() == TokenType::RPAREN)
            {
                //cout << "recognizes it hit a rparen " << endl;
                //pop until you hit lparen
                temp = rlstack.pop();
                while (temp->get_type() != TokenType::LPAREN)
                {
                    postfix.push(temp);
                    temp = rlstack.pop();
                }
            }
            else
            {
                //cout << "hits precedence check " << endl;
                //cout << "this is at the top of stack: " << rlstack.top()->get_string() << endl;
                if (temp->get_precedence() < rlstack.top()->get_precedence())
                {
                    //cout << "pops top of stack" << endl;
                    temp2 = rlstack.pop();
                    rlstack.push(temp);
                    postfix.push(temp2);
                }
                else 
                {
                    rlstack.push(temp);
                }
            }
            
        }
    }

    //now pop stack into queue until stack is empty
    while (!rlstack.empty())
    {
        postfix.push(rlstack.pop());
    }
}

//for tests
void shunting_yard::print_queue()
{
    int size = postfix.size();
    Queue <Token*> copy = postfix;
    cout << "queue size: " << size << endl;
    Token* temp;
    cout << "queue is : " << endl;
    for (int i = 0; i < size; i++)
    {
        temp = copy.pop();
        cout << temp->get_string() << " ";
    }
    cout << endl;

    // cout << "stack is: " << endl;
    // int size2 = rlstack.size();
    // for (int i = 0; i < size2; i++)
    // {
    //     temp = rlstack.pop();
    //     cout << temp->get_string() << " ";
    // }
    // cout << endl;
}
