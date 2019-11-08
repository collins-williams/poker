require "Card.rb"
require "Deck.rb"

#TODO Eliminate magic numbers by using Card.xxx and the like

# a hand is a collection of cards.  It keeps some additional state to make 
# evaluation easier.

class Hand
  @@STRAIGHT_FLUSH_BASE = 1000000
  @@FOUR_OF_A_KIND_BASE =  900000
  @@FULL_HOUSE_BASE     =  800000
  @@FLUSH_BASE          =  700000
  @@STRAIGHT_BASE       =  600000
  @@THREE_OF_A_KIND_BASE = 500000
  @@TWO_PAIR_BASE        = 400000
  @@ONE_PAIR_BASE       =  100000
  
  @@HAND_SIZE           = 5 # 5 cards required to evaluate
  @@STRAIGHT_LENGTH     = 5
  @@FLUSH_SIZE          = 5
  
  def initialize()
# cards is a sorted array of objects of class Card.  It is updated every time
# a card is added
    @cards = Array.new()  
    @evaluation = String.new()
    @rank_histogram = Array.new(Card.num_ranks,0)
    @suit_histogram = Array.new(Card.num_suits,0)
    @score = 0
    @evaluated_size = 0
  end
 

# add_card is used to update the hand.  It updates the histograms and card elements
# the evaluation if the hand contains enough cards (5)   
def add_card(aCard)
    @cards << aCard
    @cards.sort!() {|card1, card2| card1.rank <=> card2.rank}
    @rank_histogram[aCard.rank] += 1
    @suit_histogram[aCard.suit] += 1
    @evaluation = nil
    @score      = 0
end
  
  def to_s
    @cards.to_s + "\n" #+ @evaluation
  end
  
  def evaluate
    #evaluate if we have not evaluate before and there are enough cards OR
    # if we have more cards than the last time we evaluated
    if ((@evaluation.nil? && @cards.size() >= @@HAND_SIZE) ||
        (@evaluated_size < @cards.size()))
      @evaluated_size = @cards.size()
      @evaluation = evaluation_string
    end  
    return @evaluation
  end
  
  def score
    if @score == 0
      evaluate     
    end
    @score
  end
  
  def evaluation_string
    if straight_flush
      return "straight flush"
    elsif four_of_a_kind
      return "four of a kind"
    elsif full_house
      return "full house"
    elsif flush
      return "flush"
    elsif straight
      return "straight"
     elsif three_of_a_kind
       return "3 of a kind"
    elsif two_pair
      return "two pair"
    elsif one_pair
      return "one pair"
    elsif high_card
      return "high card" 
    else
      return "oops #{self}"
    end
  end
  
  def holds?(rank,suit) 
    @cards.each() {|card|
      return true if card.rank == rank && card.suit == suit
    }
    return false
  end
  
  def update_score(aScore)
    @score = aScore if aScore > @score
  end
  
  
  def straight_flush 
    # something like for each card with 4 or more cards above it
    # check to see if the cards above it are sequential and same suit
    0.upto(@cards.size()-@@STRAIGHT_LENGTH) {|low_card|
      ok = true
      step = 1
      start_card = @cards[low_card]
      while (ok && step < @@STRAIGHT_LENGTH)
        if (holds?(start_card.rank + step, start_card.suit) or
            ((start_card.rank == Card.rank_deuce) and 
             (step == (@@STRAIGHT_LENGTH-1)) and
             (holds?(Card.rank_ace, start_card.suit))))
          step += 1
        else
          ok = false
        end
      end
      if ok == true
        new_score = @@STRAIGHT_FLUSH_BASE + start_card.rank + 
          (@@STRAIGHT_LENGTH-1)
        update_score(new_score)
        return true
      end
    }
    return false
  end
  
  def flush
    0.upto(3) {|suit| 
       if @suit_histogram[suit] >= @@FLUSH_SIZE
         @score = @@FLUSH_BASE
         _counted = 0
         Card.rank_ace.downto(Card.rank_deuce) {|rank|
           if (holds?(rank,suit) && _counted < @@FLUSH_SIZE)
             _counted += 1
             @score +=  (1 << rank)
           end
         }
         return true
       end
    }
    return false
  end
  
  def straight
    Card.rank_ace.downto(Card.rank_six) {|start_rank|
      ok = true
      rank2 = start_rank
      while ((ok) && rank2 > start_rank - @@STRAIGHT_LENGTH)
        ok =  (@rank_histogram[rank2] != 0)
        rank2 -= 1
      end
      if ok
        @score = @@STRAIGHT_BASE + start_rank
        return true
      end
    }
    #check for wheel
    if ((@rank_histogram[Card.rank_ace] != 0)   &&
        (@rank_histogram[Card.rank_deuce] != 0) &&
        (@rank_histogram[Card.rank_three] != 0) &&
        (@rank_histogram[Card.rank_four] != 0)  &&
        (@rank_histogram[Card.rank_five] != 0))
          @score = @@STRAIGHT_BASE + Card.rank_five
          return true
    end
    return false
  end
  
  def four_of_a_kind
    _four_rank = -1
    _kicker    = -1
    Card.rank_ace().downto(Card.rank_deuce()) { |rank|
      if ((@rank_histogram[rank] == 4) && (_four_rank == -1))
        _four_rank = rank
      elsif ((@rank_histogram[rank] > 0 && (_kicker == -1)))
        _kicker = rank
      else  
      end
    }
    if ((_four_rank != -1) && (_kicker != -1)) 
      @score = @@FOUR_OF_A_KIND_BASE + (_four_rank * Card.num_ranks) + _kicker
      return true
    end
    return false
  end
 
  def full_house
    three_rank = -1
    two_rank   = -1
    Card.rank_ace().downto(Card.rank_deuce()) {|rank|
      if @rank_histogram[rank] == 3 && three_rank == -1
        three_rank = rank
      elsif @rank_histogram[rank] >= 2 && two_rank == -1
        two_rank = rank
      else
      end
    }
    if three_rank != -1 && two_rank != -1
      @score = @@FULL_HOUSE_BASE + three_rank * Card.num_ranks + two_rank 
      return true
    end
    return false

  end
  
  
  def three_of_a_kind
    three_rank = -1
    kick1 = -1
    kick2 = -1
    Card.rank_ace().downto(Card.rank_deuce()) {|rank|
      if ((@rank_histogram[rank] == 3) && (three_rank == -1))
        three_rank = rank
      elsif ((@rank_histogram[rank] == 1) && (kick1 == -1))
        kick1 = rank
      elsif ((@rank_histogram[rank] == 1) && (kick2 == -1))
        kick2 = rank
      else
      end
    }
    if ((three_rank != -1) && (kick1 != -1) && (kick2 != -1))
      @score = @@THREE_OF_A_KIND_BASE + 
                 three_rank * Card.num_ranks * Card.num_ranks +
                + kick1 * Card.num_ranks + kick2
      return true
    end
    return false
  end
  

  def two_pair
    pair_1_rank = -1
    pair_2_rank = -1
    kick_1 = -1
    Card.rank_ace().downto(Card.rank_deuce()) {|rank|
      if @rank_histogram[rank] == 2 && pair_1_rank == -1
        pair_1_rank = rank
      elsif @rank_histogram[rank] == 2 && pair_2_rank == -1
        pair_2_rank = rank
      elsif @rank_histogram[rank] == 1 && kick_1 == -1
        kick_1 = rank
      else
      end
    }
   if pair_1_rank != -1 && pair_2_rank != -1 && kick_1 != -1
     @score = @@TWO_PAIR_BASE + 
                  pair_1_rank * Card.num_ranks * Card.num_ranks + 
                  pair_2_rank * Card.num_ranks + kick_1
     return true
   end
   return false
  end
  
  
  def one_pair
    pair_1_rank = -1
    kick_1 = -1
    kick_2 = -1
    kick_3 = -1
    Card.rank_ace().downto(Card.rank_deuce()) {|rank|
      if @rank_histogram[rank] == 2 && pair_1_rank == -1
      pair_1_rank = rank
      elsif @rank_histogram[rank] == 1 && kick_1 == -1
      kick_1 = rank
      elsif @rank_histogram[rank] == 1 && kick_2 == -1
      kick_2 = rank
      elsif @rank_histogram[rank] == 1 && kick_3 == -1
      kick_3 = rank
      else
      end
    }
    if pair_1_rank != -1 && kick_1 != -1 && kick_2 != -1 && kick_3 != -1
      @score = @@ONE_PAIR_BASE +
                 pair_1_rank * Card.num_ranks * Card.num_ranks * Card.num_ranks +
                 kick_1 * Card.num_ranks * Card.num_ranks +
                 kick_2 * Card.num_ranks +
                 kick_3
      return true
    end
    return false
  end

 
  def high_card
    _counted = 0
    _score = 0
    Card.rank_ace.downto(Card.rank_deuce) {|rank|
           if ((@rank_histogram[rank] == 1) && (_counted < 5))
             _counted += 1
             _score +=  (1 << rank)
           end
         }

    @score = _score
    return true
  end
  
end
# test
#h = Hand.new()
#0.upto(6) {|i|
#  h.add_card(Card.new(i*4))
#}
#puts "#{h} #{h.evaluate()}"
#
#h = Hand.new()
#0.upto(3) {|i|
#  h.add_card(Card.new(i*4))
#}
#
#h.add_card(Card.new(48))
#puts "#{h} #{h.evaluate()} #{h.score}"


#found = false
#count = 0
#while (found == false)
#  h = Hand.new()
#  d = Deck.new()
#  d.shuffle()
#  d.deal(7).each {|card| h.add_card(card)}
##  0.upto(4) {h.add_card(Card.new(rand(52)))}
#  puts "#{count} #{h} #{h.evaluate} #{h.score}"
#  count += 1
#  found = h.evaluate == "straight flush"
#end
#hands = Array.new()
#0.upto(100) {
#  h = Hand.new()
#  d = Deck.new()
#  d.shuffle()
#  d.deal(7).each {|card|
#    h.add_card(card)
#  }
#  h.evaluate()
#  hands << h
#}
#hands.sort!() {|hand1, hand2| hand1.score <=> hand2.score}
#hands.each() {|aHand| 
#  puts " #{aHand} #{aHand.evaluate} #{aHand.score}"
#}


#hands = Hash.new
#sample_size = 10000
#0.upto(sample_size-1) {
#  h = Hand.new()
#  d = Deck.new()
#  d.shuffle()
#  d.deal(7).each {|card|
#    h.add_card(card)
#  }
#  h.evaluate
#  if (hands[h.score].nil?)
#    hands[h.score] = Array.new
#  end
#  hands[h.score] << h
#}
#
#total = 0
#hands.sort.each { |anArray|
#  puts "*************************\n"
#  puts "hands scoring #{anArray[0]} there are #{anArray[1].size} \n"
#  anArray[1].each {|hand|
#    puts "--> #{hand.evaluate} #{hand}"
#  }
#  total += anArray[1].size
#}
#puts "#{total}  #{sample_size}"