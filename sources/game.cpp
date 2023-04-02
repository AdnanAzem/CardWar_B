
#include "game.hpp"
#include <algorithm>
#include <random>
#include <chrono>

namespace ariel{


        
    Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2){
        this->deck = createDeck();
        shuffleDeck(this->deck);
        divideDeck(this->deck/*, this->player1, this->player2*/);
        gameover = false;
    }

    void Game::playTurn(){
        if(gameover){
            throw ("Game is Over!!!");
        }
        if(player1 == player2){ throw ("Same Player!!!");}
        if(this->player1.stacksize() == 0 && this->player2.stacksize() == 0){
            gameover = true;
            // throw ("no more cards in the hand of players");
            return;
        }
        else{
            Card card1 = this->player1.playCard();
            Card card2 = this->player2.playCard();
            if(card1.getValue()==2 && card2.getValue() == 14){
                this->player1.AddWonCard(card2);
                this->player1.AddWonCard(card1);
                this->player1.setScore(1);
                this->winnerPerRound = player1.getName();
                this->lastRound = this->player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + " " + winnerPerRound + " wins.\n";
                this->logs += this->lastRound; 
                
            }
            else if(card1.getValue()==14 && card2.getValue() == 2){
                this->player2.AddWonCard(card1);
                this->player2.AddWonCard(card2);
                this->player2.setScore(1);
                this->winnerPerRound = this->player2.getName();
                this->lastRound = this->player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + " " + winnerPerRound + " wins.\n";
                this->logs += this->lastRound;
            }
            else if(card1 > card2){
                this->player1.AddWonCard(card2);
                this->player1.AddWonCard(card1);
                this->player1.setScore(1);
                this->winnerPerRound = player1.getName();
                this->lastRound = player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + " " + winnerPerRound + " wins.\n";
                this->logs += this->lastRound; 

            }
            else if(card1 < card2){
                this->player2.AddWonCard(card1);
                this->player2.AddWonCard(card2);
                this->player2.setScore(1);
                this->winnerPerRound = player2.getName();
                this->lastRound = player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + " " + winnerPerRound + " wins.\n";
                this->logs += this->lastRound;

            }
            else{
              if(this->player1.stacksize() == 0 && this->player2.stacksize() == 0){
                cout << "Draw Round" << endl;
                draw++;
              }
              else if (this->player1.stacksize() == 1 && this->player2.stacksize() == 1){
                card1 = this->player1.playCard();
                card2 = this->player2.playCard();
                if(card1 > card2){

                }
                else if(card1 < card2){

                }
                else{

                }

                
              }
              else{

              }
            }
        }
    }

    bool Game::checkCards(){
        return false;
    }

    void Game::printLastTurn(){
        cout << this->lastRound << endl;
    }

    void Game::playAll(){
        while(!gameover){
            playTurn();
        }
    }

    void Game::printWiner(){
        if (player1.getScore() > player2.getScore()){
            winner = player1.getName();
            cout << winner << endl;
        }
        else if (player1.getScore() < player2.getScore()){
            winner = player2.getName();
            cout << winner << endl;
        }
        else{
            cout << "Draw Game!" << endl;
        }
    }

    void Game::printLog(){
        cout << this->logs << endl;
    }

    void Game::printStats(){
        string cards1;
        for(Card card : this->player1.getWonCards()){
            cards1 += "\t\t" + card.to_string() + "\n";
        }

        string cards2;
        for(Card card : this->player2.getWonCards()){
            cards2 += "\t\t" + card.to_string() + "\n";
        }
        
        stats = this->player1.getName() + "{\n"
                + "\tscore : " + to_string(player1.getScore()) + "\n"
                + "\tdraw : " + to_string(this->draw) + "\n"
                + "\twinRates : " + to_string(player1.winRate(26-this->player1.stacksize())) + "%\n"
                + "\tWonCards : " + to_string(this->player1.getWonCards().size()) + "\n"
                + "\tCards [ \n" 
                + cards1 + "\n"
                + "\t]\n"
                + "}\n\n"
                + this->player2.getName() + "{\n"
                + "\tscore : " + to_string(player2.getScore()) + "\n"
                + "\tdraw : " + to_string(this->draw) + "\n"
                + "\twinRates : " + to_string(player2.winRate(26-this->player2.stacksize())) + "%\n"
                + "\tWonCards : " + to_string(this->player2.getWonCards().size()) + "\n"
                + "\tCards [ \n" 
                + cards2 + "\n"
                + "\t]\n"
                + "}\n";
        cout << this->stats << endl;
    }

    vector<Card> Game::createDeck(){
        vector<Card> deck;
        // create a standard deck of 52 cards
        for (int suit = Card::clubs; suit <= Card::spades; ++suit){
            for (int rank = Card::two; rank <= Card::ace; ++rank){
                deck.push_back(Card(static_cast<Card::Value>(rank), static_cast<Card::Suit>(suit)));
            }
        }
        return deck;
    }

    void Game::shuffleDeck(vector<Card> &deck){
        random_device rd;
        mt19937 g(rd());
        shuffle(deck.begin(), deck.end(), g);
    }

    void Game::divideDeck(vector<Card> &deck/*, Player &player1, Player &player2*/){
        int counter = 0;
        for (Card card : deck){
            if (counter % 2 == 0){
                this->player1.addCardToHand(card);
                counter++;
            }
            else{
                this->player2.addCardToHand(card);
                counter++;
            }
        }
    }
}