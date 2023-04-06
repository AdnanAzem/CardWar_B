
#include "game.hpp"
#include <algorithm>
#include <random>
#include <chrono>

namespace ariel{
       
    Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2), draw(0){
        
        this->deck = createDeck();
        shuffleDeck(this->deck);
        divideDeck(this->deck/*, this->player1, this->player2*/);
        gameover = false;
    }

    void Game::playTurn(){
        if(gameover){
            throw ("Game is over!!!");
            return;
        }
        if(player1 == player2){ throw ("Same Player!!!");}
        if(this->player1.stacksize() == 0 || this->player2.stacksize() == 0){
            gameover = true;
            return;
        }
        else{
            Card card1 = this->player1.playCard();
            Card card2 = this->player2.playCard();
            if(card1.getValue() == 2 && card2.getValue() == 14){ // 2 wins against ace
                this->player1.AddWonCard(card2);
                this->player1.AddWonCard(card1);
                this->player1.setScore(1);
                this->winnerPerRound = player1.getName();
                this->lastRound = this->player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + ". " + winnerPerRound + " wins.\n";
                this->logs = this->lastRound + this->logs; 
                
            }
            else if(card1.getValue() == 14 && card2.getValue() == 2){ // 2 wins against ace
                this->player2.AddWonCard(card1);
                this->player2.AddWonCard(card2);
                this->player2.setScore(1);
                this->winnerPerRound = this->player2.getName();
                this->lastRound = this->player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + ". " + winnerPerRound + " wins.\n";
                this->logs = this->lastRound + this->logs; 
            }
            else if(card1 > card2){ 
                this->player1.AddWonCard(card2);
                this->player1.AddWonCard(card1);
                this->player1.setScore(1);
                this->winnerPerRound = player1.getName();
                this->lastRound = player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + ". " + winnerPerRound + " wins.\n";
                this->logs = this->lastRound + this->logs; 

            }
            else if(card1 < card2){
                this->player2.AddWonCard(card1);
                this->player2.AddWonCard(card2);
                this->player2.setScore(1);
                this->winnerPerRound = player2.getName();
                this->lastRound = player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + ". " + winnerPerRound + " wins.\n";
                this->logs = this->lastRound + this->logs; 

            }
            else{ // draw
                draw++;
                this->lastRound = player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + ". Draw.\n";
                this->logs += this->lastRound;
                vector<Card> jackpot;
                jackpot.push_back(card1);
                jackpot.push_back(card2);
                bool done = false;
                while(!done){
                  Card card1Closed, card1Open, card2Closed, card2Open;
                  if(this->player1.stacksize() < 2 || this->player2.stacksize() < 2){ // players have less than 2 cards
                    player1.AddWonCard(card1);
                    player2.AddWonCard(card2);
                    done = true;
                    break;
                  }
                  card1Closed = this->player1.playCard();
                  card1Open = this->player1.playCard();
                  card2Closed = this->player2.playCard();
                  card2Open = this->player2.playCard();
                  if(card1Open > card2Open){
                    jackpot.push_back(card1Open);
                    jackpot.push_back(card2Open);
                    jackpot.push_back(card1Closed);
                    jackpot.push_back(card2Closed);
                    for(Card card : jackpot){
                      this->player1.AddWonCard(card);
                    }
                    done = true;
                    this->winnerPerRound = player1.getName();
                    this->player1.setScore(3);
                    this->lastRound = player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + ". " + winnerPerRound + " wins.\n";
                    this->logs = this->lastRound + this->logs; 
                  }
                  else if(card1Open < card2Open){
                    jackpot.push_back(card2Open);
                    jackpot.push_back(card1Open);
                    jackpot.push_back(card2Closed);
                    jackpot.push_back(card1Closed);
                    for(Card card : jackpot){
                      this->player2.AddWonCard(card);
                      }
                    done = true;
                    this->winnerPerRound = player2.getName();
                    this->player2.setScore(3);
                    this->lastRound = player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + ". " + winnerPerRound + " wins.\n";
                    this->logs = this->lastRound + this->logs; 
                  }
                  else{ // card1 = card2
                    draw++;
                    jackpot.push_back(card1Closed);
                    jackpot.push_back(card2Closed);
                    jackpot.push_back(card1Open);
                    jackpot.push_back(card2Open);
                    this->lastRound = player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + ". draw.\n";
                    this->logs = this->lastRound + this->logs; 
                  }
                }

            }
        }
    }

    void Game::printLastTurn(){
        std::cout << this->lastRound << endl;
    }

    void Game::playAll(){
        while(!gameover || player1.stacksize() > 0){
            playTurn();
        }
    }

    void Game::printWiner(){
        if (player1.cardesTaken() > player2.cardesTaken()){
            winner = player1.getName();
            std::cout << winner << endl;
        }
        else if (player1.cardesTaken() < player2.cardesTaken()){
            winner = player2.getName();
            std::cout << winner << endl;
        }
        else{
            std::cout << "Draw Game!" << endl;
        }
    }

    void Game::printLog(){
        std::cout << this->logs << endl;
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
        std::cout << this->stats << endl;
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
