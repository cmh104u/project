import javax.swing.JFrame;

public class Test
{ 
	public static void main(String[] args)
	{
		DrawFrame drawFrame = new DrawFrame();
		drawFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		drawFrame.setSize(1000, 1000);
		drawFrame.setVisible(true);
	}
}
