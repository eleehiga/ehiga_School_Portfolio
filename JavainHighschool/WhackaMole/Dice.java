
/**
 * Write a description of class Dice here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Dice
{

    private final String BLANK = "";
    
    private int value=0;
    private String face = "";
    

    /**
     * Constructor for objects of class Dice assigns the dice a random value between 1-6
     */
    public Dice()
    {
        roll();
    }

    /**
     * Constructor for objects of class Dice assigns the dice a random value n
     * @param n  a value between 1 and 6 to be assigned to the dice
     */
    public Dice(int n)
    {
        value = n;
        switch(value)
        {
            case 1: face = "1"; break;
            case 2: face = "2"; break;
            case 3: face = "3"; break;
            case 4: face = "4"; break;
            case 5: face = "5"; break;
		    case 6: face = "6"; break;
            default: value=0; face = "0";   
        }
    }

    /**
     * randomly picks a number between 1 and 6 and sets the dice to represent that value
     */
    public int roll()
    {
        value = (int)Math.floor(Math.random()*6 + 1);
        switch(value)
        {
            case 1: face = "1"; break;
            case 2: face = "2"; break;
            case 3: face = "3"; break;
            case 4: face = "4"; break;
            case 5: face = "5"; break;
		    case 6: face = "6"; break;
		    default: value=0; face = "0";
		}
		return value;
	}
	
	/**
	 * returns the integer value of the dice 
	 */
	public int diceValue()
	{
	    return value;
	}
	
	/**
	 * returns the value of the dice as a String
	 */
	public String diceFace()
	{
	    return face;
	}
	
	public static void main(String[]args)
	{
	    Dice a;
	    TextObj w;
	    for(int i=1; i<=7; i++)
	    {
	        a = new Dice(i);
	        w = new TextObj(a.diceFace(),"blue", 20, 30*i);
	        w.makeVisible();
	        a.roll();
	        w = new TextObj(a.diceFace(),"red", 50, 30*i);
	        w.makeVisible();
	    }
	}
}
