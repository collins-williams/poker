/*
 * Player.h
 *
 *  Created on: Oct 30, 2019
 *      Author: root
 */



#ifndef PLAYER_H_
#define PLAYER_H_

#include "Card.h"

namespace Positions
{
    static const int POSITION_SMALL_BLIND = 0;
}


class Player {
public:
	Player(int position);
	~Player();

private:
	Card& hole_cards[2];

};

#endif /* PLAYER_H_ */
