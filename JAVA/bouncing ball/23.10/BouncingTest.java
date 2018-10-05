import javax.swing.JFrame;

public class BouncingTest
{
	public static void main(String[] args)
	{
		JFrame.setDefaultLookAndFeelDecorated(true);
		JFrame frame = new JFrame("Bouncing Ball");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(900, 930);
		frame.setContentPane(new BouncingPanel());
		frame.setVisible(true);
	}

}