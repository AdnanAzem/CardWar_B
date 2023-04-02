#include "card.hpp"

namespace ariel{


    string Card::suitName (Suit suit) {
        switch(suit) {
            case clubs: return "Clubs";
            case diamonds: return "Diamonds";
            case hearts: return "Hearts";
            case spades: return "Spades";
            default: throw std::out_of_range("Suit value out of range");
        }
    }

    string Card::valueName (Value value) {
        switch(value) {
        case ace: return "Ace";
        case two: return "2";
        case three: return "3";
        case four: return "4";
        case five: return "5";
        case six:  return "6";
        case seven: return "7";
        case eight: return "8";
        case nine: return "9";
        case ten: return "10";
        case jack: return "Jack";
        case queen: return "Queen";
        case king: return "King";
        default: throw std::out_of_range("Face value out of range");
        }
    }
    
}