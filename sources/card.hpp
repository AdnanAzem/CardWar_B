#pragma once
#include <iostream>


namespace ariel{
    using namespace std;
    class Card{
        public:
            enum Suit {clubs, diamonds, hearts, spades};
            enum Value {two = 2, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};

            Card (Value faceValue=two, Suit suit = clubs):
                suit (suit), faceValue(faceValue) {}

            // Getters
            Suit getSuit()  { return suit; }
            Value getValue()  { return faceValue; }


            static string suitName (Suit suitName);
            static string valueName (Value valueName);

            string to_string() { return valueName (faceValue) + " of " + suitName(suit);}

            // Comparison operator overloads
            bool operator==(const Card& other) const { return faceValue == other.faceValue; }
            bool operator>(const Card& other) const { return faceValue > other.faceValue; }
            bool operator<(const Card& other) const { return faceValue < other.faceValue; }

        private:
            Suit suit;
            Value faceValue;

    };
}