
/**
 * Write a description of class Game here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.awt.event.*;
import javax.swing.*;

public class GameClass implements KeyListener , MouseListener
{
    protected static int key = -1;                   // this variable is changed in keyPressed(KeyEvent e)
    protected static boolean endOfGame = false;      // keeps the game looping and testing for keys pressed and mouse clicks until the user hits ESC
    
    protected static boolean mouseAlreadyClicked = false;   // this variable is set in mouseClicked(MouseEvent e)
    protected static int mouseX = -1;                // this variable is set in mouseClicked(MouseEvent e)
    protected static int mouseY = -1;                // this variable is set in mouseClicked(MouseEvent e)
    
    protected static Canvas canvas;
    
    public GameClass ( )
    {

    }

     public static void mainShell()
    {
        GameClass mygame = new GameClass();
        
        //*****************************************************************
        //  Add these statements to enable keyboard and mouse input
            canvas = Canvas.getCanvas();
            canvas.setListeners(mygame);
        //*****************************************************************
       
       // mygame.start();
        do
        {
            // Handling mouse input
            if (mouseAlreadyClicked)
            {
                System.out.println("Method start() received mouse input with coordinates ( " + mouseX + " , " + mouseY + " )");
                // Figure out what areas on your display these coordinates fall into and call the  appropriate methods to handle the selection
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
                    case 27:    endOfGame = true;
                                break;
                    case 38:    // call method to implement action if user keys an UP arrow
                                break;
                    case 39:    // call method to implement action if user keys an RIGHT arrow
                                break;
                    default:    // ignore the key
                                
                    
                }
                
                key = -1;   // reset key value back to -1 to wait for next input
            }
            
        }while(!endOfGame);     // user needs to hit the ESC key to end the game
        System.out.println("ESC key was pressed to end the game");
        
        //*****************************************************************
        //  Add this statement if enabled keyboard and mouse input
            canvas.stopListeners(mygame);
        //*****************************************************************
    }
    
    public void start()
    {
        do
        {
            // Handling mouse input
            if (mouseAlreadyClicked)
            {
                System.out.println("Method start() received mouse input with coordinates ( " + mouseX + " , " + mouseY + " )");
                // Figure out what areas on your display these coordinates fall into and call the  appropriate methods to handle the selection
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
                    case 27:    endOfGame = true;
                                break;
                    case 38:    // call method to implement action if user keys an UP arrow
                                break;
                    case 39:    // call method to implement action if user keys an RIGHT arrow
                                break;
                    default:    // ignore the key
                                
                    
                }
                
                key = -1;   // reset key value back to -1 to wait for next input
            }
            
        }while(!endOfGame);     // user needs to hit the ESC key to end the game
        System.out.println("ESC key was pressed to end the game");
    }
    
   //******************** to capture keyboard input **************************
    public void keyPressed(KeyEvent e) 
    {
        int keyboardInput;
        keyboardInput = e.getKeyCode();
        //passKBinput(keyboardInput);
        System.out.println("From Gameclass keyPressed ..." + keyboardInput + "...");
        
        // Communicate with method start() by setting variable key
        
        if (key == -1)
           key = keyboardInput;     // sets the variable keyPressed to the key value if no other key is being processed.

        // 48-57  -->  0-9
        // 65-90  -->  a-z
        // 38     -->  up    Arrow
        // 40     -->  down  Arrow
        // 37     -->  left  Arrow
        // 39     -->  right Arrow
    }
    
    public void keyReleased(KeyEvent e) {}
    public void keyTyped(KeyEvent e) {}

    
    
    //******************** to capture mouse clicks **************************
    public void mousePressed(MouseEvent e) {}
    public void mouseReleased(MouseEvent e) {}
    public void mouseClicked(MouseEvent e) 
    {
        int x = e.getX();
        int y = e.getY();
        int calibratedX = x-9;
          if(calibratedX<0) 
             calibratedX=0;
         
        int calibratedY = y-30;
        System.out.println("mouse clicked from Gameclass at " + x + " and " + y + "passed as " + calibratedX + " and " + calibratedY);
        
        
        // Communicate with method start() by setting variables mouseAlreadyClicked and mouseX and mouseY
        
        if(!mouseAlreadyClicked)
        {
            mouseX = calibratedX;       // these are instance variables in the main program
            mouseY = calibratedY;       // these are instance variables in the main program
            mouseAlreadyClicked = true;
        }
        
    }
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
 
}
