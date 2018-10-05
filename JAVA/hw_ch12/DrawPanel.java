import javax.swing.JPanel;
import javax.swing.JLabel;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Graphics;

public class DrawPanel extends JPanel
{
	private final int SHAPE_MAX_CNT = 100;
	private final int LINE = 1;
	private final int OVAL = 2;
	private final int RECTANGLE = 3;
	
	private MyShape[] shapes;
	private int shapeCount;
	private int shapeType;
	private MyShape currentShape;
	private Color currentColor;
	private boolean filledShape;
	private JLabel statusLabel;

	public DrawPanel(JLabel label)
	{
		statusLabel = label;
		
		//initialize
		shapes = new MyShape[SHAPE_MAX_CNT];
		shapeCount = 0;
		shapeType = LINE;
		currentShape = null;
		currentColor = Color.BLACK;
		filledShape = false;
		setBackground(Color.WHITE);
		
		//register
		MouseHandler handler = new MouseHandler();
		addMouseListener(handler);
		addMouseMotionListener(handler);
	}
	
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		for(int i = 1; i <= shapeCount; i++)
		{
			shapes[i].draw(g);
		}
		
	}
	
	public void setShapeType(int ST)
	{
		shapeType = ST;
	}
	
	public void setCurrentColor(Color color)
	{
		currentColor = color;
	}
	
	public void setFilledShape(boolean f)
	{
		filledShape = f;
	}
	
	public void clearLastShape()
	{
		shapeCount--;
		repaint();
	}
	
	public void clearDrawing()
	{
		shapeCount = 0;
		repaint();
	}
	
	private class MouseHandler extends MouseAdapter implements MouseMotionListener
	{
		@Override
		public void mousePressed(MouseEvent event)
		{
			if(shapeType == 1){
				currentShape = new MyLine(event.getX(), event.getY(), event.getX(), event.getY(), currentColor);
			}else if(shapeType == 2){
				currentShape = new MyOval(event.getX(), event.getY(), event.getX(), event.getY(), currentColor, filledShape);
			}else if(shapeType == 3){
				currentShape = new MyRectangle(event.getX(), event.getY(), event.getX(), event.getY(), currentColor, filledShape);
			}
			shapeCount++;
		}
		
		@Override
		public void mouseReleased(MouseEvent event)
		{
			currentShape.setY1(event.getX());
			currentShape.setY2(event.getY());
			shapes[shapeCount] = currentShape;
			repaint();
		}
		
		@Override
		public void mouseMoved(MouseEvent event)
		{
			statusLabel.setText("(" + event.getX() + "," + event.getY() + ")");
		}
		
		@Override
		public void mouseDragged(MouseEvent event)
		{
			statusLabel.setText("(" + event.getX() + "," + event.getY() + ")");
			currentShape.setY1(event.getX());
			currentShape.setY2(event.getY());
			shapes[shapeCount] = currentShape;
			repaint();
		}
		

	}
	
}