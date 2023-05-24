import java.awt.event.*;
import javax.swing.*;
/**
 * Write a description of class CardGame here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class KBMouseSample extends GameClass   //implements KeyListener , MouseListener
{
    // sample data members for KBMouseGame
    private final int NUMROWS = 6;
    private final int NUMCOLS = 6;
    private final int COLWIDTH = 30;
    private final int TOPMARGIN = 100;
    private final int LEFTMARGIN = 50;
    private Figure[] vLines;
    private Figure[] hLines;
    private Figure[][] board;
    private int tRow,tCol;      // keeps track of what row and column the triangle is in
    
    private Card [] hand;
    private CardDeck deck;
    
    private Circle startCircle;
    
    private TextObj text1;
    private GifImage myPic = new GifImage("ugly.gif");
    

    public KBMouseSample()
    {
    }
    
    public void setupBoard()
    {
        // build the board based on numRows and numCols specifications
        board = new Figure[NUMROWS][NUMCOLS];
        // initialize every element on the board to refer to a null value
        for(int r=0; r < NUMROWS; r++)
          for(int c=0; c < NUMCOLS; c++)
            board[r][c] = null;
        
        vLines = new Box[NUMCOLS+1];
        hLines = new Box[NUMROWS+1];
        
        for(int c=0; c <= NUMCOLS; c++)
        {
            vLines[c] = new Box(NUMROWS*COLWIDTH,3,c*COLWIDTH+LEFTMARGIN,TOPMARGIN);
            vLines[c].makeVisible();
        }
        
        for(int r=0; r <= NUMROWS; r++)
        {
            hLines[r] = new Box(3,NUMCOLS*COLWIDTH,LEFTMARGIN,TOPMARGIN+r*COLWIDTH);
            hLines[r].makeVisible();
        }        
        // set up triangle in (0,0)
        tRow=0;
        tCol=0;
        if(board[tRow][tCol] != null)
          board[tRow][tCol].makeInvisible();
       
        board[tRow][tCol] = new Triangle();
        board[tRow][tCol].changeXY(tRow*COLWIDTH + LEFTMARGIN,tCol*COLWIDTH + TOPMARGIN);   // set (x,y) to have triangle display in correct position on screen
        board[tRow][tCol].makeVisible(); 
     }       
     
     public void setupHand()
     {
       deck = new CardDeck();  // construct a single 52-card deck were aces are high
       hand = new Card[5];     // declare hand to be an array capable of referring to 5 cards
        
       // initialize each element in the array to be null (not referring to a card)
       for (int card = 0; card < hand.length; card++)
          hand[card] = null;
               
        deal();
        showHand(hand);
      }
      
      public void setupCircleAndText()
      {
       startCircle = new Circle();
       startCircle.changeXY(0,0);   //place the circle in the upper left hand corner
       startCircle.changeSize(30,30);
       startCircle.makeVisible();

       text1 = new TextObj("Click on Circle to move Triangle, hit s to sort cards, hit ESC to quit game", 50,30);
       text1.makeVisible();
       }
       
       public void setupImage()
       {
        // draw ugly picture
         myPic.changeXY(430,150);
         myPic.makeVisible();
         JOptionPane.showMessageDialog(null,"Oops, need to resize this ugly picture");
         myPic.changeSize(100,100);
        } 
    
    public static void main(String [] args)
    {
        KBMouseSample mygame = new KBMouseSample();
        canvas = Canvas.getCanvas();
        canvas.setListeners(mygame);  // enables keyboard and mouse input

        mygame.start();
       
        canvas.stopListeners(mygame);  // stops keyboard and mouse input before ending the game
    }
    
    public void start()
    {
        setupBoard();
        setupHand();
        setupCircleAndText();
        setupImage();
       
        do
        {
            // Handling mouse input
            if (mouseAlreadyClicked)
            {
                System.out.println("Method start() received mouse input with coordinates ( " + mouseX + " , " + mouseY + " )");

                // Figure out what areas on your display these coordinates fall into and call the  appropriate methods to handle the selection        
                if (mouseX <=30 && mouseY <= 30 )
                {
                    moveTriangle();
                }
                
                mouseAlreadyClicked = false;
            }
            
            // Handling keyboard input
            // 48-57  -->  0-9
            // 65-90  -->  a-z
            // 38     -->  up    Arrow
            // 40     -->  down  Arrow
            // 37     -->  left  Arrow
            // 39     -->  right Arrow
            if (key != -1)
            {
                System.out.println("Method start() received Keyboard input with the value " + key );
                switch (key)
                {
                    case 27:                      // end game if user hits ESC
                    case 81:    endOfGame = true; // end game if user hits a q
                                break;
                    case 83:    hideHand(hand);
                                Card.sort(hand);
                                updateCardXYCoord(hand);
                                showHand(hand);
                                break;
                    default:    // ignore the key
                }
                
                key = -1;   // reset key value back to -1 to wait for next input
            }
            
        }while(!endOfGame);     // user needs to hit the ESC key to end the game
        System.out.println("ESC key was pressed to end the game");
    }
    
    public void moveTriangle()
    {
              
        Dice d = new Dice(NUMROWS);
        int row = d.roll();  // randomly pick row and column coordinates
            row = row - 1;   // adjust to rows and columns starting from 0 instead of 1
        int col = d.roll();
            col = col - 1;
            
       // make current triangle invisible then place new triangle in (row,col)
        if(board[tRow][tCol] != null)
          board[tRow][tCol].makeInvisible();
       
        // update the coordinates of the triangle to the new (row,col) coordinates, and draw it
        tRow = row;
        tCol = col;
        board[tRow][tCol] = new Triangle();
        board[tRow][tCol].changeXY(tRow*COLWIDTH + LEFTMARGIN,tCol*COLWIDTH + TOPMARGIN);   // set (x,y) to have triangle display in correct position on screen
        board[tRow][tCol].makeVisible();
    }
    
    public void deal()
    {
        // assign each element in array hand to refer to a card randomly dealt from deck
        for(int card=0; card < hand.length; card++)
        {
          hand[card] = deck.deal();         // method deal( ) returns a Card 
          hand[card].changeXY(LEFTMARGIN + card*50 ,350 );  // change its xy coordinates for proper placement on the screen
        }
    }
    
    public void showHand(Card [] cardArray)
    {

        // display all the cards in the array hand on the canvas
        for(int card=0; card < cardArray.length; card++)
        {
            if ( cardArray[card] != null )  // ensure that it refers to a valid Card
            {
                 cardArray[card].makeInvisible();
                 cardArray[card].makeVisible();                 // then make it visible
            }
        }
    }
    
    public void hideHand(Card [] cardArray)
    {

        // display all the cards in the array hand on the canvas
        for(int card=0; card < cardArray.length; card++)
        {
            if ( cardArray[card] != null )  // ensure that it refers to a valid Card
            {
                 cardArray[card].makeInvisible();
            }
        }
    }
    
    public void updateCardXYCoord(Card [] cards)
    {   
        for (int j=0; j<cards.length; j++)
           cards[j].changeXY(LEFTMARGIN + j*50 ,350 );  // change its xy coordinates for proper placement on the screen
    }
}
