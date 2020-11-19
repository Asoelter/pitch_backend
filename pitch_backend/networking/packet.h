#ifndef PAKCET_H
#define PAKCET_H

/*
 *What all messages do we need?
 *
 *Play(playerID, cardID)
 *Draw(playerID)
 *Bid(playerID, amount)
 *ShootTheMoon(playerID) //Should this be it's own message or lumped in with bid?
 *Deal(playerID)
 *Quit(PlayerID)
 *
 */

class Header
{
    size_t size;
    size_t headerSize;
    size_t type;
};

template<typename T>
class Packet
{
    
};

#endif //PAKCET_H
