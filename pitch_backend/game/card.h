#ifndef CARD_H
#define CARD_H

#include "card_enums.h"

class Card
{
public:
    Card(CardSuit suit, CardNumber number);

    CardSuit suit() const noexcept;
    CardNumber number() const noexcept;

private:
    CardSuit    suit_;
    CardNumber  number_;
};

#endif //CARD_H
