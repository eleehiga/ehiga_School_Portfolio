import java.awt.*;

/**
 * A triangle that can be manipulated and that draws itself on a canvas.
 * 
 * @author	Michael Kolling and David J. Barnes
 * @version 1.0  (15 July 2000)
 */

public class Triangle extends Figure
{
    private int height;
    private int width;

    /**
     * Create a new triangle at default position with default color.
     */
    public Triangle()
    {
		height = 30;
		width = 30;
		xPosition = 50;
		yPosition = 15;
		color = "green";
    }
    
    public Triangle(int height, int width, int x, int y)
    {
     	this.height = height;
     	this.width = width;
		xPosition = x;
		yPosition = y;
		color = "green";
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
    
	/*
	 * Draw the triangle with current specifications on screen.
	 */
	protected void draw()
	{
		if(isVisible) {
			Canvas canvas = Canvas.getCanvas();
			int[] xpoints = { xPosition, xPosition + (width/2), xPosition + width };
			int[] ypoints = { yPosition + height, yPosition , yPosition + height };
			//int[] xpoints = { xPosition, xPosition + (width/2), xPosition - (width/2) };
			//int[] ypoints = { yPosition, yPosition + height, yPosition + height };
			canvas.draw(this, color, new Polygon(xpoints, ypoints, 3));
			//canvas.wait(10);
		}
	}


}
