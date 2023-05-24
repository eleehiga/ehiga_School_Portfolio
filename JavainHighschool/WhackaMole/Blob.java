import java.awt.*;

/**
 * A Blob that can be manipulated and that draws itself on a canvas.
 * 
 * @author	Michael Kolling and David J. Barnes
 * @version 1.0  (15 July 2000)
 */

public class Blob extends Figure
{
    int nCoord;
    int [] xCoord;
    int [] yCoord;

    /**
     * Create a new triangle at default position with default color.
     */
    public Blob()
    {
        this(4);
        xCoord[0] = 10;  yCoord[0] = 70;
        xCoord[1] = 70;  yCoord[1] = 90;
        xCoord[2] = 70;  yCoord[2] = 70;
        xCoord[3] = 10;  yCoord[3] = 90;
    }
    
    public Blob (int numCoordinates)
    {
        nCoord = numCoordinates;
        xCoord = new int [nCoord];
        yCoord = new int [nCoord];
        color = "black";
        
        for(int i=0; i<nCoord; i++)
        {
            xCoord[i] = -1;
            yCoord[i] = -1;
        }
    }
    
    public void makeVisible()
    {
        for(int i=0; i<nCoord; i++)
          if (xCoord[i]== -1 || yCoord[i]== -1)
            return;
        super.makeVisible();
        
    }


    /**
     * Change the size to the new size (in pixels). Size must be >= 0.
     */
    public void changeSize(int newHeight, int newWidth)
    {
    }
    public void changeSize(int idx, int x, int y)
    {
        erase();
        xCoord[idx] = x;
        xCoord[idx] = y;
        draw();
    }
    
     public void changeSize(int numCoordinates)
     {
         nCoord = numCoordinates;
         for (int i = 0; i<nCoord; i++)
         {
            // xCoord[i] = Integer.parseInt(JOptionPane.showInputDialog);
         }
     }



	/*
	 * Draw the triangle with current specifications on screen.
	 */
	protected void draw()
	{
		if(isVisible) {
			Canvas canvas = Canvas.getCanvas();
			//int[] xpoints = { xPosition, xPosition + (width/2), xPosition - (width/2) };
			//int[] ypoints = { yPosition, yPosition + height, yPosition + height };
			canvas.draw(this, color, new Polygon(xCoord, yCoord, nCoord));
			//canvas.wait(10);
		}
	}


}

