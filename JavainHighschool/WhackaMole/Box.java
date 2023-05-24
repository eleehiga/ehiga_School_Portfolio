import java.awt.*;

/**
 * A square that can be manipulated and that draws itself on a canvas.
 * 
 * @author	Michael Kolling and David J. Barnes
 * @version 1.0  (15 July 2000)
 */

public class Box extends Figure
{
    private int height;
    private int width;


    /**
     * Create a new square at default position with default color.
     */
    public Box()
    {
		height = width = 30;
		xPosition = 0;
		yPosition = 0;
		color = "red";

    }
    
    public Box(int height, int width, int x, int y)
    {
     	this.height = height;
     	this.width = width;
		xPosition = x;
		yPosition = y;
		color = "red";
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
    
    public void changeSize(int newSize)
    {
        erase();
        height = newSize;
        width = newSize;
        draw();
    }

	/*
	 * Draw the square with current specifications on screen.
	 */
	protected void draw()
	{
		if(isVisible) {
			Canvas canvas = Canvas.getCanvas();
			canvas.draw(this, color,
						new Rectangle(xPosition, yPosition, width, height));
			//canvas.wait(10);
		}
	}


}
