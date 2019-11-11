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
    auto srAA = StringRule("AA");
    assert(srAA.match(as, ah));
    assert(!srAA.match(as, kc));

    auto h9 = Card(Ranks::nine, Suits::hearts);
    auto d9 = Card(Ranks::nine, Suits::diamonds);
    auto sr99 = StringRule("99");
    assert(!sr99.match(as, ah));
    assert(!sr99.match(as, kc));
    assert(sr99.match(d9, h9));

#if 0
    // this ERROR test could be re-instituted if the constructor stopped
    // asserting
    auto sr87 = StringRule("87");
    assert(sr87.match(d9, h9));
#endif

    // XYs    suited combination XY
    auto srAKs = StringRule("AKs");
    auto kh = Card(Ranks::king, Suits::hearts);
    assert(!srAKs.match(ah, kc));
    assert(srAKs.match(kh, ah));
    assert(srAKs.match(ah, kh));

    //   XYo   combination XY w/o regard to include suit
    auto srAKo = StringRule("AKo");
    assert(srAKo.match(ah, kc));
    assert(srAKo.match(kh, ah));
    assert(srAKo.match(ah, kh));
    assert(!srAKo.match(h9, ah));

    // XX-YY  specifies all pairs between X and Y inclusive

    auto srAA88 = StringRule("AA-88");
    assert(srAA88.match(d9, h9));
    assert(!srAA88.match(ah, kc));
    bool res;

    for (const auto r1 : Ranks::All) {
        for (const auto s1 : Suits::All) {
            auto c1 = Card(r1, s1);
            for (const auto r2 : Ranks::All) {
                for (const auto s2 : Suits::All) {
                    auto c2 = Card(r2, s2);
                    if (c1 == c2) {
                        //skip
                    } else {
                        res = (r1 >= Ranks::eight && r2 == r1);
                        assert(srAA88.match(c1, c2) == res);
                        assert(srAA88.match(c2, c1) == res);
                    }
                }
            }
        }
    }

    // XYs-XZs specifies all suited combinations
    //         with a higher card of X and a lower card between Y and Z inclusive
    auto srAKsATs = StringRule("AKs-ATs");
    for (const auto r1 : Ranks::All) {
        for (const auto s1 : Suits::All) {
            auto c1 = Card(r1, s1);
            for (const auto r2 : Ranks::All) {
                for (const auto s2 : Suits::All) {
                    auto c2 = Card(r2, s2);
                    if (c1 == c2) {
                        //skip
                    } else {
                        res = (s1 == s2)
                                && ((r1 == Ranks::ace && r2 <= Ranks::king
                                        && r2 >= Ranks::ten)
                                        || (r2 == Ranks::ace
                                                && r1 <= Ranks::king
                                                && r1 >= Ranks::ten));
                        assert(srAKsATs.match(c1, c2) == res);
                        assert(srAKsATs.match(c2, c1) == res);
                    }
                }
            }
        }
    }

    // TODO   XYo-XZo specifies all unsuited combinations
    //            with a higher card of X and a lower card between Y and Z inclusive
    auto sr98o94o = StringRule("98o-94o");
    for (const auto r1 : Ranks::All) {
        for (const auto s1 : Suits::All) {
            auto c1 = Card(r1, s1);
            for (const auto r2 : Ranks::All) {
                for (const auto s2 : Suits::All) {
                    auto c2 = Card(r2, s2);
                    if (c1 == c2) {
                        //skip
                    } else {
                        res = (r1 == Ranks::nine && r2 <= Ranks::eight
                                && r2 >= Ranks::four)
                                || (r2 == Ranks::nine && r1 <= Ranks::eight
                                        && r1 >= Ranks::four);
                        assert(sr98o94o.match(c1, c2) == res);
                        assert(sr98o94o.match(c2, c1) == res);
                    }
                }
            }
        }
    }

}
