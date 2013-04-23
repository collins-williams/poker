require "Card.rb"
class Deck
  @@SIZE = 51
  def initialize
    @cards = []
    0.upto(@@SIZE) { |x|
      @cards << Card.new(x)
    }
  end
  
  # take a list of cards as the starting position
  #TODO test
  def stack(_anArray)
    @cards = Array.new + _anArray
  end
  
  def shuffle
#    puts "shuffling"
    new_deck = []
    while @cards.size > 0 do
      new_deck << @cards.delete_at(rand(@cards.size))
       # puts "moving #{new_deck.last} @cards.size"
    end
#    puts "done shuffling"
    @cards = new_deck
#    0.upto(@@SIZE) {|source|
#      destination = rand(@@SIZE+1)
#      t = @cards[source]
#      @cards[source] = @cards[destination]
#      @cards[destination] = t
#    }
  end
  
  def deal(num_cards)
    # return array containing num cards from deck
    return @cards.slice!(0,num_cards)
  end
  
  def dump
    puts "#{@cards.size} cards"
    @cards.each{|aCard|
       puts aCard 
    }
  end
  
  def test_shuffle
    histogram = Array.new(@@SIZE+1, Array.new(@@SIZE+1,0))
    ((@@SIZE+1)*1000).times() {
      d = Deck.new()
      d.shuffle
      0.upto(@@size) { |x|
        histogram[@cards[x].val][x] += 1
      }
    }
    0.upto(@@SIZE) {|x|
      
    }
  end
  
end

# test
#d = Deck.new()
#puts "dumping new deck"
#d.dump
#d.shuffle
#puts "dumping shuffled deck"
#d.dump
#puts "testing deal"
#d=Deck.new()
#puts d.deal(1)
#puts d.deal(2)