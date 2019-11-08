/*
 * Deck_test.cpp
 *
 *  Created on: Oct 12, 2019
 *      Author: root
 */

#include "Deck.h"

using namespace std;

void deck_test() {
	auto d0 = Deck();
	cout << "created deck \n";
	d0.dump();
	cout << "shuffling \n";
	d0.shuffle();
	d0.dump();

	auto d1 = Deck();
	cout << "created deck \n";
	d1.dump();

	auto hand1 = d1.deal(2);
	cout << hand1.size() << '\n';
	for (auto& c : hand1) {
		cout << c;
	}
	d1.dump();

	auto d2 = Deck();
	cout << "created deck \n";
	auto hand2 = d2.deal(53);

}
