/*
 * Card.h
 *
 *  Created on: Oct 11, 2019
 *      Author: root
 */

#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

namespace Suits
{
  enum Suit { clubs, diamonds, hearts, spades };

  static const Suit All[] = {clubs, diamonds, hearts, spades };

  static const std::string s[] = {"clubs", "diamonds", "hearts", "spades" };

  const int num_suits = 4;
}
//std::ostream& operator<<(std::ostream& os,  Suits::Suit& suit);

namespace Ranks
{
  enum Rank {deuce, three, four, five, six,
                 seven, eight, nine, ten,
				 jack, queen, king, ace};

  static const Rank All[] = {deuce, three, four, five, six,
      seven, eight, nine, ten,
		 jack, queen, king, ace};

  static std::string s[] = {"deuce", "three", "four", "five", "six",
      "seven", "eight", "nine", "ten",
		 "jack", "queen", "king", "ace"};

  static unordered_map<char, Ranks::Rank> char_to_rank =
  {
  	  {'A', Ranks::ace}, {'K', Ranks::king}, {'Q', Ranks::queen},
	  {'J', Ranks::jack}, {'T', Ranks::ten}, {'9', Ranks::nine},
	  {'8', Ranks::eight}, {'7', Ranks::seven}, {'6', Ranks::six},
	  {'5', Ranks::five}, {'4', Ranks::four}, {'3', Ranks::three}, {'2', Ranks::deuce}
  };

  const int num_ranks = 13;
}

//std::ostream& operator<<(std::ostream& os,  Ranks::Rank& rank);

class Card {
public:
	Card(Ranks::Rank rank, Suits::Suit suit);
	~Card();
	Suits::Suit const suit() {return _suit;}
	Ranks::Rank const rank() {return _rank;}

	bool operator==(const Card& y) {return _rank == y._rank && _suit == y._suit; }
	bool operator<(const Card& y) {return _rank < y._rank;}
    std::string to_string();

private:
	Ranks::Rank _rank;
	Suits::Suit _suit;

};

std::ostream& operator<<(std::ostream& os,  Card& card);

#endif /* CARD_H_ */
