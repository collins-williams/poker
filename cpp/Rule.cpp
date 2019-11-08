/*
 * Rule.cpp
 *
 *  Created on: Nov 1, 2019
 *      Author: root
 */

#include "Rule.h"
#include <cassert>


Rule::Rule()
{

}

Rule::~Rule() {
	// TODO Auto-generated destructor stub
}

bool Rule::match(Card a, Card b) {
	return false;
}

SingleRule::SingleRule(Card& a, Card& b ) :c1{a}, c2{b}
{
	assert (!(c1 == c2));
}

bool SingleRule::match(Card a, Card b) {
	if (a == c1 && b == c2) return true;
	if (a == c2 && b == c1) return true;
	return false;
}

StringRule::StringRule(std::string st) : s{st}
{

}

bool StringRule::match(Card a, Card b) {
	return false;
}

