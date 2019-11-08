/*
 * Hand.cpp
 *
 *  Created on: Oct 13, 2019
 *      Author: root
 */

#include "Hand.h"

#include <algorithm>

using namespace std;

Hand::Hand() {
    cards.clear();
	evaluation = "not enough cards";
	_score = 0;
	evaluated_size = 0;
	for (int r = 0; r < Ranks::num_ranks; r++) {
		rank_histogram[r] = 0;
	}
	for (int s = 0; s < Suits::num_suits; s++) {
		suit_histogram[s] = 0;
	}
}

Hand::~Hand() {
	// TODO Auto-generated destructor stub
}

void Hand::add_card(Card card) {

	if (holds(card.rank(), card.suit())){
		return;
	}

	cards.push_back(card);

	sort(cards.begin(), cards.end());

	rank_histogram[card.rank()] += 1;
	suit_histogram[card.suit()] += 1;
	if (cards.size() >= Hand::MIN_SIZE) {
		evaluation.clear();
		_score      = 0;
	} else {
		evaluation = "not enough cards";
		_score = 0;
	}
}

string Hand::to_string() {
	string s;

	for (auto& c : cards) {
		s.append(c.to_string());
	}
	s += '\n';
	// can't do the following since it can lead to recursion (and change the state of the object)
//	s += std::to_string(score()) + '\n';
//	s +=  evaluation + '\n';
	// so we do this instead..
	s += _score + '\n';
	s += evaluation + '\n';

	for (const auto suit : Suits::All)  {
		s += std::to_string(suit_histogram[suit]) + ' ';
	}
	s += '\n';

	for (const auto r : Ranks::All) {
		s += std::to_string(rank_histogram[r]) + ' ';
	}
	s += '\n';

	return s;
}

void Hand::dump() {
	cout << to_string();
}

long int Hand::score() {
	if (_score == 0) {
		evaluate();
	}
	return _score;
}

string Hand::evaluate() {
	  // evaluate if we have not evaluated before and there are enough cards OR
	  // if we have more cards than the last time we evaluated

	if (((evaluation.empty()) && (cards.size() >= Hand::MIN_SIZE)) ||
			((cards.size() >= Hand::MIN_SIZE) && (evaluated_size < cards.size()))) {
		evaluation = evaluation_string();
		evaluated_size = cards.size();
	}
	return evaluation;
}

string Hand::evaluation_string() {
    if (straight_flush()) {
    	return "straight flush";
    } else if (four_of_a_kind()) {
    	return "four of a kind";
    } else if (full_house()) {
    	return "full house";
    } else if (flush()) {
    	return "flush";
    } else if (straight()) {
    	return "straight";
    } else if (three_of_a_kind()) {
    	return "three of a kind";
    } else if (two_pair()) {
    	return "two pair";
    } else if (one_pair()) {
    	return "one pair";
    } else if (high_card()) {
        return "high card";
    } else return "oops" + to_string();
}

bool Hand::holds(Ranks::Rank arank, Suits::Suit asuit) {
	for (auto& c : cards) {
		if (c.rank() == arank && c.suit() == asuit) {
			return true;
		}
	}
	return false;
}

void Hand::update_score(long int new_score) {
	if (new_score > _score) _score = new_score;
}

//
// all of the following functions have the same semantics:
// 1) they return true if the hand_type matches
// 2) if they are returning true they set _score
//

bool Hand::straight_flush() {
    bool ret = false;
    for(int low_card = 0; low_card <= (cards.size() - Hand::STRAIGHT_LENGTH); low_card++ ) {
    	auto ok = true;
    	int step = 1;
    	Card& start_card = cards.at(low_card);
    	while (ok && step < Hand::STRAIGHT_LENGTH) {
    		if ((holds(Ranks::All[start_card.rank() + step], start_card.suit())) ||
    			((start_card.rank() == Ranks::Rank::deuce) &&
    					(step == Hand::STRAIGHT_LENGTH -1) &&
						(holds(Ranks::Rank::ace, start_card.suit())))
				) {
    			step += 1;
    		} else {
    			ok = false;
    		}
    	}
    	if (ok) {
    		long int new_score = Hand::STRAIGHT_FLUSH_BASE_SCORE + start_card.rank() +
    				(Hand::STRAIGHT_LENGTH - 1);
    		update_score(new_score);
    		ret = true;
    	} else {
    	}
    }

    return ret;
}


bool Hand::four_of_a_kind() {
	bool kick_found = false;
	int four_rank;

	bool four_found = false;
	int  kick_rank;

	for (auto r = Ranks::num_ranks - 1; ((r >= 0) && ((!kick_found) || (!four_found)));
			r--) {
		if (!kick_found && rank_histogram[r] > 0 && rank_histogram[r] < 4) {
			kick_found = true;
			kick_rank  = r;
		}

		if (!four_found && rank_histogram[r] >=4) {
			four_found = true;
			four_rank  = r;
		}
	}
    if (four_found && kick_found) {
    	_score = Hand::FOUR_OF_A_KIND_BASE_SCORE + four_rank*Ranks::num_ranks + kick_rank;
    	return true;
    }

	return false;
}

bool Hand::full_house() {

	int three_rank = -1;
	int   two_rank = -1;

	for (auto r = Ranks::num_ranks - 1; ((r >= 0) && ((three_rank == -1) || (two_rank == -1)));
			r--) {
		if (three_rank == -1 && rank_histogram[r] >= 3) {
			three_rank = r;
		} else if (two_rank == -1 && rank_histogram[r] >=2) {
			two_rank  = r;
		}
	}
    if (three_rank != -1 && two_rank != -1) {
    	_score = Hand::FULL_HOUSE_BASE_SCORE + three_rank*Ranks::num_ranks + two_rank;
    	return true;
    }
	return false;
}

bool Hand::flush() {

	for (auto s = 0; s < Suits::num_suits; s++) {
		if (suit_histogram[s] >= Hand::FLUSH_SIZE) {
            _score = Hand::FLUSH_BASE_SCORE;
            // now add something for FLUSH_SIZE highest ranked cards
            auto counted = 0;
            auto r = Ranks::num_ranks -1;
            while (counted < Hand::FLUSH_SIZE && r >= 0) {
            	if (holds(Ranks::All[r], Suits::All[s])) {
            		_score += (1 << r);
            		counted++;
            	}
            	r--;
            }
         return true;
		}
	}

	return false;
}

bool Hand::straight() {
	  for (auto r = Ranks::num_ranks -1; r >= Hand::STRAIGHT_LENGTH; r--) {
		  auto ok = true;
		  auto rank2 = r;
		  while ((ok) && (rank2 > r - Hand::STRAIGHT_LENGTH)) {
			  if (rank_histogram[rank2] == 0) {
				  ok = false;
			  }
			  rank2--;
		  }
		  if (ok) {
			  _score = Hand::STRAIGHT_BASE_SCORE + r;
			  return true;
		  }
	  }
      // check for wheel
	  if ((rank_histogram[Ranks::ace] != 0) &&
			  (rank_histogram[Ranks::deuce] != 0) &&
			  (rank_histogram[Ranks::three] != 0) &&
			  (rank_histogram[Ranks::four]  != 0) &&
			  (rank_histogram[Ranks::five]  != 0)) {
	        _score = Hand::STRAIGHT_BASE_SCORE + Ranks::five;
	        return true;
	  }
	return false;
}

bool Hand::three_of_a_kind() {
	auto three_rank = -1;
	auto kick1      = -1;
	auto kick2      = -1;

	for(auto r = Ranks::num_ranks -1;
			((r >= 0) && ((three_rank == -1) || (kick1 == -1) || (kick2 == -1)));
			r--) {
		if (three_rank == -1 && rank_histogram[r] == 3) {
			three_rank = r;
		} else if (kick1 == -1 && rank_histogram[r] == 1) {
			kick1 = r;
		} else if (kick2 == -1 && rank_histogram[r] == 1) {
			kick2 = r;
		} else {
			// do nothing
		}
	}
	if (three_rank != -1 && kick1 != -1 && kick2 != -1) {
		_score = Hand::THREE_OF_A_KIND_BASE_SCORE + three_rank * Ranks::num_ranks * Ranks::num_ranks +
				kick1 * Ranks::num_ranks + kick2;
		return true;
	}
	return false;
}

bool Hand::two_pair() {
    auto pair1_rank = -1;
    auto pair2_rank = -1;
    auto kick1_rank = -1;
    for (auto r = Ranks::num_ranks -1;
    		((r >= 0) && ((pair1_rank == -1) || (pair2_rank == -1) || (kick1_rank == -1)));
    		r--) {
    	if (pair1_rank == -1 && rank_histogram[r] == 2) {
    		pair1_rank = r;
    	} else if (pair2_rank == -1 && rank_histogram[r] == 2) {
    		pair2_rank = r;
    	} else if ((kick1_rank == -1) && ((rank_histogram[r] == 1) || (rank_histogram[r] == 2))) {
    		kick1_rank = r;
    	} else {
    		//do nothing
    	}
    }
    if (pair1_rank != -1 && pair2_rank != -1 && kick1_rank != -1) {
    	_score = Hand::TWO_PAIR_BASE_SCORE + pair1_rank * Ranks::num_ranks * Ranks::num_ranks +
    			pair2_rank * Ranks::num_ranks + kick1_rank;
    	return true;
    }
	return false;
}

bool Hand::one_pair() {
	auto pair_rank = -1;
	auto kick1_rank = -1;
	auto kick2_rank = -1;
	auto kick3_rank = -1;

	for (auto r = Ranks::num_ranks -1;
			((r >= 0) && ((pair_rank == -1) || (kick1_rank == -1) || (kick2_rank == -1) || (kick3_rank == -1)));
			r--) {
		if (pair_rank == -1 && rank_histogram[r] == 2) {
			pair_rank = r;
		} else if (kick1_rank == -1 && rank_histogram[r] == 1) {
			kick1_rank = r;
		} else if (kick2_rank == -1 && rank_histogram[r] == 1) {
			kick2_rank = r;
		} else if (kick3_rank == -1 && rank_histogram[r] == 1) {
			kick3_rank = r;
		} else {
			// do nothing
		}
	}
	if ((pair_rank != -1) && (kick1_rank != -1) && (kick2_rank != -1) && (kick3_rank != -1)) {
		_score = Hand::ONE_PAIR_BASE_SCORE +
				pair_rank * Ranks::num_ranks * Ranks::num_ranks * Ranks::num_ranks +
				kick1_rank * Ranks::num_ranks * Ranks::num_ranks +
				kick2_rank *  Ranks::num_ranks +
				kick3_rank;
		return true;
	}
	return false;
}

bool Hand::high_card() {
	auto counted = 0;
	long int temp_score = 0;

	for (auto r = Ranks::num_ranks -1; ((r >= 0) && (counted < 5)); r--) {
		if (rank_histogram[r] == 1) {
			counted ++;
			temp_score += (1 << r);
		}
	}
    _score = temp_score;
	return true;
}
