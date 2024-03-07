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
    for (int i = 0; i < tokenized.size(); i++)
    {
        temp = tokenized[i];
        if (temp->get_type() == TokenType::TOKENSTR )
        {
            postfix.push(temp);
        }
        else
        {
            if (rlstack.empty() == true)
            {
                rlstack.push(temp);
            }
            else if (temp->get_type() == TokenType::LPAREN)
            {
                rlstack.push(temp);
            }
            else if (temp->get_type() == TokenType::RPAREN)
            {
                //dont pop out here
                while (rlstack.top()->get_type() != TokenType::LPAREN)
                {
                    //start popping in here
                    postfix.push(rlstack.pop());

                    //temp = rlstack.pop();
                }
                rlstack.pop();
            }
            else
            {       //

                //to keep checking whats under
                while ( !rlstack.empty() && (temp->get_precedence() < rlstack.top()->get_precedence()))
                {  
                    temp2 = rlstack.pop();
                    //rlstack.push(temp);
                    postfix.push(temp2);

                }
                rlstack.push(temp);
            }
            
        }
    }

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
