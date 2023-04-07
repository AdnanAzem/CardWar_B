#pragma once
#include "card.hpp"
#include <string>
#include <vector>

namespace ariel{

    class Player{
        private:
        string name;
        vector<Card> hand;
        vector<Card> wonCards;
        int score;
        int drawAmount;

        public:
        Player();
        Player(const char* name);

        //Getters
        string getName();
        int getScore();
        vector<Card> getHand();
        vector<Card> getWonCards();
        int getDrawAmount();

        //Setters
        void setScore(int point);
        void setHand(vector<Card> cards);
        void setWonCards(vector<Card> cards);
        void setDrawAmount(int amount);

        

        int stacksize(); //prints the amount of cards left.
        int cardesTaken(); // prints the amount of cards this player has won.

        void addCardToHand(Card &card); // add card to hand
        Card playCard(); // play card from hand
        void AddWonCard(Card &card);
        double winRate(int round);

        bool operator==(const Player& other) const { return name == other.name; }
    };
}