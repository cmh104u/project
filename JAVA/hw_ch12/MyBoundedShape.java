import java.awt.Color;
import java.awt.Graphics;

public abstract class MyBoundedShape extends MyShape
{
	private boolean isFilled;
	
	public MyBoundedShape()
	{
		super();
		isFilled = false;
	}
	
	public MyBoundedShape(int x1, int x2, int y1, int y2, Color color, boolean fill)
	{
		super(x1, x2, y1, y2, color);
		isFilled = fill;
	}
	
	public int getWidth()
	{
		return getY1()-getX1();
	}
	
	public int getHeight()
	{
			return getY2()-getX2();
	}
	
	public void setIsFilled(boolean fill)
	{
		isFilled = fill;
	}
	
	public boolean getIsFilled()
	{
		return isFilled;
	}


}