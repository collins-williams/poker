require "Hand.rb"
require "Deck.rb"
require "Card.rb"
#this class represents one deal of Hold'em
# it does not reflect betting at all just the cards and number of players
# it is to be used as a structure for simulating outcomes...
class Player
  attr_reader :hand, :name
  def initialize(_name)
    @name = _name
    @hole_cards = Array.new
    @folded = false
  end
  
  def add_hole_card(aCard)
    @hole_cards << aCard
  end
  
  def form_hand(*_cards)
    @hand = Hand.new
    @hole_cards.each() {|card| @hand.add_card(card) if card}
    _cards.flatten.each {|card| @hand.add_card(card) if card}
  end
  
  def to_s
    "#{@name}  #{@hole_cards[0]} #{@hole_cards[1]}\n"
  end
end

class Deal
  @@FLOP_SIZE = 3
  def initialize(_num_players)
    @num_players = _num_players
    @players = Array.new
    @flop    = Array.new()
    @turn = nil
    @river = nil
    @deck = Deck.new
    @deck.shuffle()
    0.upto(@num_players - 1) { |num|
      @players << Player.new("player #{num}")
    }
  end
  
  def deal_hole_cards
    @players.each() {|a_player| 
      @deck.deal(2).each{|card| a_player.add_hole_card(card)} 
    }
  end
  
  def deal_flop
    @flop = @deck.deal(@@FLOP_SIZE)
  end
  
  def deal_turn
    @turn = @deck.deal(1)[0]
  end
  
  def deal_river
    @river = @deck.deal(1)[0]
  end
  
  def to_s
    ret = String.new
    @players.each() { |a_player|
      ret << a_player.to_s
    }
    ret << "*** FLOP ***\n"
    ret << @flop.to_s if @flop.size() != 0
    ret << "\nturn #{@turn}" if @turn
    ret << "\nriver #{@river}" if @river
  end
  
  def rank_hands
    @players.each{|player| player.form_hand(@flop, @turn, @river)}
    @players.sort!{|p1, p2| p1.hand.score <=> p2.hand.score}
    @players.each{|player| 
      puts " #{player.name} #{player.hand} #{player.hand.evaluate} #{player.hand.score}"
    }
  end
  
  #there are 13 pairs of hole cards and (13*12)/2 unpaired holdings * 2 for 
  # suited and unsuited
  # call them A, K, Q, ... to represent the pairs
  # XY X>Y for a suited combination
  # XYu X>Y for an unsuited combination
end


deal = Deal.new(9)
deal.deal_hole_cards()
puts "pre flop: #{deal}"
deal.deal_flop()
puts "\n post flop:\n #{deal}"
deal.deal_turn()
deal.deal_river()
puts "\n full deal:\n #{deal}"
deal.rank_hands()

