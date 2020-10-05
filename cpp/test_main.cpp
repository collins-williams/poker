/*
 * main.cpp
 *
 *  Created on: Oct 11, 2019
 *      Author: root
 */
#include <iostream>

#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Rule.h"

int main(int argc, char* argv[])  {
#if 0
	for (const auto s : Suits::All) {
		for (const auto r : Ranks::All) {
			Card c = Card(r,s);
			std::cout << c << '\n';
		}
	}
#endif
	deck_test();
	hand_test();
	//rule_test();
}
