import java.awt.Color;
import java.awt.Graphics;

public class MyLine extends MyShape
{
	public MyLine()
	{
		super();
	}
	
	public MyLine(int x1, int x2, int y1, int y2, Color color)
	{
		super(x1, x2, y1, y2, color);
	}
	
	@Override public void draw(Graphics g)
	{
		g.setColor(getColor());
		g.drawLine(getX1(),getX2(),getY1(),getY2());
	}
}