#include "card.h"

Card::Card(CardSuit suit, CardNumber number)
    : suit_(suit)
    , number_(number)
{
    
}

CardSuit Card::suit() const noexcept
{
    return suit_;
}

CardNumber Card::number() const noexcept
{
    return number_;
}
