#include "Bulider.hpp"
#include "State.hpp"
#include "Token.hpp"
#include "Parser.hpp"
#include <vector>
#include <stack>
#include <iostream>


using namespace std;

Bulider* Bulider::_instance = NULL;

Bulider* Bulider::getInstance()
{
    if(_instance == NULL)
        _instance = new Bulider;
    return _instance;
}

void Bulider::destroyInstance()
{
    if(_instance != NULL)
        delete _instance;
    _instance = NULL;
}

void Bulider::handleOneToken(Token token)
{
    if(token.type == "START")
    {
        Token tmp;
        tmp.depth = _stack.size();
        tmp.content = "";
        tmp.type = token.content;
        _stack.push(token);
        _tokens.push_back(tmp);
    }
    else if(token.type == "END")
    {
        if(_stack.empty())
        {
            _error = true;
            return;
        }
        Token tmp = _stack.top();
        if(tmp.type == "START" && tmp.content == token.content)
            _stack.pop();
        else
        {
            _error = true;
            _stack.pop();
        }
    }
    else if(token.type == "DATA")
    {
        Token m;
        Token tmp = _stack.top();
        m.depth = _stack.size() - 1;
        m.content = token.content;
        m.type = tmp.content;
        if(_tokens.back().content == "")
        {
            _tokens.pop_back();

        }
        else
        {
            m.type = "";
        }
        _tokens.push_back(m);
    }
}

void Bulider::display()
{
    if(_error == false && _stack.empty())
    {
        vector<Token>::iterator it;
        for(it = _tokens.begin(); it != _tokens.end(); it++)
        {
            Token tmp = *it;
            if(!tmp.type.empty())
            {
                for(int i = 0; i < tmp.depth; i++)
                    cout << "  ";
                cout << tmp.type << ":" << endl;
            }
            else
            {
                if(!tmp.content.empty())
                {
                    for(int i = 0; i < tmp.depth - 1; i++)
                        cout << "  ";
                    cout << "  " << tmp.content << endl;
                }
                continue;
            }
            if(!tmp.content.empty())
            {
                for(int i = 0; i < tmp.depth; i++)
                    cout << "  ";
                cout << "  " << tmp.content << endl;
            }
        }
    }
    else
        cout << "INVALID INPUT" << endl;
}


