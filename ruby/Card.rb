class Card
  attr :suit, :rank, :val
  @@NUM_RANKS = 13
  @@NUM_SUITS = 4
  @@RANK_ACE  = 12
  @@RANK_DEUCE = 0
  @@RANK_SIX  = 4
  @@RANK_FIVE = 3
  @@RANK_FOUR  = 2
  @@RANK_THREE = 1
  
  def initialize (_val)
    @val = _val
    @suit = _val % @@NUM_SUITS
    @rank = _val / @@NUM_SUITS
  end
  
  def Card.rank_ace
    @@RANK_ACE
  end

  def Card.rank_deuce
    @@RANK_DEUCE
  end
  
  def Card.rank_six
    @@RANK_SIX
  end
  
  def Card.rank_five
    @@RANK_FIVE
  end

  def Card.rank_four
    @@RANK_FOUR
  end

  def Card.rank_three
    @@RANK_THREE
  end

  def Card.num_ranks
    @@NUM_RANKS
  end
  
  def Card.num_suits
    @@NUM_SUITS
  end
def to_s
    case @rank
    when 12
      s = :A.to_s
    when 11
      s = :K.to_s
    when 10
      s = :Q.to_s
    when 9
      s = :J.to_s
    when 8
      s = :T.to_s
    else
      s = (@rank+2).to_s         
    end
    case @suit
    when 0
      s<< :' of Clubs'.to_s
    when 1
      s<< :' of Diamonds'.to_s
    when 2
      s<< :' of Hearts'.to_s
    when 3
      s<< :' of Spades'.to_s
    end
  end
end
# test
#0.upto(51){|x| puts Card.new(x)}