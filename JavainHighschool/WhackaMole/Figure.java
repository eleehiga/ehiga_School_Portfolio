/**
 * An abstract class for shapes that can be manipulated and that draws itself on a canvas.
 * 
 * @author	Mrs. Miyamoto
 * @version 5.0  (15 July 2004)
 */

abstract public class Figure
{
    protected int xPosition=0;
	protected int yPosition=0;
	protected String color="black";
	protected boolean isVisible=false;
	
	/**
	 * Make this figure visible. If it was already visible, do nothing.
	 */
	public void makeVisible()
	{
		isVisible = true;
		draw();
	}
	
	/**
	 * Make this figure invisible. If it was already invisible, do nothing.
	 */
	public void makeInvisible()
	{
		erase();
		isVisible = false;
	}
	
    /**
	 * Return true if this figure is visible else return false.
	 */
	public boolean isVisible()
	{
		return isVisible;
	}
    
    /**
     * Move the figure a few pixels to the right.
     */
    public void moveRight()
    {
		moveHorizontal(20);
    }

    /**
     * Move the figure a few pixels to the left.
     */
    public void moveLeft()
    {
		moveHorizontal(-20);
    }

    /**
     * Move the figure a few pixels up.
     */
    public void moveUp()
    {
		moveVertical(-20);
    }

    /**
     * Move the figure a few pixels down.
     */
    public void moveDown()
    {
		moveVertical(20);
    }

    /**
     * Move the figure horizontally by 'distance' pixels.
     */
    public void moveHorizontal(int distance)
    {
		erase();
		xPosition += distance;
		draw();
    }

    /**
     * Move the figure vertically by 'distance' pixels.
     */
    public void moveVertical(int distance)
    {
		erase();
		yPosition += distance;
		draw();
    }

    /**
     * Slowly move the figure horizontally by 'distance' pixels.
     */
    public void slowMoveHorizontal(int distance)
    {
		int delta;

		if(distance < 0) 
		{
			delta = -1;
			distance = -distance;
		}
		else 
		{
			delta = 1;
		}

		for(int i = 0; i < distance; i++)
		{
			xPosition += delta;
			draw();
			wait(10);
		}
    }

    /**
     * Slowly move the figure vertically by 'distance' pixels.
     */
    public void slowMoveVertical(int distance)
    {
		int delta;

		if(distance < 0) 
		{
			delta = -1;
			distance = -distance;
		}
		else 
		{
			delta = 1;
		}

		for(int i = 0; i < distance; i++)
		{
			yPosition += delta;
			draw();
			wait(10);
		}
    }

    /**
     * Slowly move the figure horizontally by 'distance' pixels.
     */
    public void slowMoveHorizontal(int distance, int waitn)
    {
		int delta;

		if(distance < 0) 
		{
			delta = -1;
			distance = -distance;
		}
		else 
		{
			delta = 1;
		}

		for(int i = 0; i < distance; i++)
		{
			xPosition += delta;
			draw();
			wait(waitn);
		}
    }

    /**
     * Slowly move the figure vertically by 'distance' pixels.
     */
    public void slowMoveVertical(int distance, int waitn)
    {
		int delta;

		if(distance < 0) 
		{
			delta = -1;
			distance = -distance;
		}
		else 
		{
			delta = 1;
		}

		for(int i = 0; i < distance; i++)
		{
			yPosition += delta;
			draw();
			wait(waitn);
		}
    }
    
    /**
     * Change the color. Valid colors are "red", "yellow", "blue", "green", "magenta",
	 * "white", "orange", "pink", "cyan", "gray", "lightGray", "darkGray"  and "black".
     */
    public void changeColor(String newColor)
    {
        erase();
		color = newColor;
		draw();
    }
    
    public void changeXY(int x, int y)
    {
        erase();
        xPosition = x;
        yPosition = y;
        if(isVisible)
          draw();
    }
    
    public int getX()
    {
        return xPosition;
    }
    
    public int getY()
    {
        return yPosition;
    }
    
    public String getColor()
    {
        return color;
    }
    
	/*
	 * Erase the figure on screen.
	 */
	protected void erase()
	{
		if(isVisible) {
			Canvas canvas = Canvas.getCanvas();
			canvas.erase(this);
		}
	}
	
    /**
     * Change the size to the new size (in pixels). Size must be >= 0.
     */
    
    //abstract public void changeSize(int size);
    
    abstract public void changeSize(int length, int width);    

	/*
	 * Draw the figure with current specifications on screen.
	 */
	abstract protected void draw();
	
	public void wait(int n)
	{
	    Canvas canvas = Canvas.getCanvas();
		canvas.wait(n);
    }

    protected void redraw()
    {
        Canvas canvas = Canvas.getCanvas();
			canvas.redraw();
    }
}
