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
	virtual bool match(Card a, Card b) =0;

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

class RuleMaker {
public:
    RuleMaker();
    ~RuleMaker();
    Rule* parse_rule(std::string s);

};

class PairRule: public Rule {
public:
    PairRule(std::string s, Ranks::Rank r);
    ~PairRule();
    bool match(Card a, Card b);

    Ranks::Rank rank;
};

class PairRangeRule: public Rule {
public:
    PairRangeRule(std::string s, Ranks::Rank range_top, Ranks::Rank range_bottom);
    ~PairRangeRule();
    bool match(Card a, Card b);

    Ranks::Rank top, bottom;
};

class SuitAffectedRule: public Rule {
public:
    SuitAffectedRule(std::string s, bool suits_match);
    ~SuitAffectedRule();
    bool match(Card a, Card b) = 0;

    bool suited;
};

class ComboRule: public SuitAffectedRule {
public:
    ComboRule(std::string s, bool suits_match, Ranks::Rank first, Ranks::Rank second);
    ~ComboRule();
    bool match(Card a, Card b);

    Ranks::Rank first_rank, second_rank;
};

class ComboRangeRule: public SuitAffectedRule {
public:
    ComboRangeRule(std::string s, bool suits_match, Ranks::Rank top,
            Ranks::Rank upper, Ranks::Rank lower);
    ~ComboRangeRule();
    bool match(Card a, Card b);

    Ranks::Rank top_rank, upper_second, lower_second;
};

//    XYo-WZo specifies all suited combinations in which a X-W == Y-Z
//            that fall between X and W inclusive
class GapRangeRule: public SuitAffectedRule {
public:
    GapRangeRule(std::string s, bool suits_match, Ranks::Rank X, Ranks::Rank y,
            Ranks::Rank w, Ranks::Rank z);
    ~GapRangeRule();
    bool match(Card a, Card b);

    Ranks::Rank x,y,w,z;
};

void rule_test();
#endif /* RULE_H_ */
