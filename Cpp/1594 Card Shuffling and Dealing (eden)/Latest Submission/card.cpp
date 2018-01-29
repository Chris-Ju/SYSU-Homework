 #include "card.hpp"
const char* Card::faceNames[Card::totalFaces] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

const char* Card::suitNames[Card::totalSuits] = {"Hearts", "Diamonds", "Clubs", "Spades"};
Card::Card(int cardFace, int cardSuit)
{
    this->face = cardFace;
    this->suit = cardSuit;
}

std::string Card::toString() const
{
    std::string str1 = this->faceNames[this->getFace()];
    std::string str2 = this->suitNames[this->getSuit()];
    std::string str3 = str1 + " of " + str2;
    return str3;
}

int Card::getFace() const
{
    return this->face;
}

int Card::getSuit() const
{
    return this->suit;
}