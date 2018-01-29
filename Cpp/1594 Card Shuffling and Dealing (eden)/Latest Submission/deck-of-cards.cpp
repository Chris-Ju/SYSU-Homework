 #include "deck-of-cards.hpp"

DeckOfCards::DeckOfCards()
{
    int i,j;
    for(i = 0; i <= 3; i++)
    {
        for(j = 0;j <= 13; j++)
        {
            Card node(j, i);
            deck.push_back(node);
        }
    }
    this->currentCard = 0;
}

Card DeckOfCards::dealCard()
{
    int i = this->currentCard / 13;
    int j = this->currentCard % 13;
    this->currentCard++;
    Card node(j, i);
    return node;
}

bool DeckOfCards::moreCards() const
{
    if(currentCard == 52)
        return false;
    return true;
}