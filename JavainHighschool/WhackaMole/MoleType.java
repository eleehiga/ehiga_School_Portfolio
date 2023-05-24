
/**
 * Diffrent Types of Moles You Will Encounter.
 * 
 * @author (Ethan Higa) 
 * @version (1.0)
 */
public class MoleType
{
    private int pValue;
    private int hP;
    private char bombLevel;
    private int type1;
    private int m0=0;
    private boolean isBomb;
    public boolean isBlank;
    //Prince Moleton Intro **No Fight**
    private Box eyePatch;
    private Circle happyMouth;
    //Main Mole
    private Circle mEarL;
    private Circle mEarR;
    private Circle mFace;
    private Circle mEyeL;
    private Circle mEyeR;
    private Circle mPupilL;
    private Circle mPupilR;
    private Circle mNose;
    private Box mMouth;
    //Armored Mole Hat
    private Box mTop;
    private Box mHatL;
    private Box mHatR;
    //Bomber Mole
    private Box mFuse;
    private Circle mFlame;
    private Circle mHMouth;
    //Pyro Mole *****BOSS 1*****
    private Box flamethrowerR;
    private Box flamethrowerL;
    //Jetpack Mole
    private Triangle chineseHat;
    private Box jetpackL;
    private Box jetpackR;
    private Circle flameL;
    private Circle flameR;
    //Dragon Mole
    private Box mDBody;
    private Triangle mTLFang;
    private Triangle mTRFang;
    private Triangle mBLFang;
    private Triangle mBRFang;
    public MoleType()
    /**
     * Constructs Regular Mole
     * Lvl 1
     */
    {
        pValue=100;
        isBlank=false;
        hP=1;
        int x=60;
        int y=60;
        //Mole's Left Ear
        mEarL=new Circle(50,30,x,(y-20));
        mEarL.changeColor("lightGray");
        //Mole's Right Ear
        mEarR=new Circle(50,30,(x+50),(y-20));
        mEarR.changeColor("lightGray");
        //Mole's Face
        mFace=new Circle(100,80,x,y);
        mFace.changeColor("orange");
        //Mole's Left Eye
        mEyeL=new Circle(25,25,(x+10),(y+20));
        mEyeL.changeColor("white");
        //Mole's Right Eye
        mEyeR=new Circle(25,25,(x+45),(y+20));
        mEyeR.changeColor("white");
        //Mole's Left Pupil
        mPupilL=new Circle(5,5,(x+20),(y+30));
        mPupilL.changeColor("black");
        //Mole's Right Pupil
        mPupilR=new Circle(5,5,(x+55),(y+30));
        mPupilR.changeColor("black");
        //Mole's Nose
        mNose=new Circle(5,5,(x+36),(y+50));
        mNose.changeColor("black");
        //Mole's Mouth
        mMouth=new Box(3,50,(x+15),(y+70));
        mMouth.changeColor("black");
    }
    
    public MoleType(int type,int lvl, int x,int y)
    {
            //If no if statements activated after it is Regular Mole
            pValue=100;
            isBomb=false;
            type1=type;
            isBlank=false;
            hP=1;
            //Mole's Left Ear
            mEarL=new Circle(50,30,x,(y-20));
            mEarL.changeColor("lightGray");
            //Mole's Right Ear
            mEarR=new Circle(50,30,(x+50),(y-20));
            mEarR.changeColor("lightGray");
            //Mole's Face
            mFace=new Circle(100,80,x,y);
            mFace.changeColor("orange");
            //Mole's Left Eye
            mEyeL=new Circle(25,25,(x+10),(y+20));
            mEyeL.changeColor("white");
            //Mole's Right Eye
            mEyeR=new Circle(25,25,(x+45),(y+20));
            mEyeR.changeColor("white");
            //Mole's Left Pupil
            mPupilL=new Circle(5,5,(x+20),(y+30));
            mPupilL.changeColor("black");
            //Mole's Right Pupil
            mPupilR=new Circle(5,5,(x+55),(y+30));
            mPupilR.changeColor("black");
            //Mole's Nose
            mNose=new Circle(5,5,(x+36),(y+50));
            mNose.changeColor("black");
            //Mole's Mouth
            mMouth=new Box(3,50,(x+15),(y+70));
            mMouth.changeColor("black");
            if(type==0||type==1)
            {
                pValue=0;
                isBlank=true;
                hP=99999999;
                mEarL.changeColor("green");
                mEarR.changeColor("green");
                mFace.changeColor("green");
                mEyeL.changeColor("green");
                mEyeR.changeColor("green");
                mPupilL.changeColor("green");
                mPupilR.changeColor("green");
                mNose.changeColor("green");
                mMouth.changeColor("green");
            }
            
            if(type==5)
            //Armored Mole
            {
                pValue=200;
                hP=3;
                //Army Hat Top
                mTop=new Box(15,80,x,y);
                mTop.changeColor("gray");
                //Army Hat Base Left
                mHatL=new Box(20,10,x,(y+12));
                mHatL.changeColor("gray");
                //Army Hat Base Right
                mHatR=new Box(20,10,(x+70),(y+12));
                mHatR.changeColor("gray");
            }
        
            if(type==6)
            //Bomber Mole
            {
                pValue=150;
                hP=2;
                //Mole's Fuse
                mFuse=new Box(50,5,(x+38),(y-20));
                mFuse.changeColor("gray");
                //Mole Fuse's Flame
                mFlame=new Circle(20,20,(x+30),(y-25));
                mFlame.changeColor("red");
                //Left Eye Change
                mPupilL.moveVertical(-5);
                mPupilL=new Circle(5,5,(x+20),(y+25));
                mPupilL.changeColor("black");
                //Right Eye Change
                mPupilR.moveVertical(5);
                mPupilR=new Circle(5,5,(x+55),(y+35));
                mPupilR.changeColor("black");
            }
        
            if(type==8)
            //Ninja Mole
            {
                pValue=200;
                hP=2;
                mFace.changeColor("black");
            }
        
            if(type==9)
            //Jetpack Mole
            {
                pValue=200;
                hP=2;
                //Mole's Hat
                chineseHat=new Triangle(40,90,(x-5),(y-20));
                chineseHat.changeColor("gray");
                //Jetpack Left
                jetpackL=new Box(60,15,x,(y+25));
                jetpackL.changeColor("blue");
                jetpackR=new Box(60,15,(x+66),(y+25));
                jetpackR.changeColor("blue");
                flameL=new Circle(20,20,(x-5),(y+75));
                flameL.changeColor("red");
                flameR=new Circle(20,20,(x+65),(y+75));
                flameR.changeColor("red");
            }
        
            if(type==10)
            //Dragon Mole
            {
                mFace.changeColor("red");
            }
        
            if(type==11)
            {
            
            }
            
    }
    
    public MoleType(int boss,int x,int y)
    {
            //If no if statements activated after it is Regular Mole
            isBlank=false;
            hP=1;
            //Mole's Left Ear
            mEarL=new Circle(50,30,x,(y-20));
            mEarL.changeColor("lightGray");
            //Mole's Right Ear
            mEarR=new Circle(50,30,(x+50),(y-20));
            mEarR.changeColor("lightGray");
            //Mole's Face
            mFace=new Circle(100,80,x,y);
            mFace.changeColor("orange");
            //Mole's Left Eye
            mEyeL=new Circle(25,25,(x+10),(y+20));
            mEyeL.changeColor("white");
            //Mole's Right Eye
            mEyeR=new Circle(25,25,(x+45),(y+20));
            mEyeR.changeColor("white");
            //Mole's Left Pupil
            mPupilL=new Circle(5,5,(x+20),(y+30));
            mPupilL.changeColor("black");
            //Mole's Right Pupil
            mPupilR=new Circle(5,5,(x+55),(y+30));
            mPupilR.changeColor("black");
            //Mole's Nose
            mNose=new Circle(5,5,(x+36),(y+50));
            mNose.changeColor("black");
            //Mole's Mouth
            mMouth=new Box(3,50,(x+15),(y+70));
            mMouth.changeColor("black");
        if(boss==0)
        {
            hP=99;
            //Eyepatch
            mEyeR.changeColor("black");
            eyePatch=new Box(5,70,(x+5),(y+20));
            eyePatch.changeColor("black");
        }
        if(boss==1)
            //Pyro Mole *BOSS*
            {
                hP=30;
                pValue=500;
                //Mole Suit
                mPupilL=null;
                mPupilR=null;
                mMouth=null;
                mFace.changeColor("red");
                //Mole's Flamethrower Large
                flamethrowerL=new Box(20,40,x,(y+60));
                flamethrowerL.changeColor("black");
                //Mole's Flamethrower Nozzle
                flamethrowerR=new Box(10,20,(x+40),(y+60));
                flamethrowerR.changeColor("black");
            }
        if(boss==2)
        {
            
        }
    }
    
    public MoleType(boolean bomb,int x,int y)
    {
                isBlank=false;
                isBomb=true;
                //The Bomb
                mFace=new Circle(100,80,x,y);
                mFace.changeColor("black");
                //Bomb's Fuse
                mFuse=new Box(50,5,(x+38),(y-20));
                mFuse.changeColor("gray");
                //Bomb's Flame
                mFlame=new Circle(20,20,(x+30),(y-25));
                mFlame.changeColor("red");
    }
    
    public void makeVisible()
    {
        if (isBlank==false)
        {
            if(mFuse!=null&&mFlame!=null)
            {
                mFuse.makeVisible();
                mFlame.makeVisible();
            }
            if(mEarL!=null)
            {
                mEarL.makeVisible();
                mEarR.makeVisible();
            }
            if(jetpackL!=null)
            {
                flameL.makeVisible();
                flameR.makeVisible();
                jetpackL.makeVisible();
                jetpackR.makeVisible();
            }
            if(mFace!=null)
            {
                mFace.makeVisible();
            }
            if(eyePatch!=null)
            {
                eyePatch.makeVisible();
            }
            if(mEyeL!=null)
            {
                mEyeL.makeVisible();
                mEyeR.makeVisible();
            }
            if(mPupilL!=null)
            {
                mPupilL.makeVisible();
                mPupilR.makeVisible();
                mNose.makeVisible();
            }
            if(mMouth!=null)
            {
                mMouth.makeVisible();
            }
            if(mTop!=null)
            {
                mTop.makeVisible();
                mHatL.makeVisible();
                mHatR.makeVisible();
            }
            if(flamethrowerL!=null)
            {
                flamethrowerL.makeVisible();
                flamethrowerR.makeVisible();
            }
            if(chineseHat!=null)
            {
                chineseHat.makeVisible();
            }
            mFace.redraw();
        }
    }
    
    public void makeInvisible()
    {
        if(mFuse!=null&&mFlame!=null)
        {
            mFuse.makeInvisible();
            mFlame.makeInvisible();
        }
        if(mEarL!=null)
        {
            mEarL.makeInvisible();
            mEarR.makeInvisible();
        }
        if(jetpackL!=null)
            {
                flameL.makeInvisible();
                flameR.makeInvisible();
                jetpackL.makeInvisible();
                jetpackR.makeInvisible();
            }
        if(mFace!=null)
        {
            mFace.makeInvisible();
        }
        if(eyePatch!=null)
        {
                eyePatch.makeInvisible();
        }
        if(mEyeL!=null)
        {
            mEyeL.makeInvisible();
            mEyeR.makeInvisible();
        }
        if(mPupilL!=null)
        {
            mPupilL.makeInvisible();
            mPupilR.makeInvisible();
            mNose.makeInvisible();
        }
        if(mMouth!=null)
        {
            mMouth.makeInvisible();
        }
        if(mTop!=null)
        {
            mTop.makeInvisible();
            mHatL.makeInvisible();
            mHatR.makeInvisible();
        }
        if(flamethrowerL!=null)
        {
            flamethrowerL.makeInvisible();
            flamethrowerR.makeInvisible();
        }
        if(chineseHat!=null)
            {
                chineseHat.makeInvisible();
            }
        mFace.redraw();
    }
    
    public void subtractHp()
    {
        if(mFace.isVisible()==true&&isBlank==false)
        {
            hP--;
            if (hP<=0)
            {
                    isBlank=true;
                    makeInvisible();
                    mFace.redraw();
            }
        }
    }
    
    public int getType()
    {
        return type1;
    }
    
    public boolean isVisible()
    {
        if (mFace.isVisible()&&mFace!=null)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    public boolean bombVisible()
    {
        if(mFace.isVisible()&&mFuse.isVisible())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    public boolean isBlank()
    {
        return isBlank;   
    }
    
    public boolean isBomb()
    {
        return isBomb;
    }
    
    public int getpValue()
    {
        return pValue;
    }
    
    public int getHp()
    {
        return hP;
    }
    
    public String face()
    {
        return mFace.getX()+","+mFace.getY();
    }
    
    
    
    public void moveHorizontal(int h)
    {
        if(mFuse!=null&&mFlame!=null)
        {
            mFuse.moveHorizontal(h);
            mFlame.moveHorizontal(h);
        }
        mEarL.moveHorizontal(h);
        mEarR.moveHorizontal(h);
        mFace.moveHorizontal(h);
        mEyeL.moveHorizontal(h);
        mEyeR.moveHorizontal(h);
        mPupilL.moveHorizontal(h);
        mPupilR.moveHorizontal(h);
        mNose.moveHorizontal(h);
        mMouth.moveHorizontal(h);
        if(mTop!=null)
        {
            mTop.moveHorizontal(h);
            mHatL.moveHorizontal(h);
            mHatR.moveHorizontal(h);
        }
        mFace.redraw();
    }
    
    
}
