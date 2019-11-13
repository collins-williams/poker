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

SuitAffectedRule::SuitAffectedRule(std::string s) : StringRule(s) {
    suited = false;
}
SuitAffectedRule::~SuitAffectedRule() {
}

PairRule::PairRule(std::string s) :  StringRule(s) {
    }
PairRule::~PairRule() {
    }

PairRangeRule::PairRangeRule(std::string s) :  StringRule(s) {
}
PairRangeRule::~PairRangeRule() {
}

ComboRule::ComboRule(std::string s) : SuitAffectedRule(s) {
    }
ComboRule::~ComboRule()    {
}

ComboRangeRule::ComboRangeRule(std::string s) : SuitAffectedRule(s) {
}
ComboRangeRule::~ComboRangeRule() {
}

GapRangeRule::GapRangeRule(std::string s) :  SuitAffectedRule(s) {
}
GapRangeRule::~GapRangeRule() {

}

//TODO get rid of magic numbers (perhaps per subclass constants?)
//TODO pre chew the rule where practical
//TODO collapse suited and unsuited rules

StringRule* StringRuleMaker::parse_rule(std::string st) {

    //TODO look at throwing an exception rather than a nullptr?

    if (st.length() == 2 && st[0] == st[1]) {
        //TODO see that it is a correct card letter
        return new PairRule(st);
    } else if (st.length() == 3) {
        //XYs or XYo
        auto sr = new ComboRule(st);
        sr->suited = st[2] == 's';
        return sr;
    } else if ((st.length() == 5) && (st[0] == st[1]) && (st[2] = '-')
            && (st[3] == st[4])) {
        return new PairRangeRule(st);
    } else if ((st.length() == 7) && (st[0] == st[4]) && (st[3] == '-') &&
            (Ranks::char_to_rank[st[1]]) > Ranks::char_to_rank[st[5]]) {
        auto sr = new ComboRangeRule(st);
        sr->suited = st[2] == 's' && st[6] == 's';
        return sr;
    } else if ((st.length() == 7) &&
            (Ranks::char_to_rank[st[0]] > Ranks::char_to_rank[st[4]]) &&
            ((Ranks::char_to_rank[st[1]] - Ranks::char_to_rank[st[5]]) == (Ranks::char_to_rank[st[0]] - Ranks::char_to_rank[st[4]])) &&
            (st[3] == '-')) {
        auto sr = new GapRangeRule(st);
        sr->suited = st[2] == 's' && st[6] == 's';
        return sr;
    } else {
        return nullptr;
    }
    return nullptr;
}

bool PairRule::match(Card a, Card b) {
    return ((Ranks::char_to_rank[rule[0]] == a.rank()) && (a.rank() == b.rank()));
}

bool ComboRule::match(Card a, Card b) {
    if ((suited) && (a.suit() != b.suit())) {
        return false;
    }
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

bool ComboRangeRule::match(Card a, Card b) {
    if ((suited) && (a.suit() != b.suit())) {
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

bool GapRangeRule::match(Card a, Card b) {
    if ((suited) && (a.suit() != b.suit())) {
        return false;
    }
    if (a.rank() > b.rank()) {
        return ((a.rank() <= Ranks::char_to_rank[rule[0]] && (a.rank() >= Ranks::char_to_rank[rule[4]])) &&
                ((a.rank() - b.rank()) ==
                (Ranks::char_to_rank[rule[0]] - Ranks::char_to_rank[rule[1]])));
    } else if (b.rank() > a.rank()) {
        return (((b.rank() <= Ranks::char_to_rank[rule[0]]) && (b.rank() >= Ranks::char_to_rank[rule[4]])) &&
                (((b.rank() - a.rank()) ==
                (Ranks::char_to_rank[rule[0]] - Ranks::char_to_rank[rule[1]]))));
    } else {
        return false;
    }
}
