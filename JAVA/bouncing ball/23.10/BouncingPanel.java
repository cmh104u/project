import javax.swing.JPanel;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Graphics;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;

public class BouncingPanel extends JPanel
{
	final private int radius = 10;
	private int X;
	private int Y;
	private int start;	//be 1 when mouse press, otherwise be 0
	private Ball ballThreads;
	private ExecutorService executorService;
	
	public BouncingPanel()
	{
		X = 450;
		Y = 600;
		start = 0;
		//register
		MouseHandler handler = new MouseHandler();
		addMouseListener(handler);
		
		//
		executorService = Executors.newCachedThreadPool();
	}
	
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.setColor(Color.BLUE);
		g.fillOval(X-radius, Y-radius, 2*radius, 2*radius);
	}
	
	private class MouseHandler extends MouseAdapter
	{
		@Override
		public void mousePressed(MouseEvent event)
		{
			if(start == 0){
				ballThreads = new Ball();
				executorService.execute(ballThreads);
				start = 1;
			}
		}
	}
	
	//thread let ball to move
	public class Ball implements Runnable
	{
		private int dx;
		private int dy;
		
		public Ball()
		{
			dx = 3;
			dy = 4;
		}
		
		public void run()
		{
			while(true){ 
				X = X + dx;
				Y = Y + dy;
 
				if(X - radius < 0) {
					dx = -dx; 
					X = radius; 
				}else if (X + radius > 900) {
					dx = -dx;
					X = 900 - radius;
				}
 
				if(Y - radius < 0) {
					dy = -dy;
					Y = radius;
				}else if (Y + radius > 900) {
					dy = -dy;
					Y = 900 - radius;
				}
				repaint();
				try{
					Thread.sleep(20);
				}catch(InterruptedException ex) {
				}
			}
		}
	}
	
	
}