import javax.swing.JPanel;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Graphics;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.security.SecureRandom;

public class BouncingPanel extends JPanel
{
	private static final SecureRandom generator = new SecureRandom();
	final private int radius = 10;
	final private int MAX_BALL_NUM = 50;
	private int[] X;
	private int[] Y;
	private Ball[] ballThreads;
	private Color[] ballColor;
	private int ballCnt;
	private ExecutorService executorService;
	
	public BouncingPanel()
	{
		X = new int[MAX_BALL_NUM];
		Y = new int[MAX_BALL_NUM];
		ballThreads = new Ball[MAX_BALL_NUM];
		ballColor = new Color[MAX_BALL_NUM];
		ballCnt = 0;
		
		//register
		MouseHandler handler = new MouseHandler();
		addMouseListener(handler);
		addMouseMotionListener(handler);
		
		//
		executorService = Executors.newCachedThreadPool();
	}
	
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		for(int i = 0; i < ballCnt; i++){
			g.setColor(ballColor[i]);
			g.fillOval(X[i]-radius, Y[i]-radius, 2*radius, 2*radius);
		}
	}
	
	private class MouseHandler extends MouseAdapter
	{
		//generator new ball when mouse clicks
		@Override
		public void mouseClicked(MouseEvent event)
		{
			X[ballCnt] = event.getX()-radius;
			Y[ballCnt] = event.getY()-radius;
			ballColor[ballCnt] = new Color(generator.nextInt(255),generator.nextInt(255),generator.nextInt(255));
			ballThreads[ballCnt] = new Ball(ballCnt);
			executorService.execute(ballThreads[ballCnt]);	//add new ball thread
			ballCnt++;
		}	
	}
	
	public class Ball implements Runnable
	{
		private int ballNum;
		private int dx;
		private int dy;
		
		public Ball(int b)
		{
			ballNum = b;
			dx = 4;
			dy = 3;
		}
		
		public void run()
		{
			while(true){ 
				X[ballNum] = X[ballNum] + dx;
				Y[ballNum] = Y[ballNum] + dy;
 
				if(X[ballNum] - radius < 0) {
					dx = -dx; 
					X[ballNum] = radius; 
				}else if (X[ballNum] + radius > 900) {
					dx = -dx;
					X[ballNum] = 900 - radius;
				}
 
				if(Y[ballNum] - radius < 0) {
					dy = -dy;
					Y[ballNum] = radius;
				}else if (Y[ballNum] + radius > 900) {
					dy = -dy;
					Y[ballNum] = 900 - radius;
				}
				repaint();
 
				try {
					Thread.sleep(30);
				}catch(InterruptedException ex) {
				}
 
			}
		}
	}
	
	
}