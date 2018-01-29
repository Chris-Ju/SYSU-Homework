#include "Parser.hpp"
#include "Token.hpp"
#include "Bulider.hpp"
#include "State.hpp"

Parser* Parser::_instance = NULL;

Parser* Parser::getInstance()
{
    if(_instance == NULL)
        _instance = new Parser;
    return _instance;
}

void Parser::destroyInstance()
{
    if(_instance != NULL)
        delete _instance;
    _instance = NULL;
}

void Parser::consumeOneChar(char ch)
{
    if(ch == '<')
    {
        _state->handleOneChar(this, ch);
        _state = TagNameState::getInstance();
    }
    else if(ch == '>')
    {
        _state->handleOneChar(this, ch);
        _state = DataState::getInstance();
    }
    else
        _state->handleOneChar(this, ch);

}

