public class GameBoard
{
       private Box[] row=new Box[6];
       private Box[] column=new Box[6];
       private Circle[] displayHp=new Circle[3];
        
    public GameBoard()
    {
        for(int b1=0;b1<6;b1++)
        {
            row[b1]=new Box(10,1000,0,(b1*160));
        }
        for(int b2=0;b2<6;b2++)
        {
            column[b2]=new Box(1000,10,(b2*160),0);
        }
        for(int b4=0;b4<displayHp.length;b4++)
        {
            displayHp[b4]=new Circle(100,100,1200,((b4*200)+100));
            displayHp[b4].changeColor("red");
        }
        row[0].redraw();
    }
    
    public void makeVisible()
    {
        for(int b3=0;b3<6;b3++)
        {
            row[b3].makeVisible();
            column[b3].makeVisible();
        }
        for(int b4=0;b4<displayHp.length;b4++)
        {
            displayHp[b4].makeVisible();
        }
        row[0].redraw();
    }
    
    public int damageToYou()
    {
            if(displayHp[0].isVisible==true)
            {
                displayHp[0].makeInvisible();
                displayHp[0].redraw();
                return 2;
            }
            else if(displayHp[1].isVisible==true)
            {
                displayHp[1].makeInvisible();
                displayHp[1].redraw();
                return 1;
            }
            else if(displayHp[2].isVisible==true)
            {
                displayHp[2].makeInvisible();
                displayHp[2].redraw();
                return 0;
            }
            else
            {
                return 0;
            }
    }
    
    public int resetHp()
    {
        for(int b4=0;b4<displayHp.length;b4++)
        {
            displayHp[b4].makeVisible();
        }
        return 3;
    }
}