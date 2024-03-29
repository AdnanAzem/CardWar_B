/*
    I used this link to get more information about: random_device, mt19937, shuffle 
    https://stackoverflow.com/questions/38367976/do-stdrandom-device-and-stdmt19937-follow-an-uniform-distribution
*/

#include "game.hpp"
#include <algorithm>
#include <random>
#include <chrono>

namespace ariel{

    // ==================== constructor ====================
    Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2), draw(0), rounds(0){
        this->deck = createDeck();
        shuffleDeck(this->deck);
        divideDeck(this->deck/*, this->player1, this->player2*/);
        gameover = false;
    }

    // ==================== fill info ====================
    void Game::fillInfo(int playerNum, Card &playedCard1, Card &playedCard2, int points){
        if(playerNum == 1){ // fill info for player 1
            this->player1.setScore(points);
            this->winnerPerRound = player1.getName();
            this->lastRound = this->player1.getName() + " played " + playedCard1.to_string() + " " +this->player2.getName() + " played " + playedCard2.to_string() + ". " + winnerPerRound + " wins.\n";
            this->logs += this->lastRound;
        }
        else { // fill info for player 2
            this->player2.setScore(points);
            this->winnerPerRound = player2.getName();
            this->lastRound = this->player1.getName() + " played " + playedCard1.to_string() + " " + this->player2.getName() + " played " + playedCard2.to_string() + ". " + winnerPerRound + " wins.\n";
            this->logs += this->lastRound;
        }
    }

    // ==================== add all cards ====================
    void Game::addAllCards(Player &player, Card &card1, Card &card2, int points){
        player.AddWonCard(card1);
        player.AddWonCard(card2);
        player.setWins(points);
    }

    // ==================== play turn ====================
    void Game::playTurn(){
        if(gameover){
            throw ("Game is over!!!");
            return;
        }
        if(&player1 == &player2){ throw ("Same Player!!!");}
        if(this->player1.stacksize() == 0 || this->player2.stacksize() == 0){
            gameover = true;
            return;
        }
        else{
            rounds++;
            Card card1 = this->player1.playCard();
            Card card2 = this->player2.playCard();
            if(card1.getValue() == 2 && card2.getValue() == 14){ // 2 wins against ace
                addAllCards(player1,card2,card1,1);
                fillInfo(1,card1,card2,1); 
            }
            else if(card1.getValue() == 14 && card2.getValue() == 2){ // 2 wins against ace
                addAllCards(player2,card1,card2,1);
                fillInfo(2,card1,card2,1);
            }
            else if(card1 > card2){ 
                addAllCards(player1,card2,card1,1);
                fillInfo(1,card1,card2,1);
            }
            else if(card1 < card2){
                addAllCards(player2,card1,card2,1);
                fillInfo(2,card1,card2,1);
            }
            else{ // draw
                draw++;
                this->lastRound = player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + ". Draw. ";
                this->logs += this->lastRound;
                vector<Card> jackpot;
                jackpot.push_back(card1);
                jackpot.push_back(card2);
                bool done = false;
                while(!done){
                  Card card1Closed, card1Open, card2Closed, card2Open;
                  if(this->player1.stacksize() < 2 || this->player2.stacksize() < 2){ // players have less than 2 cards
                    if(this->player1.stacksize() == 0 || this->player2.stacksize() == 0){ // no cards in the stacksize
                        player1.AddWonCard(card1);
                        player2.AddWonCard(card2);
                        done = true;
                        break;
                    }
                    else{ // one card left in the stacksize
                        player1.AddWonCard(card1);
                        card1 = this->player1.playCard();
                        player1.AddWonCard(card1);
                        player2.AddWonCard(card2);
                        card2 = this->player2.playCard();
                        player2.AddWonCard(card2);
                        done = true;
                        break;
                    }
                  }
                  card1Closed = this->player1.playCard();
                  card1Open = this->player1.playCard();
                  card2Closed = this->player2.playCard();
                  card2Open = this->player2.playCard();
                  if(card1Open.getValue() == 2 && card2Open.getValue() == 14){ // 2 wins against ace
                    addToJackpot(jackpot, card1Open, card2Open, card1Closed, card2Closed);
                    for(Card card : jackpot){
                      this->player1.AddWonCard(card);
                    }
                    done = true;
                    fillInfo(1,card1Open,card2Open,3);
                    break;
                  }
                  else if(card1Open.getValue() == 14 && card2Open.getValue() == 2){ // 2 wins against ace
                    addToJackpot(jackpot, card2Open, card1Open, card2Closed, card1Closed);
                    for(Card card : jackpot){
                      this->player2.AddWonCard(card);
                    }
                    done = true;
                    fillInfo(2,card1Open,card2Open,3);
                    break;
                  }
                  else if(card1Open > card2Open){ // card 1 open bigger than card 2 open
                    addToJackpot(jackpot, card1Open, card2Open, card1Closed, card2Closed);
                    for(Card card : jackpot){
                      this->player1.AddWonCard(card);
                    }
                    done = true;
                    fillInfo(1,card1Open,card2Open,3);
                    break;
                  }
                  else if(card1Open < card2Open){ // card 1 open smaller than card 2 open
                    addToJackpot(jackpot, card2Open, card1Open, card2Closed, card1Closed);
                    for(Card card : jackpot){
                      this->player2.AddWonCard(card);
                      }
                    done = true;
                    fillInfo(2,card1Open,card2Open,3);
                    break;
                  }
                  else{ // card 1 open equal to card 2 open
                    draw++;
                    addToJackpot(jackpot, card1Closed, card2Closed, card1Open, card2Open);
                    this->lastRound = player1.getName() + " played " + card1.to_string() + " " +this->player2.getName() + " played " + card2.to_string() + ". draw. ";
                    this->logs += this->lastRound;
                  }
                }
            }
        }
    }

    // ==================== add to jackpot ====================
    void Game::addToJackpot(vector<Card> &jackpot, Card &card1, Card &card2, Card &card3, Card &card4){
        jackpot.push_back(card1);
        jackpot.push_back(card2);
        jackpot.push_back(card3);
        jackpot.push_back(card4);
    }

    // ==================== print last turn ====================
    void Game::printLastTurn(){
        std::cout << this->lastRound << endl;
    }

    // ==================== play all ====================
    void Game::playAll(){
        while(!gameover || player1.stacksize() > 0){
            playTurn();
        }
    }

    // ==================== print winner ====================
    void Game::printWiner(){
        if (player1.cardesTaken() > player2.cardesTaken()){
            winner = player1.getName();
            std::cout << "The winner is : " << winner << endl;
        }
        else if (player1.cardesTaken() < player2.cardesTaken()){
            winner = player2.getName();
            std::cout << "The winner is : " << winner << endl;
        }
        else{
            std::cout << "Draw Game!" << endl;
        }
    }

    // ==================== print log ====================
    void Game::printLog(){
        std::cout << this->logs << endl;
    }

    // ==================== print stats ====================
    void Game::printStats(){
        string cards1;
        for(Card card : this->player1.getWonCards()){
            cards1 += "\t\t" + card.to_string() + "\n";
        }

        string cards2;
        for(Card card : this->player2.getWonCards()){
            cards2 += "\t\t" + card.to_string() + "\n";
        }

        stats = fillStats(player1,cards1) + fillStats(player2,cards2);
        std::cout << this->stats << endl;
    }

    // ==================== fill stats ====================
    string Game::fillStats(Player &player, string cards){
        string res;
        res = player.getName() + "{\n"
            + "\tamout of rounds : " + to_string(rounds) + "\n"
            + "\tscore : " + to_string(player.getScore()) + "\n"
            + "\twins : " + to_string(player.getWins()) + "\n"
            + "\tamount of draws : " + to_string(this->draw) + "\n"
            + "\tdraw rate : " + to_string((double)this->draw/rounds*100.0) + "%\n" 
            + "\twinRates : " + to_string(player.getWins()*100.0/rounds) + "%\n"
            + "\tWonCards : " + to_string(player.getWonCards().size()) + "\n"
            + "\tCards [ \n" 
            + cards + "\n"
            + "\t]\n"
            + "}\n\n";
        return res;
    }

    // ==================== create deck ====================
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

    // ==================== shuffle deck ====================
    void Game::shuffleDeck(vector<Card> &deck){
        random_device rd;   // is a uniformly-distributed random number generator that may access a hardware device in your system, or something like /dev/random on Linux. 
                            // It is usually just used to seed a pseudo-random generator, since the underlying device wil usually run out of entropy quickly.

        mt19937 g(rd());    // is a fast pseudo-random number generator using the Mersenne Twister engine which, according to the original authors' paper title, is also uniform. This generates fully random 32-bit or 64-bit unsigned integers.
                            // Since std::random_device is only used to seed this generator, it does not have to be uniform itself 

        shuffle(deck.begin(), deck.end(), g);   // Reorders the elements in the given range [first, last) such that each possible permutation of those elements has equal probability of appearance.
                                                // The source of randomness is the object g.
    }

    // ==================== divide deck ====================
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
