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

bool SingleRule::match(Card a, Card b) {
    if (a == c1 && b == c2)
        return true;
    if (a == c2 && b == c1)
        return true;
    return false;
}

StringRule::StringRule(std::string st) :
        s { st } {
    type = StringRule::UnknownRule;

    // determine rule type
    if ((s.length()) == 2 && (s[0] == s[1])) {
        //XX     a pair of X
        //TODO see that it is a correct card letter
        type = StringRule::PairRule;
    } else if (s.length() == 3) {
        //XYs or XYo
        if (s[2] == 's') {
            type = StringRule::SuitedComboRule;

        } else if (s[2] == 'o') {
            type = StringRule::UnsuitedComboRule;
        }
    } else if ((s.length() == 5) && (s[0] == s[1]) && (s[2] = '-')
            && (s[3] == s[4])) {
        type = StringRule::PairRangeRule;
    } else if ((s.length() == 7) && (s[0] == s[4]) && (s[3] == '-')
            && (s[2] == 's') && (s[6] == 's')
            && (Ranks::char_to_rank[s[1]]) > Ranks::char_to_rank[s[5]]) {
        type = StringRule::SuitedComboRangeRule;
    } else if ((s.length() == 7) && (s[0] == s[4]) && (s[3] == '-')
            && (s[2] == 'o') && (s[6] == 'o')
            && (Ranks::char_to_rank[s[1]]) > Ranks::char_to_rank[s[5]]) {
        type = StringRule::UnsuitedComboRangeRule;
    } else {
        // add this for now to catch rules that don't construct properly
        assert(0);
    }
}

bool StringRule::match(Card a, Card b) {
    assert(type != StringRule::UnknownRule);

    if (type == StringRule::PairRule) {
        if ((Ranks::char_to_rank[s[0]] == a.rank()) && (a.rank() == b.rank())) {
            return true;
        } else {
            return false;
        }
    } else if (type == StringRule::SuitedComboRule) {
        if (a.suit() != b.suit()) {
            return false;
        }
        if (((Ranks::char_to_rank[s[0]] == a.rank())
                && (Ranks::char_to_rank[s[1]] == b.rank()))
                || ((Ranks::char_to_rank[s[0]] == b.rank())
                        && (Ranks::char_to_rank[s[1]] == a.rank()))) {
            return true;
        }
        return false;
    } else if (type == StringRule::UnsuitedComboRule) {
        //TODO look at making this a helper
        if (((Ranks::char_to_rank[s[0]] == a.rank())
                && (Ranks::char_to_rank[s[1]] == b.rank()))
                || ((Ranks::char_to_rank[s[0]] == b.rank())
                        && (Ranks::char_to_rank[s[1]] == a.rank()))) {
            return true;
        }
        return false;
    } else if (type == StringRule::PairRangeRule) {
        if (a.rank() != b.rank()) {
            return false;
        }
        if (a.rank() <= Ranks::char_to_rank[s[0]]
                && a.rank() >= Ranks::char_to_rank[s[3]]) {
            return true;
        }
        return false;
    } else if (type == StringRule::SuitedComboRangeRule) {
        if (a.suit() != b.suit()) {
            return false;
        }
        if ((a.rank() == Ranks::char_to_rank[s[0]])
                && (b.rank() <= Ranks::char_to_rank[s[1]])
                && (b.rank() >= Ranks::char_to_rank[s[5]])) {
            return true;
        }
        if ((b.rank() == Ranks::char_to_rank[s[0]])
                && (a.rank() <= Ranks::char_to_rank[s[1]])
                && (a.rank() >= Ranks::char_to_rank[s[5]])) {
            return true;
        }
        return false;
    } else if (type == StringRule::UnsuitedComboRangeRule) {
        if ((a.rank() == Ranks::char_to_rank[s[0]])
                && (b.rank() <= Ranks::char_to_rank[s[1]])
                && (b.rank() >= Ranks::char_to_rank[s[5]])) {
            return true;
        }
        if ((b.rank() == Ranks::char_to_rank[s[0]])
                && (a.rank() <= Ranks::char_to_rank[s[1]])
                && (a.rank() >= Ranks::char_to_rank[s[5]])) {
            return true;
        }
        return false;
    } else {
        cout << "unimplemented rule type %d\n", type;
        assert(0);
    }
    return false;
}

