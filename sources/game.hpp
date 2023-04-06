#pragma once
#include "player.hpp"

namespace ariel{

    class Game{
        private:
        Player &player1;
        Player &player2;
        vector<Card> deck;
        string logs;
        string stats;
        string lastRound;
        string winnerPerRound;
        string winner;
        bool gameover;
        int draw;
        
        public:
        Game(Player &player1, Player &player2);

        void playTurn();
        void printLastTurn(); // print the last turn stats.
        void playAll(); //playes the game untill the end
        void printWiner(); // prints the name of the winning player
        void printLog(); // prints all the turns played one line per turn (same format as game.printLastTurn())
        void printStats(); // for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )

        vector<Card> createDeck();     // Define a function to create a deck of cards
        void shuffleDeck(vector<Card>& deck); // Define a function to shuffle the deck of cards
        void divideDeck(vector<Card>& deck/*, Player &player1, Player &player2*/);  // Define a function to divide the deck of cards between two players


    };
}