
#include "player.hpp"

namespace ariel{

    Player::Player() : name("Adnan"){

    }

    Player::Player(const char* name) : name(name), score(0){

    }

    string Player::getName(){
        return this->name;
    }

    int Player::getScore(){
        return this->score;
    }

    vector<Card> Player::getHand(){
        return this->hand;
    }

    vector<Card> Player::getWonCards(){
        return this->wonCards;
    }

    void Player::setScore(int point){
        this->score += point;
    }

    int Player::cardesTaken(){
        return this->wonCards.size();
    }

    int Player::stacksize(){
        return this->hand.size();
    }

    void Player::addCardToHand(Card &card){
        this->hand.push_back(card);
    }

    Card Player::playCard(){
        Card card = this->hand.back();
        this->hand.pop_back();
        return card; 
    }

    void Player::AddWonCard(Card &card){
        this->wonCards.push_back(card);
    }

    double Player::winRate(int round){
        return (double)this->score/round*100.0;
    }

    void Player::setHand(vector<Card> cards){
        this->hand = cards;
    }
    void Player::setWonCards(vector<Card> cards){
        this->wonCards = cards;
    }


}