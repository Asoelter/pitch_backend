#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

#include <algorithm>
#include <array>
#include <random>
#include <string>
#include <vector>

#include <covid/socket.h>

#include "card_enums.h"
#include "messages.h"

struct CardHandle
{
    CardSuit    suit;
    CardNumber  number;
};

enum class DealerState
{
    WaitingForPlayersToBeReady,
    Dealing,
    DebugUnknown
};

void MsgBox(const char * title, const char * message)
{
    MessageBox(NULL, title, message, NULL);
}

INT WinMain(HINSTANCE hInstance, 
            HINSTANCE hPrevInstance,
            PSTR      lpCmdLine, 
            INT       nCmdShow)
{
    std::array<CardHandle, 52> deck = { {
        {CardSuit::Heart, CardNumber::Two},   {CardSuit::Heart, CardNumber::Three}, {CardSuit::Heart, CardNumber::Four},
        {CardSuit::Heart, CardNumber::Five},  {CardSuit::Heart, CardNumber::Six},   {CardSuit::Heart, CardNumber::Seven},
        {CardSuit::Heart, CardNumber::Eight}, {CardSuit::Heart, CardNumber::Nine},  {CardSuit::Heart, CardNumber::Ten},
        {CardSuit::Heart, CardNumber::Jack},  {CardSuit::Heart, CardNumber::Queen}, {CardSuit::Heart, CardNumber::King},
        {CardSuit::Heart, CardNumber::Ace},

        {CardSuit::Spade, CardNumber::Two},   {CardSuit::Spade, CardNumber::Three}, {CardSuit::Spade, CardNumber::Four},
        {CardSuit::Spade, CardNumber::Five},  {CardSuit::Spade, CardNumber::Six},   {CardSuit::Spade, CardNumber::Seven},
        {CardSuit::Spade, CardNumber::Eight}, {CardSuit::Spade, CardNumber::Nine},  {CardSuit::Spade, CardNumber::Ten},
        {CardSuit::Spade, CardNumber::Jack},  {CardSuit::Spade, CardNumber::Queen}, {CardSuit::Spade, CardNumber::King},
        {CardSuit::Spade, CardNumber::Ace},

        {CardSuit::Diamond, CardNumber::Two},   {CardSuit::Diamond, CardNumber::Three}, {CardSuit::Diamond, CardNumber::Four},
        {CardSuit::Diamond, CardNumber::Five},  {CardSuit::Diamond, CardNumber::Six},   {CardSuit::Diamond, CardNumber::Seven},
        {CardSuit::Diamond, CardNumber::Eight}, {CardSuit::Diamond, CardNumber::Nine},  {CardSuit::Diamond, CardNumber::Ten},
        {CardSuit::Diamond, CardNumber::Jack},  {CardSuit::Diamond, CardNumber::Queen}, {CardSuit::Diamond, CardNumber::King},
        {CardSuit::Diamond, CardNumber::Ace},

        {CardSuit::Club, CardNumber::Two},   {CardSuit::Club, CardNumber::Three}, {CardSuit::Club, CardNumber::Four},
        {CardSuit::Club, CardNumber::Five},  {CardSuit::Club, CardNumber::Six},   {CardSuit::Club, CardNumber::Seven},
        {CardSuit::Club, CardNumber::Eight}, {CardSuit::Club, CardNumber::Nine},  {CardSuit::Club, CardNumber::Ten},
        {CardSuit::Club, CardNumber::Jack},  {CardSuit::Club, CardNumber::Queen}, {CardSuit::Club, CardNumber::King},
        {CardSuit::Club, CardNumber::Ace},
    } };
    const auto port = Port("127.0.0.1", "49152");

    constexpr int expectedClients = 1;
    constexpr uint8_t cardsToDeal = 10;
    int numClients = 0;
    std::vector<Socket> clients;

    while(numClients < expectedClients)
    {
        clients.emplace_back(Socket::listenOn(port));
        ++numClients;
    }

    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(deck.begin(), deck.end(), g);

    bool keepRunning = true;
    int activePlayerIndex = 0;
    DealerState dealerState = DealerState::WaitingForPlayersToBeReady;
    int numReadyClients = 0;
    int cardsDealt = 0;
    int currentCardIndex = 0;

    while(keepRunning)
    {
        if (dealerState == DealerState::WaitingForPlayersToBeReady)
        {
            const auto messageInBytes = clients[activePlayerIndex].receive();
            const auto message = std::string(messageInBytes.begin(), messageInBytes.end());
            MsgBox("received stuff", message.c_str());
            clients[activePlayerIndex].send({ 'b', 'a', 'c', 'k', '\0' });
            ++numReadyClients;

            if(numReadyClients == expectedClients)
            {
                dealerState = DealerState::Dealing;
            }
        }

        if(dealerState == DealerState::Dealing)
        {
            for(auto& client : clients)
            {
                const auto suit = deck[currentCardIndex].suit;
                const auto number = deck[currentCardIndex].number;
                client.send(PlayedCardMessage(suit, number).serialize());
                ++currentCardIndex;
            }

            ++cardsDealt;

            if(cardsDealt >= cardsToDeal)
            {
                dealerState = DealerState::DebugUnknown;
            }
        }
    }

    return 0;
}
