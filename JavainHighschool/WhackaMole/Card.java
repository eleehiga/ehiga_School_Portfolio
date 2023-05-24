
/**
 * Write a description of class Card here.
 * 
 * @author Lisa Miyamoto
 * @version (a version number or a date)
 */
public class Card extends TextObj
{
    private final char HEART   = '\u2665';
    private final char DIAMOND = '\u2666';
    private final char CLUB    = '\u2663';
    private final char SPADE   = '\u2660';
    
    private String suit;
    private char suitSymbol;   
    //private String cardColor;
    private String face;
    private int faceValue;
    private int cardRank;
    private boolean dealt;

    public static void main(String[]args)
    {
        Card [] hand = new Card[7];
        hand[0] = new Card(14, "Hearts");
        hand[1] = new Card(9, "Diamonds");
        hand[2] = new Card(13, "Spades");
        hand[3] = new Card(9, "Hearts");
        hand[4] = new Card(3, "Clubs");
        hand[5] = new Card(5, "Hearts");
        hand[6] = new Card(10, "Hearts");
        Card.sort(hand);
    }
    /**
     * The default construtor creates a blue Joker
     */
    public Card()
    {
        suit = "JOKER";
        suitSymbol = '?';
        face = "Joker";
        faceValue = 0;
        cardRank = 0;
        dealt = false;
        color = "blue";
        text = getCardFace();
        changeXY(0,30);
    }
    
    /**
     * Constructs a specific card given the cardRank and suit
     * @param   cardRank  values 2-13 represent cards 2-10, Jack, Queen and King respectively,
     *                           1 or 14 for Aces depending on whether you want them weighted high or low
     * @param   cardSuit  valid suits are "Hearts","Diamonds","Spades" or "Clubs"
     */
    public Card (int cardRank, String cardSuit)
    {
        suit=cardSuit;
        if(suit.equals("Hearts"))
        {  suitSymbol = HEART; color = "red";}
        else if(suit.equals("Diamonds"))
        {  suitSymbol = DIAMOND; color = "red";}
        else if(suit.equals("Clubs"))
        {  suitSymbol = CLUB; color = "black";}
        else if(suit.equals("Spades"))
        {  suitSymbol = SPADE; color = "black";}
        faceValue = cardRank;
        this.cardRank = cardRank;
        if(cardRank >= 2 && cardRank <= 10)
            face = Integer.toString(cardRank);
        else switch(cardRank)
             {
                 case 14: faceValue = 1; 
                 case  1: face = "A"; 
                          break;
                 case 11: face = "J"; faceValue = 10; break;
                 case 12: face = "Q"; faceValue = 10; break;
                 case 13: face = "K"; faceValue = 10; break;
                 default: suit = "JOKER";
                          suitSymbol = '?';
                          face = "Joker";
                          faceValue = 0;
                          cardRank = 0;
                          dealt = false;
                          color = "blue";
             }
          text = getCardFace();
          changeXY(0,30);
    }

    /**
     * returns a character representing the card's suit (a heart, spade, diamond or club)
     */
    public char getSuitSymbol()
    {
        return suitSymbol;
    }
    
    /**
     * returns a string that spells out the suit of the card ("Hearts", "Spades", "Diamonds" or "Clubs")
     */
    public String getSuitName()
    {
        return suit;
    }

    
    /**
     * returns a string containing the card's suit symbol and face (a heart followed by an A is the Ace of Hearts)
     */
    public String getCardFace()
    {
        return suitSymbol+face;
    }
    
    /**
     * returns a string representing the face of the card ("J", "A", "3" for a Jack, Ace or 3)
     */
    public String getCardType()
    {
        return face;
    }
    
    /**
     * returns an integer representing the value of the card (1-10 for Aces-10, 10 for J,Q,and K)
     */
    public int getFaceValue()
    {
        return faceValue;
    }
    
    /**
     * returns an integer representing the value of the card (1-13 or 2-14)
     *   i.e. cards 2..10,J,Q,K returns 2..10,11,12,13 respectively;
     *        Aces return a 1 or 14 depending on how the card was constructed
     */
    public int getCardRank()
    {
        return cardRank;
    }
    
    /**
     * When the method used is called, it will flag the card as having been dealt
     */
    public void setUsed()
    {
        dealt = true;
    }
    
    /**
     * When the method unUsed is called, it will flag the card as having been NOT dealt
     */
    public void setNotUsed()
    {
        dealt = false;
    }

    /**
     * returns a true if the card was marked as having been used/dealt otherwise false
     */
    public boolean wasDealt()
    {
        return dealt;
    }
    
    /**
     * converts the card to a text string such as "J of Hearts" or "10 of Clubs"
     */
    public String toString()
    {
        return face + " of " + suit;
    }
    
    /**
     * compares whether two cards are the same suit and face
     */
    public boolean equals(Card c)
    {
        return suit.equals(c.suit) && face.equals(c.face);
    }
    
    public static void sort (Card [] cards)
    {
        int i,j;
        Card temp;

        System.out.print("Array of cards BEFORE sorting:  ");  
        for(i=0; i<cards.length; i++)
          System.out.print("Card [" + i + "] - " + cards[i] + "\t");
        System.out.println();
        
        for(i=cards.length-1; i>0; i--)
          for(j=0; j<i; j++)
          {
              
              if(cards[j].getCardRank() > cards[j+1].getCardRank())
              {
                  temp = cards[j];
                  cards[j] = cards[j+1];
                     //cards[j].changeXY(LEFTMARGIN + j*50 ,350 );  // change its xy coordinates for proper placement on the screen
                  cards[j+1] = temp;
                     //cards[j+1].changeXY(LEFTMARGIN + (j+1)*50 ,350 );  // change its xy coordinates for proper placement on the screen
              }
          }

        System.out.print("Array of cards AFTER sorting:  ");  
        for(i=0; i<cards.length; i++)
          System.out.print("Card [" + i + "] - " + cards[i] + "\t");
        System.out.println();
    }
    
}
