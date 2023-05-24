import java.awt.*;
import java.awt.geom.*;

/**
 * A circle that can be manipulated and that draws itself on a canvas.
 * 
 * @author	Michael Kolling and David J. Barnes
 * @version 1.0  (15 July 2000)
 */

public class Circle extends Figure
{
    private int height;
    private int width;
	
    /**
     * Create a new circle at default position with default color.
     */
    public Circle()
    {
		height = 30;
		width = 30;
		xPosition = 20;
		yPosition = 60;
		color = "blue";

    }
    
    public Circle(int height, int width, int x, int y)
    {
     	this.height = height;
     	this.width = width;
		xPosition = x;
		yPosition = y;
		color = "blue";
    }

    /**
     * Change the size to the new size (in pixels). Size must be >= 0.
     */
  
    public void changeSize(int newHeight, int newWidth)
    {
        erase();
        height = newHeight;
        width = newWidth;
        draw();
    }
      
    public void changeSize(int newDiameter)
    {
        erase();
        height = newDiameter;
        width = newDiameter;
        draw();
    }
	/*
	 * Draw the circle with current specifications on screen.
	 */
	protected void draw()
	{
		if(isVisible) {
			Canvas canvas = Canvas.getCanvas();
			canvas.draw(this, color, new Ellipse2D.Double(xPosition, yPosition, 
														  width, height));
			//canvas.wait(5);
		}
	}
    
	public int getHeight()
	{
	    return this.height;
	   }
	   
	public int getWidth()
	{
	    return this.width;
	   }
}
