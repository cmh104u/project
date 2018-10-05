import java.awt.Color;
import java.awt.Graphics;

public class MyOval extends MyBoundedShape
{
	public MyOval()
	{
		super();
	}
	
	public MyOval(int x1, int x2, int y1, int y2, Color color, boolean fill)
	{
		super(x1, x2, y1, y2, color, fill);
	}
	
	@Override public void draw(Graphics g)
	{
		g.setColor(getColor());
		if(getIsFilled()){
			g.fillOval(getX1(),getX2(),getWidth(),getHeight());
		}else{
			g.drawOval(getX1(),getX2(),getWidth(),getHeight());
		}
		
	}
}