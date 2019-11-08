/*
 * Deck.cpp
 *
 *  Created on: Oct 12, 2019
 *      Author: root
 */

#include "Deck.h"
#include <algorithm>

using namespace std;

Deck::Deck() {
	for (const auto s : Suits::All) {
		for (const auto r : Ranks::All) {
			Card c = Card(r,s);
			cards.push_back(c);
		}
	}

}

Deck::~Deck() {
	// TODO Auto-generated destructor stub
}

void Deck::dump() {
	cout << cards.size() << '\n';
	for (auto& c : cards) {
		cout << c;
	}
}

void Deck::shuffle() {
	//TODO look into seeding the RNG
	std::random_shuffle(cards.begin(), cards.end());
	//std::random_shuffle(cards.back(), cards.end());
}

std::vector<Card> Deck::deal(int num_cards) {
	vector<Card> dealt_cards;
	if (num_cards <= cards.size()) {
		for (int i = 0; i < num_cards; i++) {
			//TODO understand how this works...
			//in particular if the 2nd two statements are reversed
			//then the deal_cards vector gets the 2nd and 3rd cards of the deck
			//and the second dealt card remains on the front of the deck.
			Card& c = cards.front();
			dealt_cards.push_back(c);
			cards.erase(cards.begin());
		}
	} else {
		cout << "request for " << num_cards << " deck contains " << cards.size() << '\n';
	}

	return dealt_cards;
}
