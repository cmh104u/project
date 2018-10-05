import java.awt.Graphics;
import javax.swing.JPanel;
import java.awt.Color;

public class DrawPanel extends JPanel
{
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		
		MyShape[] shape = new MyShape[3];
		
		shape[0] = new MyLine(0,0,500,500,Color.RED);
		shape[1] = new MyOval(500,500,800,800,Color.GREEN,true);
		shape[2] = new MyRectangle(0,500,500,800,Color.BLACK,false);
		
		for(MyShape s : shape)
		{
			s.draw(g);
		}
		
	}



}