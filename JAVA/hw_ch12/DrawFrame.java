 import java.awt.Color;
 import javax.swing.JFrame;
 import javax.swing.JPanel;
 import javax.swing.JLabel;
 import javax.swing.JButton; 
 import java.awt.event.ActionListener;
 import java.awt.event.ActionEvent; 
 import java.awt.BorderLayout;
 import javax.swing.JScrollPane; 
 import javax.swing.JList;
 import javax.swing.event.ListSelectionListener; 
 import javax.swing.event.ListSelectionEvent; 
 import javax.swing.ListSelectionModel; 
 import java.awt.event.ItemListener;
 import java.awt.event.ItemEvent; 
 import javax.swing.JCheckBox;
 import java.awt.FlowLayout;
 
 public class DrawFrame extends JFrame
 {
	private JLabel statusBar;
	private DrawPanel drawPanel;
	private ComponentPanel cPanel;
	
	private JButton undoButton;
	private JButton clearButton;
	
	private JList colorList;
	private JList shapeList;
	private static final String[] colorNames = { "Black", "Blue", "Cyan", "Dark Gray", "Gray", "Green", "Light Gray", "Magenta",  "Orange", "Pink", "Red", "White", "Yellow" }; 
	private static final Color[] colors = { Color.BLACK, Color.BLUE, Color.CYAN, Color.DARK_GRAY, Color.GRAY, Color.GREEN, Color.LIGHT_GRAY, Color.MAGENTA, Color.ORANGE, Color.PINK, Color.RED, Color.WHITE, Color.YELLOW };
	private static final String[] shapeNames = {"Line", "Oval", "Rectangle"};
	private static final int[] shapes = {1, 2, 3};
	
	private JCheckBox fillCheckBox;
	
	//constructor
	public DrawFrame()
	{
		super("Chapter 12 Homework"); 

		statusBar = new JLabel();
		add(statusBar, BorderLayout.SOUTH);
		
		drawPanel = new DrawPanel(statusBar);
		add(drawPanel, BorderLayout.CENTER);
		
		cPanel = new ComponentPanel();
		add(cPanel, BorderLayout.NORTH);
	}
	
	//inner class : component panel on the top
	private class ComponentPanel extends JPanel
	{
		ComponentPanel()
		{
			setLayout(new FlowLayout());
		
			//Button
			undoButton = new JButton("Undo");
			add(undoButton);
			UndoButtonHandler ubHandler = new UndoButtonHandler();
			undoButton.addActionListener(ubHandler);
		
			clearButton = new JButton("Clear");
			add(clearButton);
			ClearButtonHandler cbHandler = new ClearButtonHandler();
			clearButton.addActionListener(cbHandler);
		
			//List
			colorList = new JList(colorNames);
			colorList.setVisibleRowCount( 5 );
			colorList.setSelectionMode( ListSelectionModel.SINGLE_SELECTION );
			add(new JScrollPane(colorList));
			colorList.addListSelectionListener(
				new ListSelectionListener()
				{
					public void valueChanged(ListSelectionEvent event)
					{
						drawPanel.setCurrentColor(colors[colorList.getSelectedIndex()]);
					}
				}
			);
		
			shapeList = new JList(shapeNames);
			shapeList.setVisibleRowCount( 3 );
			shapeList.setSelectionMode( ListSelectionModel.SINGLE_SELECTION );
			add(new JScrollPane(shapeList));
			shapeList.addListSelectionListener(
				new ListSelectionListener()
				{
					public void valueChanged(ListSelectionEvent event)
					{
					drawPanel.setShapeType(shapes[shapeList.getSelectedIndex()]);
					}
				}
			);
		
			//check box
			fillCheckBox = new JCheckBox("Filled");
			add(fillCheckBox);
			CheckBoxHandler cboxHandler = new CheckBoxHandler();
			fillCheckBox.addItemListener(cboxHandler);
		}
	}
	
	//undo button event handling
	private class UndoButtonHandler implements ActionListener
	{
		public void actionPerformed(ActionEvent event)
		{
			drawPanel.clearLastShape();
		}
	}
	
	//clear buttom event handling
	private class ClearButtonHandler implements ActionListener
	{
		public void actionPerformed(ActionEvent event)
		{
			drawPanel.clearDrawing();
		}
	}
	 
	//check box handler
	private class CheckBoxHandler implements ItemListener
	{
		public void itemStateChanged(ItemEvent event)
		{
			if(fillCheckBox.isSelected()){
				drawPanel.setFilledShape(true);
			}else{
				drawPanel.setFilledShape(false);
			}
		}
	}
 }