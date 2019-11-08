/*
 * Card.cpp
 *
 *  Created on: Oct 11, 2019
 *      Author: root
 */

#include "Card.h"

using namespace std;

Card::Card(Ranks::Rank rank, Suits::Suit suit) {
	_suit = suit;
	_rank = rank;
}

Card::~Card() {
	// TODO Auto-generated destructor stub
}

string Card::to_string() {
    string s = string();

    s = Ranks::s[_rank] + " of " +  Suits::s[_suit] + '\n';

    return s;
}


std::ostream& operator<<(std::ostream& os,  Card& card) {
	return os << card.to_string();
}
