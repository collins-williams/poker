/*
 * Deck.h
 *
 *  Created on: Oct 12, 2019
 *      Author: root
 */

#ifndef DECK_H_
#define DECK_H_

#include <vector>
#include "Card.h"

class Deck {
public:
	Deck();
	~Deck();
	// TODO stack --> take a list of cards as the starting position
	void shuffle();
	std::vector<Card> deal(int num_cards);
	void dump();

private:
	std::vector<Card> cards;
};


void deck_test();
#endif /* DECK_H_ */
