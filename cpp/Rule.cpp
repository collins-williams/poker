/*
 * Rule.cpp
 *
 *  Created on: Nov 1, 2019
 *      Author: root
 */

#include "Rule.h"
#include <cassert>

Rule::Rule() {

}

Rule::~Rule() {
    // TODO Auto-generated destructor stub
}

bool Rule::match(Card a, Card b) {
    return false;
}

SingleRule::SingleRule(Card& a, Card& b) :
        c1 { a }, c2 { b } {
    assert(!(c1 == c2));
}

SingleRule::~SingleRule() {

}

bool SingleRule::match(Card a, Card b) {
    if (a == c1 && b == c2)
        return true;
    if (a == c2 && b == c1)
        return true;
    return false;
}

StringRuleMaker::StringRuleMaker() {

}

StringRuleMaker::~StringRuleMaker() {

}

StringRule::StringRule(std::string st) : rule { st } {
}

StringRule::~StringRule() {

}

PairRule::PairRule(std::string s) : StringRule(s) {
    }
PairRule::~PairRule() {
    }

SuitedComboRule::SuitedComboRule(std::string s) : StringRule(s) {
    }
SuitedComboRule::~SuitedComboRule()    {
}


UnsuitedComboRule::UnsuitedComboRule(std::string s) :  StringRule(s) {
}
UnsuitedComboRule::~UnsuitedComboRule() {
}

PairRangeRule::PairRangeRule(std::string s) :  StringRule(s) {
}
PairRangeRule::~PairRangeRule() {
}


SuitedComboRangeRule::SuitedComboRangeRule(std::string s) : StringRule(s) {
}
SuitedComboRangeRule::~SuitedComboRangeRule() {
}

UnsuitedComboRangeRule::UnsuitedComboRangeRule(std::string s) :  StringRule(s) {
}
UnsuitedComboRangeRule::~UnsuitedComboRangeRule() {
}

StringRule* StringRuleMaker::parse_rule(std::string st) {

    if (st.length() == 2 && st[0] == st[1]) {
        //TODO see that it is a correct card letter
        return new PairRule(st);
    } else if (st.length() == 3) {
        //XYs or XYo
        if (st[2] == 's') {
            return new SuitedComboRule(st);
        } else if (st[2] == 'o') {
            return new UnsuitedComboRule(st);
        } else {
            return nullptr;
        }
    } else if ((st.length() == 5) && (st[0] == st[1]) && (st[2] = '-')
            && (st[3] == st[4])) {
        return new PairRangeRule(st);
    } else if ((st.length() == 7) && (st[0] == st[4]) && (st[3] == '-')
               && (st[2] == 's') && (st[6] == 's')
               && (Ranks::char_to_rank[st[1]]) > Ranks::char_to_rank[st[5]]) {
        return new SuitedComboRangeRule(st);
    } else if ((st.length() == 7) && (st[0] == st[4]) && (st[3] == '-')
            && (st[2] == 'o') && (st[6] == 'o')
            && (Ranks::char_to_rank[st[1]]) > Ranks::char_to_rank[st[5]]) {
        return new UnsuitedComboRangeRule(st);
    } else {
        return nullptr;
    }
    return nullptr;
}

bool PairRule::match(Card a, Card b) {
    return ((Ranks::char_to_rank[rule[0]] == a.rank()) && (a.rank() == b.rank()));
}

bool SuitedComboRule::match(Card a, Card b) {
    if (a.suit() != b.suit()) {
        return false;
    }
    return (((Ranks::char_to_rank[rule[0]] == a.rank())
            && (Ranks::char_to_rank[rule[1]] == b.rank()))
            || ((Ranks::char_to_rank[rule[0]] == b.rank())
                    && (Ranks::char_to_rank[rule[1]] == a.rank())));
}

bool UnsuitedComboRule::match(Card a, Card b) {
    //TODO look at making this a helper
    return (((Ranks::char_to_rank[rule[0]] == a.rank())
            && (Ranks::char_to_rank[rule[1]] == b.rank()))
            || ((Ranks::char_to_rank[rule[0]] == b.rank())
                    && (Ranks::char_to_rank[rule[1]] == a.rank())));
}

bool PairRangeRule::match(Card a, Card b) {
    if (a.rank() != b.rank()) {
        return false;
    }
    return (a.rank() <= Ranks::char_to_rank[rule[0]]
            && a.rank() >= Ranks::char_to_rank[rule[3]]);
}

bool SuitedComboRangeRule::match(Card a, Card b) {
    if (a.suit() != b.suit()) {
        return false;
    }
    if ((a.rank() == Ranks::char_to_rank[rule[0]])
            && (b.rank() <= Ranks::char_to_rank[rule[1]])
            && (b.rank() >= Ranks::char_to_rank[rule[5]])) {
        return true;
    }
    if ((b.rank() == Ranks::char_to_rank[rule[0]])
            && (a.rank() <= Ranks::char_to_rank[rule[1]])
            && (a.rank() >= Ranks::char_to_rank[rule[5]])) {
        return true;
    }
    return false;
}

bool UnsuitedComboRangeRule::match(Card a, Card b) {
    if ((a.rank() == Ranks::char_to_rank[rule[0]])
            && (b.rank() <= Ranks::char_to_rank[rule[1]])
            && (b.rank() >= Ranks::char_to_rank[rule[5]])) {
        return true;
    }
    if ((b.rank() == Ranks::char_to_rank[rule[0]])
            && (a.rank() <= Ranks::char_to_rank[rule[1]])
            && (a.rank() >= Ranks::char_to_rank[rule[5]])) {
        return true;
    }
    return false;
}
