import java.awt.event.*;
import javax.swing.*;

public class SimpleGameSample
{
    private static final int TOP_MARGIN=100;
    private static final int LEFT_MARGIN=100;
    private static final int ROW_WIDTH=50;
    private static final int COL_WIDTH=50;
    
    private TextObj title, letterX, letterY;
    Circle c;
    Triangle t;
    Box b;
    Card ace, joker;
        
    private Figure[][] board = new Figure[3][3];
       
    private Box[] lines = new Box[4];
    
    public static void main(String[]args)
    {
        SimpleGameSample ttt = new SimpleGameSample();
        
        ttt.setup();
        
        ttt.start();
    }
    
    public void setup()
    {
        // Create title
        title = new TextObj("My Game Board", "blue", 100, 50, 20);
        title.makeVisible();
        
           // draw grid lines
        drawLines();
        
           // create shapes and put them in the "board"
        c = new Circle();
        t = new Triangle();
        b = new Box();
        
        letterX = new TextObj("X",0,0);
        letterY = new TextObj("Y",0,0);
    }
    
    public void drawLines()
    {
        // create horizontal lines
        for(int i = 0; i<2;i++)
        {
            lines[i] = new Box();
            lines[i].changeSize(1,ROW_WIDTH*3);
            lines[i].changeXY(LEFT_MARGIN, TOP_MARGIN + (i+1)*ROW_WIDTH);
            lines[i].makeVisible();
        }
        // create vertical lines
        for(int i = 2; i<4;i++)
        {
            lines[i] = new Box();
            lines[i].changeSize(COL_WIDTH*3,1);
            lines[i].changeXY(LEFT_MARGIN+(i-1)*COL_WIDTH, TOP_MARGIN);
            lines[i].makeVisible();
        }
    }

    public void start()
    {
        addFigureToBoard(c,0,0);
        addFigureToBoard(t,1,1);
        addFigureToBoard(b,2,2);

           // create text objects and put them in the "board"

        addTextToBoard(letterX,0,2);
        addTextToBoard(letterY,2,0);
        
          // move circle then enlarge it
        board[0][0].slowMoveVertical(ROW_WIDTH*2);
        board[0][0].slowMoveHorizontal(COL_WIDTH);
        c.changeSize(COL_WIDTH-6,ROW_WIDTH-6);
        
           // create Card objects and put them in the "board"
        ace = new Card(1,"Hearts");
        joker = new Card();
        addTextToBoard(ace,0,1);
        addTextToBoard(joker,1,2);
        
        // change font size of letterX
        ( (TextObj)board[0][2] ).changeFontSize(ROW_WIDTH);
        letterY.changeFontSize(ROW_WIDTH);
    }
    
    // ***********  sample methods for board games ***************************
   public void addFigureToBoard(Figure figure,int row, int col)
   {
       if(board[row][col] != null)
          board[row][col].makeInvisible();
       
       board[row][col] = figure;
         
          // set the X and Y coordinates to position the figure to fit within the grid
       board[row][col].changeXY(LEFT_MARGIN+col*COL_WIDTH+3, TOP_MARGIN+row*ROW_WIDTH+3);
       board[row][col].makeVisible();
   }
   
   public void addTextToBoard(TextObj t,int row, int col)
   {
       if(board[row][col] != null)
          board[row][col].makeInvisible();
       
       board[row][col] = t;
       
          // set the X and Y coordinates to position the figure to fit within the grid
       board[row][col].changeXY(LEFT_MARGIN+col*COL_WIDTH+3, TOP_MARGIN+row*ROW_WIDTH+3);
          // since TextObj objects (x,y) refers to the BOTTOM left corner, raise it by 1 ROW_WIDTH
       board[row][col].moveVertical(ROW_WIDTH-6);
       board[row][col].makeVisible();

   }
    
}
