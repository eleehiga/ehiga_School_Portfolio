import java.awt.event.*; 
import javax.swing.*;
import java.util.*;
import javax.sound.*;
import javax.sound.sampled.AudioInputStream;
/**
 * Write a description of class CardGame here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

public class YourGame extends GameClass   //inherits KeyListener and MouseListener from GameClass
{
	public AudioInputStream regularBattles = new AudioInputStream(URL "https://soundcloud.com/hingyan/kirby-planet-robobot-music-company-boss-battle-theme", Format );
	
	
    // inherits the following data members from GameClass that are accessible to you because they are protected
    //     protected int key = -1;                          // this variable is changed in keyPressed(KeyEvent e)
    //     protected boolean endOfGame = false;             // keeps the game looping and testing for keys pressed and mouse clicks until the user hits ESC
    //     protected boolean mouseAlreadyClicked = false;   // this variable is set in mouseClicked(MouseEvent e)
    //     protected int mouseX = -1;                       // this variable is set in mouseClicked(MouseEvent e)
    //     protected int mouseY = -1;                       // this variable is set in mouseClicked(MouseEvent e)
    //     
    //     protected static Canvas canvas;
    
    // add the data members for YourGame here
    private GameBoard gameBoard=new GameBoard();;
    private MoleType[][] moles=new MoleType[5][5];
    private MoleType[][] bombs=new MoleType[5][5];
    private MoleType princeMoleton=new MoleType(0,1160,745);
    private Random ran=new Random();
    private String adminCode;
    private String selector;
    private int intensity=1;
    private int yourHp=3;
    private int points=0;
    private double loops=0;
    private int megaLoops=0;
    private int level=1;
    private boolean bossBeaten=false;
    private String yourName;
    YourGame ( )
    {

    }
    
    public static void main(String [] args)
    {
        YourGame mygame = new YourGame();
        canvas = Canvas.getCanvas();
        canvas.setListeners(mygame);  // enables keyboard and mouse input

        mygame.start();
       
        canvas.stopListeners(mygame);  // stops keyboard and mouse input before ending the game
    }
    
    public void start()
    {
        //Multi Level
            princeMoleton.makeVisible();
                JOptionPane.showMessageDialog(null,"Wake up farmer.");
                JOptionPane.showMessageDialog(null,"I said, WAKE UP FARMER!");
                JOptionPane.showMessageDialog(null,"Whoa don't hurt me!\n And I won't hurt you!");
                JOptionPane.showMessageDialog(null,"Well your finally up, but anyway, your farm is under attack by the mole army\n Led by, my father, King Mole");
                yourName=JOptionPane.showInputDialog(null,"First what is your name?");
                JOptionPane.showMessageDialog(null,"Well salutations "+yourName+" my name is Prince Moleton, and I am here to help you defeat my father.");
                
                JOptionPane.showMessageDialog(null,"Good luck defending your broccili patch. :D");
                princeMoleton.makeInvisible();
        do
        {
            if(level>1)
            {
                princeMoleton.makeVisible();
                JOptionPane.showMessageDialog(null," Good job!");
            }
            if(level==2)
            {
                JOptionPane.showMessageDialog(null,"Now look out for the armored mole he is armored and prepared to take on your hits!.");
            }
            else if(level==3)
            {
                JOptionPane.showMessageDialog(null,"Now here comes the bomber mole try to destroy him before the level ends or... KABOOM!.");
                
            }
            else if(level==4)
            {
                JOptionPane.showMessageDialog(null,"Warning farmer "+yourName+" the leader of the Basic Army called Pyro Mole is here to destroy you!");
            }
            else if(level==5)
            {
                JOptionPane.showMessageDialog(null,"Now that we defeated the basic army let's Head over to the bok choy patch to defeat the Asian Mole Army.");
                JOptionPane.showMessageDialog(null,"(Loading)");
                JOptionPane.showMessageDialog(null,"(Loading");
                JOptionPane.showMessageDialog(null,"While we were traveling here I saw the ninja mole's on the move, be careful they have quick bombs.");
            }
            else if(level==6)
            {
                JOptionPane.showMessageDialog(null,"The jetpack moles like to fly around a lot with their firework jetpack, be careful.");
            }
            else if(level==7)
            {
                JOptionPane.showMessageDialog(null,"The dragon mole likes to breathe fire and set off bombs, be careful.");
            }
                princeMoleton.makeInvisible();
            //creates Moles
            gameBoard.makeVisible();
            for(int r=0;r<moles.length;r++)
            {
                for(int c=0;c<moles[0].length;c++)
                {
                    moles[r][c]=new MoleType((ran.nextInt(level+4)),intensity,((160*c)+40),((160*r)+40));
                    bombs[r][c]=new MoleType(false,((160*c)+40),((160*r)+40));
                    moles[r][c].makeVisible();
                }
            }
            if(level%4==0)
            {
                moles[2][2].makeInvisible();
                moles[2][2]=null;
                moles[2][2]=new MoleType(1,((160*2)+40),((160*2)+40));
                moles[2][2].makeVisible();
            }
            JOptionPane.showMessageDialog(null,"Level "+level);
            
            if(level==1)
            {
                princeMoleton.makeVisible();
                JOptionPane.showMessageDialog(null,"Alright, here is where my helping skill come in handy.");
                JOptionPane.showMessageDialog(null,"The mole army's favorite choice of weapon to deal with humans is the bomb.");
                JOptionPane.showMessageDialog(null,"If you hit a bomb your health, displayed as the three circles above me, will go down.");
                JOptionPane.showMessageDialog(null,"So do not whack the bombs and hit the moles,\n not me...");
                JOptionPane.showMessageDialog(null,"Remember certain amount of moles requires more hits to defeat them.\n Good luck!");
                princeMoleton.makeInvisible();
            }
            
            //change to bombs 1,000,000+ loop and 1/1400 chance of changing
            do
            {
                if (loops%1000000==0)
                {
                    for(int r=0;r<moles.length;r++)
                    {
                        for(int c=0;c<moles[0].length;c++)
                        {
                            if(ran.nextInt(701)==1)
                            {
                                if(ran.nextInt(2)==1&&moles[r][c].isVisible()==true)
                                {
                                    moles[r][c].makeInvisible();
                                    bombs[r][c].makeVisible();
                                }
                                else if(ran.nextInt(2)==0&moles[r][c].isVisible()!=true)
                                {
                                    moles[r][c].makeVisible();
                                    bombs[r][c].makeInvisible();
                                }
                            }
                        }
                    }
                }
           
            
                // Handling mouse input
                if (mouseAlreadyClicked)
                {
                    System.out.println("Method start() received mouse input with coordinates ( " + mouseX + " , " + mouseY + " )");
                
                    //If tapped Mouse will lose hP but if you tap a bomb you will lose hP
                    if ((mouseX>=0&&mouseX<760)&&(mouseY>=0&&mouseY<800))
                    {
                        moles[mouseY/160][mouseX/152].subtractHp();
                        if(bombs[mouseY/160][mouseX/152].bombVisible())
                        {
                            yourHp=gameBoard.damageToYou();
                            points=points-100;
                        }
                        else if(moles[mouseY/160][mouseX/152].isBlank()==true&&moles[mouseY/160][mouseX/153].isVisible()==false)
                        {
                            //Adds points
                            points=points+(moles[mouseY/160][mouseX/152].getpValue());
                        }
                    }
                    mouseAlreadyClicked=false;
                }
            
                    // Handling keyboard input.  Add cases for specific key values and the java statements you want to execute for that key.
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
                            case 81:    endOfGame = true;
                            break;// end game if user hits a q
                            case 38:    princeMoleton.makeVisible();
                                        adminCode=JOptionPane.showInputDialog(null,"Whoa, didn't know you were the admin, so what is the admin code?");
                                        if(adminCode.equals("itsyousilly"))
                                        {
                                            selector=JOptionPane.showInputDialog(null,"What level would like to visit?");
                                            level=Integer.parseInt(selector);
                                            level=level-1;
                                            megaLoops=2;
                                            JOptionPane.showMessageDialog(null," See you on Level "+(level+1)+"!");
                                        }
                                        else
                                        {
                                            JOptionPane.showMessageDialog(null,"Ha ha, sorry incorrect.");
                                        }
                                        princeMoleton.makeInvisible();
                                        break;
                            default:    // ignore any other keys
                        }
                
                        key = -1;   // reset key value back to -1 to wait for next input
                    }
                    loops++;
                //Max=999,999,999 of loops 
                    if(loops>999999999)
                    {
                        loops=0;
                        megaLoops++;
                    }
                if(level%4==0&&moles[2][2].getHp()<=0)
                {
                    bossBeaten=true;
                    megaLoops=0;
                }
                //Surviving the mole wave and passing two mega Loops wins the level
                }while(!endOfGame&&yourHp>0&&megaLoops<=2&&megaLoops<=1&&bossBeaten==false);
             if(yourHp>0)
             {
                if(endOfGame==true)
                //If escape was pressed if would reset the level
                {
                    JOptionPane.showMessageDialog(null,"You restarted the level...");
                }
                else if(megaLoops>=1||bossBeaten==true)
                {
                    JOptionPane.showMessageDialog(null,"You won level "+level+" with "+points+" points!");
                    level++;
                    loops=0;
                    megaLoops=0;
                    bossBeaten=false;
                    JOptionPane.showMessageDialog(null,"The next level shall begin");
                }
              }
                else if(yourHp<=0)
            {
                JOptionPane.showMessageDialog(null,"You loss!");
            }
            for(int r=0;r<moles.length;r++)
            {
                for(int c=0;c<moles[0].length;c++)
                {
                    moles[r][c].makeInvisible();
                    bombs[r][c].makeInvisible();
                }
            }
            yourHp=gameBoard.resetHp();
            loops=0;
            megaLoops=0;
            }while(level<=7);
        // user needs to hit the ESC key to end the game
        JOptionPane.showMessageDialog(null,"Thanks "+yourName+", for playing Whack a Mole RPG by Ethan Higa! \n:D");
        System.out.println("ESC key was pressed to end the game");
    }

}
