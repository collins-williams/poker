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

RuleMaker::RuleMaker() {

}

RuleMaker::~RuleMaker() {

}

SuitAffectedRule::SuitAffectedRule(std::string s, bool suits_match) : Rule() {
    suited = suits_match;
}
SuitAffectedRule::~SuitAffectedRule() {
}

PairRule::PairRule(std::string s, Ranks::Rank r) :  Rule() {
    rank = r;
    }
PairRule::~PairRule() {
    }

PairRangeRule::PairRangeRule(std::string s, Ranks::Rank range_top, Ranks::Rank range_bottom)
    :  Rule() {
    top = range_top;
    bottom = range_bottom;
}

PairRangeRule::~PairRangeRule() {
}

ComboRule::ComboRule(std::string s, bool suits_match, Ranks::Rank first, Ranks::Rank second) : SuitAffectedRule(s, suits_match) {
    first_rank = first;
    second_rank = second;
}
ComboRule::~ComboRule()    {
}

ComboRangeRule::ComboRangeRule(std::string s, bool suits_match, Ranks::Rank top,
        Ranks::Rank upper, Ranks::Rank lower) : SuitAffectedRule(s, suits_match) {
    top_rank = top;
    upper_second = upper;
    lower_second = lower;
}
ComboRangeRule::~ComboRangeRule() {
}

GapRangeRule::GapRangeRule(std::string s, bool suits_match, Ranks::Rank X, Ranks::Rank Y,
            Ranks::Rank W, Ranks::Rank Z):  SuitAffectedRule(s, suits_match) {
    x = X;
    y = Y;
    w = W;
    z = Z;
}
GapRangeRule::~GapRangeRule() {

}

//TODO get rid of magic numbers (perhaps per subclass constants?)

Rule* RuleMaker::parse_rule(std::string st) {

    //TODO look at throwing an exception rather than a nullptr?

    if (st.length() == 2 && st[0] == st[1]) {
        //TODO see that it is a correct card letter
        return new PairRule(st, Ranks::char_to_rank[st[0]]);
    } else if (st.length() == 3) {
        //XYs or XYo
        return new ComboRule(st, st[2] == 's', Ranks::char_to_rank[st[0]],
                Ranks::char_to_rank[st[1]]);
    } else if ((st.length() == 5) && (st[0] == st[1]) && (st[2] = '-')
            && (st[3] == st[4])) {
        return new PairRangeRule(st, Ranks::char_to_rank[st[0]], Ranks::char_to_rank[st[3]]);
    } else if ((st.length() == 7) && (st[0] == st[4]) && (st[3] == '-') &&
            (Ranks::char_to_rank[st[1]]) > Ranks::char_to_rank[st[5]]) {
        return new ComboRangeRule(st, st[2] == 's' && st[6] == 's',
                Ranks::char_to_rank[st[0]], Ranks::char_to_rank[st[1]],
                Ranks::char_to_rank[st[5]]);
    } else if ((st.length() == 7) &&
            (Ranks::char_to_rank[st[0]] > Ranks::char_to_rank[st[4]]) &&
            ((Ranks::char_to_rank[st[1]] - Ranks::char_to_rank[st[5]]) == (Ranks::char_to_rank[st[0]] - Ranks::char_to_rank[st[4]])) &&
            (st[3] == '-')) {
        return new GapRangeRule(st, st[2] == 's' && st[6] == 's',
                Ranks::char_to_rank[st[0]], Ranks::char_to_rank[st[1]],
                Ranks::char_to_rank[st[4]], Ranks::char_to_rank[st[5]]);
    } else {
        return nullptr;
    }
    return nullptr;
}

bool PairRule::match(Card a, Card b) {
    return ((rank == a.rank()) && (a.rank() == b.rank()));
}

bool ComboRule::match(Card a, Card b) {
    if ((suited) && (a.suit() != b.suit())) {
        return false;
    }
    return (((first_rank == a.rank()) && (second_rank == b.rank())) ||
            ((first_rank == b.rank()) && (second_rank == a.rank())));
}

bool PairRangeRule::match(Card a, Card b) {
    if (a.rank() != b.rank()) {
        return false;
    }
    return ((a.rank() <= top) && (a.rank() >= bottom));
}

bool ComboRangeRule::match(Card a, Card b) {
    if ((suited) && (a.suit() != b.suit())) {
        return false;
    }
    if ((a.rank() == top_rank)
            && (b.rank() <= upper_second)
            && (b.rank() >= lower_second)) {
        return true;
    }
    if ((b.rank() == top_rank)
            && (a.rank() <= upper_second)
            && (a.rank() >= lower_second)) {
        return true;
    }
    return false;
}

bool GapRangeRule::match(Card a, Card b) {
    if ((suited) && (a.suit() != b.suit())) {
        return false;
    }
    if (a.rank() > b.rank()) {
        return ((a.rank() <= x && (a.rank() >= w)) &&
                ((a.rank() - b.rank()) == (x - y)));
    } else if (b.rank() > a.rank()) {
        return (((b.rank() <= x) && (b.rank() >= w)) &&
                (((b.rank() - a.rank()) == (x - y))));
    } else {
        return false;
    }
}
