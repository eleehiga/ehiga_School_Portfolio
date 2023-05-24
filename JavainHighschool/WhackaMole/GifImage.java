import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.List;
import java.util.*;

//import javax.swing.*;
//import java.awt.*;
//import java.util.*;
/**
 * Write a description of class GifImage here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class GifImage extends Figure
{
    private String gifFile;
    private int width;
    private int height;
    private Image img;
    
    public GifImage()
    {}
    
    public GifImage(String gifFile)
    {
        this.gifFile = gifFile;
   
        JFrame frame = new JFrame();
        //canvas canvas = Canvas.getCanvas();
        //CanvasPane canvas = new CanvasPane();
        //frame.setContentPane(canvas);
        //frame.setTitle(title);
        frame.setSize(new Dimension(550,500));
        
        img=Toolkit.getDefaultToolkit().getImage(gifFile);
        width = img.getWidth(frame);
        height = img.getHeight(frame);
        
        while(width==-1 || height==-1)
          initSize();
    }
    
    public void initSize()
    {
        JFrame frame = new JFrame();
        //canvas canvas = Canvas.getCanvas();
        //CanvasPane canvas = new CanvasPane();
        //frame.setContentPane(canvas);
        //frame.setTitle(title);
        frame.setSize(new Dimension(550,500));
        
        img=Toolkit.getDefaultToolkit().getImage(gifFile);
        width = img.getWidth(frame);
        height = img.getHeight(frame);
    }
    
    public void setWidth(int w)
    {
        width=w;
    }
    
    public void setHeight(int h)
    {
        height=h;
    }
    
//     public void changeHeightWidth(int h, int w)
//     {
//         this.height=h;
//         this.width=w;
//         draw();
//     }
    
    public int width()
    {
        return width;
    }
    
    public int height()
    {
        return height;
    }
	public void changeColor(String newColor)
    {
    }
    
  
    public String getColor()
    {   return "red"; }
    
    public void changeSize(int height, int width)
    {
       // changeHeightWidth(width,length);
        this.height=height;
        this.width=width;
        draw();
    }
    
    public String getGifFile()
    {
        return gifFile;
    }

    public Image getImg()
    {
        return img;
    }
    protected void draw()
    {
    if(isVisible) {
			Canvas canvas = Canvas.getCanvas();
			//g.drawImage(Toolkit.getDefaultToolkit().getImage(d.getGifFile()),d.getX(),d.getY(),this);
			canvas.draw(this,this);
			//canvas.draw(this, color, new Ellipse2D.Double(xPosition, yPosition, width, height));
			canvas.wait(5);
		}
    }
}
