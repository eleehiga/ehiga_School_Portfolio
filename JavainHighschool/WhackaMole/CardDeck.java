
/**
 * CardDeck represents a single deck of 52 Cards
 * 
 * @author Lisa Miyamoto 
 * @version (a version number or a date)
 */

public class CardDeck
{
	private Card [] deck;
	private int numUnusedCards;
	private int numDecks;
	
	/**
	 * Construct a deck of 52 cards with Aces given a cardRank > Kings
	 */
	public CardDeck ()
	{   
	    this(1,true);
	}
	
	/**
	 * Construct numDecks number of decks of 52 cards.  If aceHigh is true, Aces will be given a cardRank of 14 (higher than Kings 13) otherwise their cardRank will be 1. 
	 *   @param  numDecks   the number of 52 card decks you want included in this deck
	 *   @param  aceHigh    set to true for Aces valued higher than Kings or false to set them less than a 2
	 */
	public CardDeck (int numDecks, boolean aceHigh)
	{   
	  this.numDecks=numDecks;
	  deck = new Card[52*numDecks];
	  numUnusedCards = deck.length;
	  String cardSuit="";
	  for(int n=0; n< numDecks; n++)
	    for (int suit=0; suit <4; suit ++)
	    { 
	        switch(suit)
	        {
	          case 1: cardSuit = "Hearts"; break;
	          case 2: cardSuit = "Clubs"; break;
	          case 3: cardSuit = "Diamonds"; break;
	          case 0: cardSuit = "Spades"; break;
	        }
	      
	        for (int card=1; card <=13; card++)
	        {
	          switch(card)
	          {
	              case  1: if(aceHigh)
	                         deck[52*n+(13*suit+card-1)] = new Card (14, cardSuit);
	                       else
	                         deck[52*n+(13*suit+card-1)] = new Card (1, cardSuit); 
	                       break;
	              default: deck[52*n+(13*suit+card-1)] = new Card (card, cardSuit); 
	                       break;
	          }
	        }
	    }
	}
	
	/**
	 * uses System.out to display all the cards in the deck
	 */
	public void showAllCardsSystemOut()
	{
	    for (int i=0; i<deck.length; i++)
	      System.out.println(i+"--"+deck[i].toString() + " "+deck[i].getCardFace()+" "+deck[i].getFaceValue()+" "+deck[i].getCardRank()+" "+deck[i].getColor()+" "+deck[i].wasDealt());
	}
	
	/**
	 * uses TextWriter to display all the cards in the deck graphically
	 */
	public void showAllCardsGraphically()
	{
	    for(int d=0; d<numDecks; d++)
	      for(int i=0+52*d; i<deck.length;i++)
	      {
	          deck[i].changeXY(i%13*25+10,i%4*20+10+80*d);
	          deck[i].makeVisible();
	      }

	}
	
	/**
	 * resets all the Cards in the deck to a status of NOT yet used/dealt
	 */
	public void shuffle()
	{
	    for (int i=0; i<deck.length; i++)
	      deck[i].setNotUsed();
	    numUnusedCards=deck.length;
	}
	
	/**
	 * returns how many cards have not yet been dealt/used
	 */
	public int getNumUnusedCards()
	{
	    return numUnusedCards;
	}
	
	/**
	 * randomly return a Card from the deck that has not yet been dealt/used
	 */
	public Card deal()
	{
	    double randomDecimal;
	    int randomNum=0;
	    
	    if(numUnusedCards==0)
	      return null;
	    else
	    {
	        do
	        {randomNum=(int)Math.floor(Math.random()*deck.length);
	        }while(randomNum>=0 && randomNum<=51 && deck[randomNum].wasDealt());
	        
	        deck[randomNum].setUsed();
	        numUnusedCards--;
	        return deck[randomNum];
	    }
	}
	
}
