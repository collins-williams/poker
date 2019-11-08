/*
 * Hand.h
 *
 *  Created on: Oct 13, 2019
 *      Author: root
 */

#ifndef HAND_H_
#define HAND_H_

#include "Card.h"
#include <vector>
#include <string>

class Hand {
public:
	Hand();
	~Hand();
	void add_card(Card card);
	std::string evaluate();
	void dump();
	long int score();
	//std::string evaluation_string();

	static const long int STRAIGHT_FLUSH_BASE_SCORE = 1000000;
	static const long int FOUR_OF_A_KIND_BASE_SCORE =  900000;
	static const long int FULL_HOUSE_BASE_SCORE     =  800000;
	static const long int FLUSH_BASE_SCORE          =  700000;
	static const long int STRAIGHT_BASE_SCORE       =  600000;
	static const long int THREE_OF_A_KIND_BASE_SCORE =  500000;
	static const long int TWO_PAIR_BASE_SCORE       =  400000;
	static const long int ONE_PAIR_BASE_SCORE       =  100000;
	static const long int HIGH_CARD_BASE_SCORE       = 1;


private:
	std::vector<Card> cards;
	std::string evaluation;
	long int _score;
	int evaluated_size;
	int rank_histogram[Ranks::num_ranks];
	int suit_histogram[Suits::num_suits];
	//std::string evaluate();
	std::string evaluation_string();
	std::string to_string();

	const int MIN_SIZE = 5;
	const int STRAIGHT_LENGTH = 5;
	const int FLUSH_SIZE = 5;



	bool straight_flush();
    bool four_of_a_kind();
    bool full_house();
    bool flush();
    bool straight();
    bool three_of_a_kind();
    bool two_pair();
    bool one_pair();
    bool high_card();

    bool holds(Ranks::Rank arank, Suits::Suit asuit);
    void update_score(long int new_score);

};

void hand_test();

std::ostream& operator<<(std::ostream& os,  Hand& card);

#endif /* HAND_H_ */
