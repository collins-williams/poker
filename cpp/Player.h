/*
 * Player.h
 *
 *  Created on: Oct 30, 2019
 *      Author: root
 */

// general notes on the classes that are more complicated than Hand
// a player is part of a deal
// a player contains
//   a _position_
//   hole cards
//   a _range_
//   maybe a _strategy_ that contains a set of ranges based on position
//   some method for indicating the hole cards meet the range
//
//
//  position indicates how early the player must act.  It is used (right now) for selecting
//     between ranges (all contained in the strategy?)
//
//  a range is a set of _rules_
//    only hands that meet one of the rules will be included in a simulation
//

//
//
//
//
//
//     the higher card is listed first, a range specifier of +
//     when applied to a non pair means iterate the second card higher
//     until it become 1 less than the first card
//
//
//
// a deal contains x players each with hole cards
//   and a turn and a river card
//   it is not a holder for betting
//   there must be a way to describe a deal with text file or files that
//   describe the players their positions and strategies
//  (may be the players are in distinct files)

#ifndef PLAYER_H_
#define PLAYER_H_

namespace Positions
{
}
	static const int POSITION_SMALL_BLIND = 0;

	static const long int FOUR_OF_A_KIND_BASE_SCORE =  900000;
	static const long int FULL_HOUSE_BASE_SCORE     =  800000;
	static const long int FLUSH_BASE_SCORE          =  700000;
	static const long int STRAIGHT_BASE_SCORE       =  600000;
	static const long int THREE_OF_A_KIND_BASE_SCORE =  500000;
	static const long int TWO_PAIR_BASE_SCORE       =  400000;
	static const long int ONE_PAIR_BASE_SCORE       =  100000;
	static const long int HIGH_CARD_BASE_SCORE       = 1;

class Player {
public:
	Player();
	~Player();
};

#endif /* PLAYER_H_ */
