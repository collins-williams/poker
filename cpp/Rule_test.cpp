/*
 * Rule_test.cpp
 *
 *  Created on: Nov 1, 2019
 *      Author: root
 */

#include "Rule.h"

#include <cassert>

//
//    a rule can match 2 specific cards
// TODO or be created from a text string
//    grammar

// TODO  XYs    suited combination XY
// TODO   XYo    unsuited combination XY
// TODO   XX-YY  specifies all pairs between X and Y inclusive
// TODO   XYs-XZs specifies all suited combinations
//            with a higher card of X and a lower card between Y and Z inclusive
// TODO   XYo-XZo specifies all unsuited combinations
//            with a higher card of X and a lower card between Y and Z inclusive
// TODO  XYs-WZs specifies all suited combinations in which a X-W == Y-Z
//            that fall between X and W inclusive
// TODO  XYo-WZo specifies all suited combinations in which a X-W == Y-Z
//            that fall between X and W inclusive

void rule_test() {
	auto ah = Card(Ranks::ace, Suits::hearts);
	auto as = Card(Ranks::ace, Suits::spades);
	auto kc = Card(Ranks::king, Suits::clubs);
	auto qd = Card(Ranks::queen, Suits::diamonds);
	auto r = SingleRule(ah, kc);

	assert(r.match(ah, kc));
	assert(r.match(kc, ah));
	assert(!r.match(kc, qd));
	assert(!r.match(ah, qd));
	assert(!r.match(qd, ah));
	assert(!r.match(qd, kc));

	//auto r1 = SingleRule(qd, qd);  need to keep this commented out

	//  XX     a pair of X
    auto sr = StringRule("AA");
    assert(sr.match(as,ah));
    assert(!sr.match(as,kc));

}
