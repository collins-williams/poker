/*
 * Rule.h
 *
 *  Created on: Nov 1, 2019
 *      Author: root
 */

#ifndef RULE_H_
#define RULE_H_

#include <string>
#include "Card.h"

//  a rule is a set of pairs of cards like
//
//    a rule can match 2 specific cards or be created from a text string
//    grammar
//    XX     a pair of X
//    XYs    suited combination XY
//    XYo    unsuited combination XY
//    XX-YY  specifies all pairs between X and Y inclusive
//    XYs-XZs specifies all suited combinations
//            with a higher card of X and a lower card between Y and Z inclusive
//    XYo-XZo specifies all unsuited combinations
//            with a higher card of X and a lower card between Y and Z inclusive
//    XYs-WZs specifies all suited combinations in which a X-W == Y-Z
//            that fall between X and W inclusive
//    XYo-WZo specifies all suited combinations in which a X-W == Y-Z
//            that fall between X and W inclusive

class Rule {
public:
	Rule();
	//Rule(std::string s);
	~Rule();

	// return true if rule matches card pair
	virtual bool match(Card a, Card b);

	//TODO to_string();

private:

};

class SingleRule: public Rule {
public:
	SingleRule(Card& a, Card& b);
	bool match(Card a, Card b);
	virtual ~SingleRule();

private:
	Card c1;
	Card c2;
};

class StringRule: public Rule {
public:
	StringRule(std::string s);
	virtual bool match(Card a, Card b) = 0;
	virtual ~StringRule();

    std::string rule;
#if 0
	static const int UnknownRule = 1;
	static const int PairRule = 2;
	static const int SuitedComboRule = 3;
	static const int UnsuitedComboRule = 4;
	static const int PairRangeRule = 5;
	static const int SuitedComboRangeRule = 6;
	static const int UnsuitedComboRangeRule = 7;
#endif

private:

	//int  type;
};

class StringRuleMaker {
public:
    StringRuleMaker();
    ~StringRuleMaker();
    StringRule* parse_rule(std::string s);

};

class PairRule: public StringRule {
public:
    PairRule(std::string s);
    ~PairRule();
    bool match(Card a, Card b);
};

class SuitedComboRule: public StringRule {
public:
    SuitedComboRule(std::string s);
    ~SuitedComboRule();
    bool match(Card a, Card b);
};

class UnsuitedComboRule: public StringRule {
public:
    UnsuitedComboRule(std::string s);
    ~UnsuitedComboRule();
    bool match(Card a, Card b);
};

class PairRangeRule: public StringRule {
public:
    PairRangeRule(std::string s);
    ~PairRangeRule();
    bool match(Card a, Card b);
};

class SuitedComboRangeRule: public StringRule {
public:
    SuitedComboRangeRule(std::string s);
    ~SuitedComboRangeRule();
    bool match(Card a, Card b);
};

class UnsuitedComboRangeRule: public StringRule {
public:
    UnsuitedComboRangeRule(std::string s);
    ~UnsuitedComboRangeRule();
    bool match(Card a, Card b);
};


void rule_test();
#endif /* RULE_H_ */
