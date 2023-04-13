#pragma once
#include "card.hpp"
#include <string>
#include <vector>

namespace ariel{

    class Player{
        private:
        string name; // name of the player
        vector<Card> hand; // the cards that the player have 
        vector<Card> wonCards; // the cards that the player won
        int score; // add points (1 if win, 3 if draw then win) like the amount that player win without his cards
        int wins; // counts the wins for player

        public:
        Player();
        Player(const char* name);

        //Getters
        string getName();
        int getScore();
        vector<Card> getHand();
        vector<Card> getWonCards();
        int getWins();

        //Setters
        void setScore(int point);
        void setHand(vector<Card> cards);
        void setWonCards(vector<Card> cards);
        void setWins(int amount);

        

        int stacksize(); //prints the amount of cards left.
        int cardesTaken(); // prints the amount of cards this player has won.

        void addCardToHand(Card &card); // add card to hand
        Card playCard(); // play card from hand
        void AddWonCard(Card &card); // add won cards to (wonCards)
        double winRate(int round);

        // bool operator==(const Player& other) const { return name == other.name; } // Comparison operator overloads
    };
}