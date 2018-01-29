#include "State.hpp"
#include "Token.hpp"
#include "Parser.hpp"
#include <string>
#include <iostream>

std::string& trim(std::string &s)
{
    if(s.empty())
        return s;
    if(s[0] == ' ')
        s.erase(0, s.find_first_not_of(" "));
    if(s.empty())
        return s;
    if(s[s.length() - 1] == ' ')
        s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

State* DataState:: _instance = NULL;
State* TagNameState::_instance = NULL;

State* DataState::getInstance()
{
    if(_instance == NULL)
        _instance = new DataState;
    return _instance;
}

void DataState::destroyInstance()
{
    if(_instance != NULL)
        delete _instance;
    _instance = NULL;
}

void DataState::handleOneChar(Parser* parser, char ch)
{
    if(ch == '<')
    {
        trim(_cache);
        if(_cache != "")
            emit(parser->getBulider());
    }
    else
        _cache += ch;


}

void DataState::emit(Bulider* dest)
{
    Token tmp;
    tmp.type = "DATA";
    tmp.content = _cache;
    _cache = "";
    //std::cout << tmp.content << std::endl;
    dest->handleOneToken(tmp);
}

State* TagNameState::getInstance()
{
    if(_instance == NULL)
        _instance = new TagNameState;
    return _instance;
}

void TagNameState::destroyInstance()
{
    if(_instance != NULL)
        delete _instance;
    _instance = NULL;
}

void TagNameState::handleOneChar(Parser* parser, char ch)
{
    if(ch == '>')
    {
        trim(_cache);
        //if(_cache != "")
            emit(parser->getBulider());
    }
    else
        _cache += ch;
}
void TagNameState::emit(Bulider* dest)
{
    Token tmp;
    if(_cache[0] == '/')
    {
        tmp.type = "END";
        tmp.content = _cache.substr(1);
    }
    else
    {
        tmp.type = "START";
        tmp.content = _cache;
    }
    _cache = "";
    //std::cout << tmp.content << std::endl;
    dest->handleOneToken(tmp);
}
