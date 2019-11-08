/*
 * Hand_test.cpp
 *
 *  Created on: Oct 13, 2019
 *      Author: root
 */

#include "Card.h"
#include "Hand.h"

#include <cassert>

using namespace std;

void hand_test() {

	//constructor test cases
	auto h = Hand();
	assert(h.evaluate() == "not enough cards");
	assert(h.score() == 0);

	/***********************************************************************/
	// straight flush test cases
	auto c = Card(Ranks::ace, Suits::spades);
	h.add_card(c);
	h.add_card(Card(Ranks::queen, Suits::spades));
	h.add_card(Card(Ranks::king, Suits::spades));
	h.add_card(Card(Ranks::jack, Suits::spades));
	h.add_card(Card(Ranks::ten, Suits::spades));
	h.add_card(Card(Ranks::nine, Suits::spades));
	//h.dump();
	assert(h.score() >= Hand::STRAIGHT_FLUSH_BASE_SCORE);
	assert(h.evaluate() == "straight flush");

	auto hsw = Hand();  //steel wheel
	hsw.add_card(Card(Ranks::four, Suits::spades));
	hsw.add_card(Card(Ranks::three, Suits::spades));
	hsw.add_card(Card(Ranks::deuce, Suits::spades));
	hsw.add_card(Card(Ranks::five, Suits::spades));
	hsw.add_card(Card(Ranks::ace, Suits::spades));
	assert(h.score() >= Hand::STRAIGHT_FLUSH_BASE_SCORE);
	assert(h.evaluate() == "straight flush");
	assert(h.score() > hsw.score());

	/***********************************************************************/
	// four of a kind test cases

	auto h1 = Hand();
	h1.add_card(Card(Ranks::queen, Suits::diamonds));
	h1.add_card(Card(Ranks::queen, Suits::hearts));
	h1.add_card(Card(Ranks::queen, Suits::spades));
	h1.add_card(Card(Ranks::queen, Suits::clubs));
	h1.add_card(Card(Ranks::four, Suits::clubs));
	//h1.dump();
	assert(h1.score() >= Hand::FOUR_OF_A_KIND_BASE_SCORE);
	assert(h1.evaluate() == "four of a kind");

	// test that rank differentiates
	auto h4ka = Hand();
	h4ka.add_card(Card(Ranks::king, Suits::diamonds));
	h4ka.add_card(Card(Ranks::king, Suits::hearts));
	h4ka.add_card(Card(Ranks::king, Suits::spades));
	h4ka.add_card(Card(Ranks::king, Suits::clubs));
	h4ka.add_card(Card(Ranks::ace, Suits::clubs));

	assert(h4ka.score() >= Hand::FOUR_OF_A_KIND_BASE_SCORE);
	assert(h4ka.evaluate() == "four of a kind");
	assert(h4ka.score() > h1.score());

	// test that kicker differentiates
	auto h4kq = Hand();
	h4kq.add_card(Card(Ranks::king, Suits::diamonds));
	h4kq.add_card(Card(Ranks::king, Suits::hearts));
	h4kq.add_card(Card(Ranks::king, Suits::spades));
	h4kq.add_card(Card(Ranks::king, Suits::clubs));
	h4kq.add_card(Card(Ranks::queen, Suits::clubs));

	assert(h4kq.score() >= Hand::FOUR_OF_A_KIND_BASE_SCORE);
	assert(h4kq.evaluate() == "four of a kind");
	assert(h4ka.score() > h4kq.score());

	// test that highest score is less than straight flush
	auto h4ak = Hand();
	h4ak.add_card(Card(Ranks::ace, Suits::diamonds));
	h4ak.add_card(Card(Ranks::ace, Suits::hearts));
	h4ak.add_card(Card(Ranks::ace, Suits::spades));
	h4ak.add_card(Card(Ranks::ace, Suits::clubs));
	h4ak.add_card(Card(Ranks::king, Suits::clubs));

	assert(h4ak.score() >= Hand::FOUR_OF_A_KIND_BASE_SCORE);
	assert(h4ak.evaluate() == "four of a kind");
	assert(h4ak.score() < Hand::STRAIGHT_FLUSH_BASE_SCORE);

	// test cases for bigger hands that allow for kicker to be paired (or more)
	auto h4a3k = Hand();
	h4a3k.add_card(Card(Ranks::ace, Suits::diamonds));
	h4a3k.add_card(Card(Ranks::ace, Suits::hearts));
	h4a3k.add_card(Card(Ranks::ace, Suits::spades));
	h4a3k.add_card(Card(Ranks::ace, Suits::clubs));
	h4a3k.add_card(Card(Ranks::king, Suits::clubs));
	h4a3k.add_card(Card(Ranks::king, Suits::spades));
	h4a3k.add_card(Card(Ranks::king, Suits::hearts));

	assert(h4ak.score() >= Hand::FOUR_OF_A_KIND_BASE_SCORE);
	assert(h4ak.evaluate() == "four of a kind");
	assert(h4ak.score() == h4a3k.score());

	/***********************************************************************/
	// full house test cases

	auto h2 = Hand();
	h2.add_card(Card(Ranks::jack, Suits::spades));
	h2.add_card(Card(Ranks::jack, Suits::hearts));
	h2.add_card(Card(Ranks::jack, Suits::diamonds));
	h2.add_card(Card(Ranks::four, Suits::hearts));
	h2.add_card(Card(Ranks::four, Suits::clubs));
	h2.add_card(Card(Ranks::four, Suits::spades));
	assert(h2.score() >= Hand::FULL_HOUSE_BASE_SCORE);
	assert(h2.evaluate() == "full house");

	// test that highest score is less than 4 of a kind
	auto h3a2k = Hand();
	h3a2k.add_card(Card(Ranks::ace, Suits::spades));
	h3a2k.add_card(Card(Ranks::ace, Suits::hearts));
	h3a2k.add_card(Card(Ranks::ace, Suits::diamonds));
	h3a2k.add_card(Card(Ranks::king, Suits::hearts));
	h3a2k.add_card(Card(Ranks::king, Suits::clubs));

	assert(h3a2k.score() >= Hand::FULL_HOUSE_BASE_SCORE);
	assert(h3a2k.evaluate() == "full house");
	assert(h3a2k.score() < Hand::FOUR_OF_A_KIND_BASE_SCORE);

	// test that pair differentiates
	auto h3a2q = Hand();
	h3a2q.add_card(Card(Ranks::ace, Suits::spades));
	h3a2q.add_card(Card(Ranks::ace, Suits::hearts));
	h3a2q.add_card(Card(Ranks::ace, Suits::diamonds));
	h3a2q.add_card(Card(Ranks::queen, Suits::hearts));
	h3a2q.add_card(Card(Ranks::queen, Suits::clubs));

	assert(h3a2q.score() >= Hand::FULL_HOUSE_BASE_SCORE);
	assert(h3a2q.evaluate() == "full house");
	assert(h3a2k.score() > h3a2q.score());

	// test that three differentiates
	auto h3k2q = Hand();
	h3k2q.add_card(Card(Ranks::king, Suits::spades));
	h3k2q.add_card(Card(Ranks::king, Suits::hearts));
	h3k2q.add_card(Card(Ranks::king, Suits::diamonds));
	h3k2q.add_card(Card(Ranks::queen, Suits::hearts));
	h3k2q.add_card(Card(Ranks::queen, Suits::clubs));

	assert(h3a2q.score() >= Hand::FULL_HOUSE_BASE_SCORE);
	assert(h3a2q.evaluate() == "full house");
	assert(h3a2k.score() > h3k2q.score());
	assert(h3a2q.score() > h3k2q.score());

	/***********************************************************************/
	// flush test cases

	// test that highest flush is less than a full house
	auto h_f_akqj9 = Hand();
	h_f_akqj9.add_card(Card(Ranks::jack, Suits::spades));
	h_f_akqj9.add_card(Card(Ranks::king,  Suits::spades));
	h_f_akqj9.add_card(Card(Ranks::queen, Suits::spades));
	h_f_akqj9.add_card(Card(Ranks::nine, Suits::spades));
	h_f_akqj9.add_card(Card(Ranks::four, Suits::clubs));
	h_f_akqj9.add_card(Card(Ranks::ace,  Suits::spades));
	assert(h_f_akqj9.score() >= Hand::FLUSH_BASE_SCORE);
	assert(h_f_akqj9.evaluate() == "flush");
	assert(h_f_akqj9.score() < Hand::FULL_HOUSE_BASE_SCORE);

	// test that high cards differentiate all the way down
	// test that highest card differentiates
	auto h_f_kqjt8 = Hand();
	h_f_kqjt8.add_card(Card(Ranks::jack, Suits::spades));
	h_f_kqjt8.add_card(Card(Ranks::king,  Suits::spades));
	h_f_kqjt8.add_card(Card(Ranks::queen, Suits::spades));
	h_f_kqjt8.add_card(Card(Ranks::ten, Suits::spades));
	h_f_kqjt8.add_card(Card(Ranks::four, Suits::clubs));
	h_f_kqjt8.add_card(Card(Ranks::eight,  Suits::spades));
	assert(h_f_kqjt8.score() >= Hand::FLUSH_BASE_SCORE);
	assert(h_f_kqjt8.evaluate() == "flush");
	assert(h_f_akqj9.score() > h_f_kqjt8.score());

	// test that second highest card differentiates
	auto h_f_aqjt9 = Hand();
	h_f_aqjt9.add_card(Card(Ranks::jack, Suits::spades));
	h_f_aqjt9.add_card(Card(Ranks::nine,  Suits::spades));
	h_f_aqjt9.add_card(Card(Ranks::queen, Suits::spades));
	h_f_aqjt9.add_card(Card(Ranks::ten, Suits::spades));
	h_f_aqjt9.add_card(Card(Ranks::four, Suits::clubs));
	h_f_aqjt9.add_card(Card(Ranks::ace,  Suits::spades));
	assert(h_f_aqjt9.score() >= Hand::FLUSH_BASE_SCORE);
	assert(h_f_aqjt9.evaluate() == "flush");
	assert(h_f_aqjt9.score() < h_f_akqj9.score());

	// test that third highest card differentiates
	auto h_f_akjt9 = Hand();
	h_f_akjt9.add_card(Card(Ranks::jack, Suits::spades));
	h_f_akjt9.add_card(Card(Ranks::king,  Suits::spades));
	h_f_akjt9.add_card(Card(Ranks::ten, Suits::spades));
	h_f_akjt9.add_card(Card(Ranks::nine, Suits::spades));
	h_f_akjt9.add_card(Card(Ranks::four, Suits::clubs));
	h_f_akjt9.add_card(Card(Ranks::ace,  Suits::spades));
	assert(h_f_akjt9.score() >= Hand::FLUSH_BASE_SCORE);
	assert(h_f_akjt9.evaluate() == "flush");
	assert(h_f_akjt9.score() < h_f_akqj9.score());

	// test that fourth highest card differentiates
	auto h_f_akqt9 = Hand();
	h_f_akqt9.add_card(Card(Ranks::ten, Suits::spades));
	h_f_akqt9.add_card(Card(Ranks::king,  Suits::spades));
	h_f_akqt9.add_card(Card(Ranks::queen, Suits::spades));
	h_f_akqt9.add_card(Card(Ranks::nine, Suits::spades));
	h_f_akqt9.add_card(Card(Ranks::four, Suits::clubs));
	h_f_akqt9.add_card(Card(Ranks::ace,  Suits::spades));
	assert(h_f_akqt9.score() >= Hand::FLUSH_BASE_SCORE);
	assert(h_f_akqt9.evaluate() == "flush");
	assert(h_f_akqt9.score() < h_f_akqj9.score());

	// test that fifth highest card differentiates
	auto h_f_akqj8 = Hand();
	h_f_akqj8.add_card(Card(Ranks::jack, Suits::spades));
	h_f_akqj8.add_card(Card(Ranks::king,  Suits::spades));
	h_f_akqj8.add_card(Card(Ranks::queen, Suits::spades));
	h_f_akqj8.add_card(Card(Ranks::eight, Suits::spades));
	h_f_akqj8.add_card(Card(Ranks::four, Suits::clubs));
	h_f_akqj8.add_card(Card(Ranks::ace,  Suits::spades));
	assert(h_f_akqj8.score() >= Hand::FLUSH_BASE_SCORE);
	assert(h_f_akqj8.evaluate() == "flush");
	assert(h_f_akqj8.score() < h_f_akqj9.score());

	// test total order
	assert(h_f_kqjt8.score() < h_f_aqjt9.score());
	assert(h_f_aqjt9.score() < h_f_akjt9.score());
	assert(h_f_akjt9.score() < h_f_akqt9.score());
	assert(h_f_akqt9.score() < h_f_akqj9.score());
	assert(h_f_akqj8.score() < h_f_akqj9.score());

	/***********************************************************************/
	// Straight test cases
	auto h4 = Hand();
	h4.add_card(Card(Ranks::jack, Suits::spades));
	h4.add_card(Card(Ranks::king,  Suits::spades));
	h4.add_card(Card(Ranks::queen, Suits::spades));
	h4.add_card(Card(Ranks::nine, Suits::spades));
	h4.add_card(Card(Ranks::ten, Suits::clubs));
	h4.add_card(Card(Ranks::three,  Suits::hearts));
	//h4.dump();
	assert(h4.evaluate() == "straight");
	assert(h4.score() > Hand::STRAIGHT_BASE_SCORE);

	// test that higher start card differentiates
	auto h5 = Hand();
	h5.add_card(Card(Ranks::jack, Suits::spades));
	h5.add_card(Card(Ranks::king,  Suits::spades));
	h5.add_card(Card(Ranks::queen, Suits::spades));
	h5.add_card(Card(Ranks::nine, Suits::spades));
	h5.add_card(Card(Ranks::ten, Suits::clubs));
	h5.add_card(Card(Ranks::ace,  Suits::hearts));
	//h5.dump();

	assert(h5.evaluate() == "straight");
	assert(h5.score() > h4.score());

	// test that highest straight is less than a flush
	auto h33 = Hand();
	h33.add_card(Card(Ranks::jack, Suits::spades));
	h33.add_card(Card(Ranks::king,  Suits::spades));
	h33.add_card(Card(Ranks::queen, Suits::spades));
	h33.add_card(Card(Ranks::ace, Suits::spades));
	h33.add_card(Card(Ranks::ten, Suits::clubs));
	h33.add_card(Card(Ranks::three,  Suits::hearts));
	assert(h33.evaluate() == "straight");
    assert(h33.score() < Hand::FLUSH_BASE_SCORE);

	/***********************************************************************/
	// three of a kind test cases

	auto h6 = Hand();
	h6.add_card(Card(Ranks::jack, Suits::spades));
	h6.add_card(Card(Ranks::jack,  Suits::clubs));
	h6.add_card(Card(Ranks::queen, Suits::spades));
	h6.add_card(Card(Ranks::nine, Suits::spades));
	h6.add_card(Card(Ranks::ten, Suits::clubs));
	h6.add_card(Card(Ranks::jack,  Suits::hearts));
	//h6.dump();

	assert(h6.evaluate() == "three of a kind");
	assert(h6.score() >= Hand::THREE_OF_A_KIND_BASE_SCORE);

	// test that first kicker differentiates
	auto h7 = Hand();
	h7.add_card(Card(Ranks::jack, Suits::spades));
	h7.add_card(Card(Ranks::jack,  Suits::clubs));
	h7.add_card(Card(Ranks::ace, Suits::spades));
	h7.add_card(Card(Ranks::nine, Suits::spades));
	h7.add_card(Card(Ranks::ten, Suits::clubs));
	h7.add_card(Card(Ranks::jack,  Suits::hearts));

	assert(h7.evaluate() == "three of a kind");
	assert(h7.score() > h6.score());

	// test that second kicker differentiates
	auto h8 = Hand();
	h8.add_card(Card(Ranks::jack, Suits::spades));
	h8.add_card(Card(Ranks::jack,  Suits::clubs));
	h8.add_card(Card(Ranks::ace, Suits::spades));
	h8.add_card(Card(Ranks::nine, Suits::spades));
	h8.add_card(Card(Ranks::deuce, Suits::clubs));
	h8.add_card(Card(Ranks::jack,  Suits::hearts));

	assert(h8.evaluate() == "three of a kind");
	assert(h8.score() < h7.score());
	assert(h8.score() > h6.score());

	// test that highest hand is less than straight
	auto h32 = Hand();
	h32.add_card(Card(Ranks::ace, Suits::spades));
	h32.add_card(Card(Ranks::ace,  Suits::clubs));
	h32.add_card(Card(Ranks::ace, Suits::hearts));
	h32.add_card(Card(Ranks::king, Suits::spades));
	h32.add_card(Card(Ranks::queen, Suits::clubs));
	h32.add_card(Card(Ranks::jack,  Suits::hearts));
	assert(h32.evaluate() == "three of a kind");
	assert(h32.score() < Hand::STRAIGHT_BASE_SCORE);

	/***********************************************************************/
	// test cases for two pair
	// test case for difference in second pair
	auto h9 = Hand();
	h9.add_card(Card(Ranks::jack, Suits::spades));
	h9.add_card(Card(Ranks::jack,  Suits::clubs));
	h9.add_card(Card(Ranks::ace, Suits::spades));
	h9.add_card(Card(Ranks::nine, Suits::spades));
	h9.add_card(Card(Ranks::deuce, Suits::clubs));
	h9.add_card(Card(Ranks::deuce,  Suits::hearts));

	assert(h9.evaluate() == "two pair");
	assert(h9.score() >= Hand::TWO_PAIR_BASE_SCORE);

	auto h10 = Hand();
	h10.add_card(Card(Ranks::jack, Suits::spades));
	h10.add_card(Card(Ranks::jack,  Suits::clubs));
	h10.add_card(Card(Ranks::ace, Suits::spades));
	h10.add_card(Card(Ranks::nine, Suits::spades));
	h10.add_card(Card(Ranks::deuce, Suits::clubs));
	h10.add_card(Card(Ranks::nine,  Suits::hearts));

	assert(h10.evaluate() == "two pair");
	assert(h10.score() > h9.score());

	// test case for difference in first pair
	auto h12 = Hand();
	h12.add_card(Card(Ranks::jack, Suits::spades));
	h12.add_card(Card(Ranks::jack,  Suits::clubs));
	h12.add_card(Card(Ranks::ace, Suits::spades));
	h12.add_card(Card(Ranks::nine, Suits::spades));
	h12.add_card(Card(Ranks::deuce, Suits::clubs));
	h12.add_card(Card(Ranks::nine,  Suits::hearts));
	assert(h12.evaluate() == "two pair");

	auto h13 = Hand();
	h13.add_card(Card(Ranks::queen, Suits::spades));
	h13.add_card(Card(Ranks::queen,  Suits::clubs));
	h13.add_card(Card(Ranks::ace, Suits::spades));
	h13.add_card(Card(Ranks::nine, Suits::spades));
	h13.add_card(Card(Ranks::deuce, Suits::clubs));
	h13.add_card(Card(Ranks::nine,  Suits::hearts));
	assert(h13.evaluate() == "two pair");
	assert(h12.score() < h13.score());

	// test case for difference in kicker
	auto h14 = Hand();
	h14.add_card(Card(Ranks::jack, Suits::spades));
	h14.add_card(Card(Ranks::jack,  Suits::clubs));
	h14.add_card(Card(Ranks::ace, Suits::spades));
	h14.add_card(Card(Ranks::nine, Suits::spades));
	h14.add_card(Card(Ranks::deuce, Suits::clubs));
	h14.add_card(Card(Ranks::nine,  Suits::clubs));
	assert(h14.evaluate() == "two pair");

	auto h15 = Hand();
	h15.add_card(Card(Ranks::jack, Suits::spades));
	h15.add_card(Card(Ranks::jack,  Suits::clubs));
	h15.add_card(Card(Ranks::deuce, Suits::spades));
	h15.add_card(Card(Ranks::nine, Suits::spades));
	h15.add_card(Card(Ranks::deuce, Suits::clubs));
	h15.add_card(Card(Ranks::nine,  Suits::hearts));
	assert(h15.evaluate() == "two pair");
	assert(h15.score() < h14.score());

	// test that best two pair is less than 3 of a kind
	auto h30 = Hand();
	h30.add_card(Card(Ranks::ace, Suits::spades));
	h30.add_card(Card(Ranks::ace,  Suits::clubs));
	h30.add_card(Card(Ranks::king, Suits::spades));
	h30.add_card(Card(Ranks::king, Suits::hearts));
	h30.add_card(Card(Ranks::queen, Suits::clubs));
	h30.add_card(Card(Ranks::nine,  Suits::hearts));
	assert(h30.evaluate() == "two pair");
	assert(h30.score() < Hand::THREE_OF_A_KIND_BASE_SCORE);


	// test kicker can be paired
	auto h31 = Hand();
	h31.add_card(Card(Ranks::ace, Suits::spades));
	h31.add_card(Card(Ranks::ace,  Suits::clubs));
	h31.add_card(Card(Ranks::king, Suits::spades));
	h31.add_card(Card(Ranks::king, Suits::hearts));
	h31.add_card(Card(Ranks::queen, Suits::clubs));
	h31.add_card(Card(Ranks::queen,  Suits::hearts));
	assert(h31.evaluate() == "two pair");
	assert(h31.score() == h30.score());


/***********************************************************************/
	// test cases for one pair
	auto h16 = Hand();
	h16.add_card(Card(Ranks::jack, Suits::spades));
	h16.add_card(Card(Ranks::queen,  Suits::clubs));
	h16.add_card(Card(Ranks::deuce, Suits::spades));
	h16.add_card(Card(Ranks::nine, Suits::spades));
	h16.add_card(Card(Ranks::three, Suits::clubs));
	h16.add_card(Card(Ranks::nine,  Suits::hearts));
	assert(h16.evaluate() == "one pair");
	assert(h16.score() >= Hand::ONE_PAIR_BASE_SCORE);

	// test that pair differentiates
	auto h17 = Hand();
	h17.add_card(Card(Ranks::jack, Suits::spades));
	h17.add_card(Card(Ranks::queen,  Suits::clubs));
	h17.add_card(Card(Ranks::deuce, Suits::spades));
	h17.add_card(Card(Ranks::jack, Suits::clubs));
	h17.add_card(Card(Ranks::three, Suits::clubs));
	h17.add_card(Card(Ranks::nine,  Suits::hearts));
	assert(h17.evaluate() == "one pair");
	assert(h17.score() > h16.score());

	// test that first kicker differentiates
	auto h18 = Hand();
	h18.add_card(Card(Ranks::jack, Suits::spades));
	h18.add_card(Card(Ranks::king,  Suits::clubs));
	h18.add_card(Card(Ranks::deuce, Suits::spades));
	h18.add_card(Card(Ranks::jack, Suits::clubs));
	h18.add_card(Card(Ranks::three, Suits::clubs));
	h18.add_card(Card(Ranks::nine,  Suits::hearts));
	assert(h18.evaluate() == "one pair");
	assert(h17.score() < h18.score());

	// test that second kicker differentiates
	auto h19 = Hand();
	h19.add_card(Card(Ranks::jack, Suits::spades));
	h19.add_card(Card(Ranks::king,  Suits::clubs));
	h19.add_card(Card(Ranks::deuce, Suits::spades));
	h19.add_card(Card(Ranks::jack, Suits::clubs));
	h19.add_card(Card(Ranks::three, Suits::clubs));
	h19.add_card(Card(Ranks::eight,  Suits::hearts));
	assert(h19.evaluate() == "one pair");
	assert(h19.score() < h18.score());

	// test that third kicker differentiates
	auto h20 = Hand();
	h20.add_card(Card(Ranks::jack, Suits::spades));
	h20.add_card(Card(Ranks::king,  Suits::clubs));
	h20.add_card(Card(Ranks::deuce, Suits::spades));
	h20.add_card(Card(Ranks::jack, Suits::clubs));
	h20.add_card(Card(Ranks::four, Suits::clubs));
	h20.add_card(Card(Ranks::eight,  Suits::hearts));
	assert(h20.evaluate() == "one pair");
	assert(h20.score() > h19.score());

	// test that if no differences the scores are equal
	auto h21 = Hand();
	h21.add_card(Card(Ranks::jack, Suits::hearts));
	h21.add_card(Card(Ranks::king,  Suits::hearts));
	h21.add_card(Card(Ranks::deuce, Suits::spades));
	h21.add_card(Card(Ranks::jack, Suits::clubs));
	h21.add_card(Card(Ranks::four, Suits::clubs));
	h21.add_card(Card(Ranks::eight,  Suits::hearts));
	assert(h21.evaluate() == "one pair");
	assert(h20.score() == h21.score());

	/***********************************************************************/
	// test that highest is smaller than pair
    auto h22 = Hand();
	h22.add_card(Card(Ranks::ace, Suits::hearts));
	h22.add_card(Card(Ranks::king,  Suits::hearts));
	h22.add_card(Card(Ranks::queen, Suits::spades));
	h22.add_card(Card(Ranks::jack, Suits::clubs));
	h22.add_card(Card(Ranks::nine, Suits::clubs));
	h22.add_card(Card(Ranks::eight,  Suits::hearts));
	assert(h22.evaluate() == "high card");
	assert(h22.score() < Hand::ONE_PAIR_BASE_SCORE);
	assert(h22.score() > 0);

	// test that fifth highest card matters
    auto h23 = Hand();
	h23.add_card(Card(Ranks::ace, Suits::hearts));
	h23.add_card(Card(Ranks::king,  Suits::hearts));
	h23.add_card(Card(Ranks::queen, Suits::spades));
	h23.add_card(Card(Ranks::jack, Suits::clubs));
	h23.add_card(Card(Ranks::seven, Suits::clubs));
	h23.add_card(Card(Ranks::eight,  Suits::hearts));
	assert(h23.evaluate() == "high card");
	assert(h23.score() > 0);
	assert(h23.score() < h22.score());

	// test that fourth highest card matters
    auto h24 = Hand();
	h24.add_card(Card(Ranks::ace, Suits::hearts));
	h24.add_card(Card(Ranks::king,  Suits::hearts));
	h24.add_card(Card(Ranks::queen, Suits::spades));
	h24.add_card(Card(Ranks::ten, Suits::clubs));
	h24.add_card(Card(Ranks::seven, Suits::clubs));
	h24.add_card(Card(Ranks::eight,  Suits::hearts));
	assert(h24.evaluate() == "high card");
	assert(h24.score() > 0);
	assert(h24.score() < h23.score());

	// test that third highest card matters
    auto h25 = Hand();
	h25.add_card(Card(Ranks::ace, Suits::hearts));
	h25.add_card(Card(Ranks::king,  Suits::hearts));
	h25.add_card(Card(Ranks::jack, Suits::spades));
	h25.add_card(Card(Ranks::ten, Suits::clubs));
	h25.add_card(Card(Ranks::seven, Suits::clubs));
	h25.add_card(Card(Ranks::eight,  Suits::hearts));
	assert(h25.evaluate() == "high card");
	assert(h25.score() > 0);
	assert(h25.score() < h24.score());

	// test that second highest card matters
    auto h26 = Hand();
	h26.add_card(Card(Ranks::ace, Suits::hearts));
	h26.add_card(Card(Ranks::queen,  Suits::hearts));
	h26.add_card(Card(Ranks::jack, Suits::spades));
	h26.add_card(Card(Ranks::ten, Suits::clubs));
	h26.add_card(Card(Ranks::seven, Suits::clubs));
	h26.add_card(Card(Ranks::eight,  Suits::hearts));
	assert(h26.evaluate() == "high card");
	assert(h26.score() > 0);
	assert(h26.score() < h25.score());

	// test that highest card matters
    auto h27 = Hand();
	h27.add_card(Card(Ranks::king, Suits::hearts));
	h27.add_card(Card(Ranks::queen,  Suits::hearts));
	h27.add_card(Card(Ranks::jack, Suits::spades));
	h27.add_card(Card(Ranks::ten, Suits::clubs));
	h27.add_card(Card(Ranks::seven, Suits::clubs));
	h27.add_card(Card(Ranks::eight,  Suits::hearts));
	assert(h27.evaluate() == "high card");
	assert(h27.score() > 0);
	assert(h27.score() < h26.score());

	/************************************************************************/
	// test case for rejecting duplicate cards in hand
	auto h11 = Hand();
	h11.add_card(Card(Ranks::queen, Suits::spades));
	h11.add_card(Card(Ranks::queen, Suits::spades));
	h11.add_card(Card(Ranks::king, Suits::spades));
	h11.add_card(Card(Ranks::ten, Suits::spades));
	h11.add_card(Card(Ranks::nine, Suits::spades));
	assert(h11.evaluate() == "not enough cards");
	assert(h11.score() == 0);

}
