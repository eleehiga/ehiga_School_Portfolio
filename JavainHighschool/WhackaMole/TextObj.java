
/**
 * Write a description of class textWriter here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class TextObj extends Figure
{
    protected String text;
    protected int fontSize=12;
    protected boolean bold=false;

    public TextObj()
    {
        text = "";
        changeXY(0,30);
    }
    
    public TextObj(String str, int x, int y)
    {
        text=str;
        xPosition=x;
        yPosition=y;
    }

    public TextObj(String str, String color,int x, int y)
    {
        this(str,x,y);
        this.color=color;
    }    

    public TextObj(String str, String color,int x, int y, int fontSize)
    {
        this(str,x,y);
        this.color=color;
        this.fontSize=fontSize;
    }


    
    public void bold()
    {
        bold=true;
        draw();
    }
    
    public void unBold()
    {
        bold=false;
        draw();
    }

    public void changeFontSize(int size)
    {
        fontSize=size;
        draw();
    }
    
    public void changeSize(int length, int height)
    {
        fontSize=height;
	    draw();
    }

   
    protected void draw()
    {
        if(isVisible) {
            Canvas canvas = Canvas.getCanvas();
            canvas.draw(this,this);
            canvas.wait(10);
        }
    }

    public String getText()
    {
        return text;
    }
    
    public void changeText(String newstr)
    {
        text = newstr;
        draw();
    }
    
    public int getFontSize()
    {
        return fontSize;
    }
    
    public boolean getBold()
    {
        return bold;
    }
    
    
}
