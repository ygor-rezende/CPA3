import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * Class Name:	GUICalculator.java	
 * Purpose:	Class to build the user interface of the calculator		
 * Coder: Ygor Lopez de Rezende			
 * Date: April 14 2021			
*/
public class GUICalculator extends JFrame implements ActionListener
{
	private static final long serialVersionUID = 1L;
	// references to calculator creation
	Calculator myCalc;
	JPanel btnPanel;
	JTextField display;
	JButton clear, backspace, percent, signal, square, sqrt, blank1, divisor, seven, eight, nine, prod, four, 
	five, six, minus, one, two, three, plus, blank2, zero, point, equal;
	JMenuBar bar;
	JMenu file, convert, help;
	JMenuItem exit, hex, dec, oct, bin, how, about;
	boolean opClicked = false;
	boolean resultOnDisplay = false;
	boolean flagMinus = false;
	
	GUICalculator()
	{
		super("Calculator");
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setSize(300, 365);
		this.setResizable(false);
		this.setLocationRelativeTo(null);
		this.setLayout(new BorderLayout());
		myCalc = new Calculator();
		
		//font creation
		Font mainFont = new Font(Font.SANS_SERIF, Font.PLAIN, 22);
		
		//display creation
		display = new JTextField();
		display.setFont(mainFont);
		display.setEditable(false);
		display.setText("0.0");
		display.setBackground(Color.white);
		display.setHorizontalAlignment(JTextField.RIGHT);
		display.setBorder(BorderFactory.createLineBorder(Color.black, 1));
		
		
		//JPanel and buttons creation
		btnPanel = new JPanel(new GridLayout(6, 4, 5, 5));
		clear = new JButton("C");
		backspace = new JButton("\u232b");
		percent = new JButton("%");
		signal = new JButton("+/-");
		square = new JButton("X\u00b2");
		sqrt = new JButton("\u221a");
		blank1 = new JButton("");
		divisor = new JButton("/");
		seven = new JButton("7");
		eight = new JButton("8");
		nine = new JButton("9");
		prod = new JButton("X");
		four = new JButton("4");
		five = new JButton("5");
		six = new JButton("6");
		minus = new JButton("-");
		one = new JButton("1");
		two = new JButton("2");
		three = new JButton("3");
		plus = new JButton("+");
		blank2 = new JButton("");
		zero = new JButton("0");
		point = new JButton(".");
		equal = new JButton("=");
	
		//setting buttons font
		clear.setFont(mainFont);
		backspace.setFont(mainFont);
		percent.setFont(mainFont);
		signal.setFont(mainFont);
		square.setFont(mainFont);
		sqrt.setFont(mainFont);
		divisor.setFont(mainFont);
		seven.setFont(mainFont);
		eight.setFont(mainFont);
		nine.setFont(mainFont);
		prod.setFont(mainFont);
		four.setFont(mainFont);
		five.setFont(mainFont);
		six.setFont(mainFont);
		minus.setFont(mainFont);
		one.setFont(mainFont);
		two.setFont(mainFont);
		three.setFont(mainFont);
		plus.setFont(mainFont);
		zero.setFont(mainFont);
		point.setFont(mainFont);
		equal.setFont(mainFont);
		
		//adding action listener to buttons
		clear.addActionListener(this);
		backspace.addActionListener(this);
		percent.addActionListener(this);
		signal.addActionListener(this);
		square.addActionListener(this);
		sqrt.addActionListener(this);
		divisor.addActionListener(this);
		seven.addActionListener(this);
		eight.addActionListener(this);
		nine.addActionListener(this);
		prod.addActionListener(this);
		four.addActionListener(this);
		five.addActionListener(this);
		six.addActionListener(this);
		minus.addActionListener(this);
		one.addActionListener(this);
		two.addActionListener(this);
		three.addActionListener(this);
		plus.addActionListener(this);
		zero.addActionListener(this);
		point.addActionListener(this);
		equal.addActionListener(this);
		
		//adding buttons to JPanel
		btnPanel.add(clear);
		btnPanel.add(backspace);
		btnPanel.add(percent);
		btnPanel.add(signal);
		btnPanel.add(square);
		btnPanel.add(sqrt);
		btnPanel.add(blank1);
		btnPanel.add(divisor);
		btnPanel.add(seven);
		btnPanel.add(eight);
		btnPanel.add(nine);
		btnPanel.add(prod);
		btnPanel.add(four);
		btnPanel.add(five);
		btnPanel.add(six);
		btnPanel.add(minus);
		btnPanel.add(one);
		btnPanel.add(two);
		btnPanel.add(three);
		btnPanel.add(plus);
		btnPanel.add(blank2);
		btnPanel.add(zero);
		btnPanel.add(point);
		btnPanel.add(equal);
		
		//Menu creation
		bar = new JMenuBar();
		file = new JMenu("File");
		convert = new JMenu("Convert");
		help = new JMenu("Help");
		exit = new JMenuItem("Exit");
		hex = new JMenuItem("Hex");
		dec = new JMenuItem("Dec");
		oct = new JMenuItem("Oct");
		bin = new JMenuItem("Bin");
		how = new JMenuItem("How to use");
		about = new JMenuItem("About");
		
		// adding action listeners to menu items
		exit.addActionListener(this);
		hex.addActionListener(this);
		dec.addActionListener(this);
		oct.addActionListener(this);
		bin.addActionListener(this);
		how.addActionListener(this);
		about.addActionListener(this);
		
		//grouping menu items
		file.add(exit);
		convert.add(hex);
		convert.add(dec);
		convert.add(oct);
		convert.add(bin);
		help.add(how);
		help.add(about);
		
		//adding menu groups to bar
		bar.add(file);
		bar.add(convert);
		bar.add(help);
		
		//setting bar to JFrame
		setJMenuBar(bar);
	
		//adding display and panel to Frame
		this.add(display, BorderLayout.NORTH);
		this.add(btnPanel, BorderLayout.CENTER);
		
		this.setVisible(true);
	}
	
	
	// main method to create the GUI calculator
	public static void main(String[] args)
	{
		new GUICalculator();

	}//end main


	
	@Override
	public void actionPerformed(ActionEvent e)
	{
		Object source = e.getSource();
		String result = "";
		
		//clear
		if(source.equals(clear)) 
		{
			myCalc.clear();
			display.setText("0.0");
		}
		//backspace
		else if(source.equals(backspace))
		{
			try 
			{
				myCalc.setOperand(myCalc.backspace(myCalc.getOperand()));
				display.setText(myCalc.backspace(display.getText()));
			}
			catch (EmptyOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
				display.setText("0.0");
			}
		}
		//find percentage
		else if(source.equals(percent))
		{
			try
			{
				display.setText(myCalc.findPercentage(myCalc.getOperand()));
				resultOnDisplay = true;
			}
			catch (EmptyOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}

		}
		// signal +/-
		else if(source.equals(signal))
		{
			try
			{
				if (flagMinus)
				{
					display.setText(myCalc.toogglePlusMinus(false));
					flagMinus = false;
				}

				else
				{
					display.setText(myCalc.toogglePlusMinus(true));
					flagMinus = true;
				}
					
			}
			catch (EmptyOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
			
		}
		// squared
		else if(source.equals(square))
		{
			try
			{
				display.setText(myCalc.findSquared(myCalc.getOperand()));
				resultOnDisplay = true;
				flagMinus = false;
			}
			catch (EmptyOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
			
		}
		// square root
		else if(source.equals(sqrt))
		{
			try
			{
				display.setText(myCalc.findSquareRoot(myCalc.getOperand()));
				resultOnDisplay = true;
			}
			catch (EmptyOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		}
		// divisor
		else if(source.equals(divisor))
		{
			if(!opClicked) 
			{
				try 
				{
					myCalc.buildExpression(divisor.getText());
					opClicked = true;
				}
				catch (EmptyOperandException ex)
				{
					JOptionPane.showMessageDialog(null, ex.getMessage());
				}
			}
		}
		// button 7
		else if(source.equals(seven))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			try
			{
				myCalc.buildOperand(seven.getText());
				display.setText(myCalc.getOperand());
				resetOperator();
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		
		}
		// button 8
		else if(source.equals(eight))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			try
			{
				myCalc.buildOperand(eight.getText());
				display.setText(myCalc.getOperand());
				resetOperator();	
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
			
		}
		// button 9
		else if(source.equals(nine))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			try
			{
				myCalc.buildOperand(nine.getText());
				display.setText(myCalc.getOperand());
				resetOperator();
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		
		}
		// product
		else if(source.equals(prod))
		{
			if(!opClicked) 
			{
				try 
				{
					myCalc.buildExpression(prod.getText());
					opClicked = true;
				}
				catch (EmptyOperandException ex)
				{
					JOptionPane.showMessageDialog(null, ex.getMessage());
				}
			}
		}
		// button 4
		else if(source.equals(four))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			try
			{
				myCalc.buildOperand(four.getText());
				display.setText(myCalc.getOperand());
				resetOperator();
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		}
		// button 5
		else if(source.equals(five))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			try
			{
				myCalc.buildOperand(five.getText());
				display.setText(myCalc.getOperand());
				resetOperator();
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		}
		// button 6
		else if(source.equals(six))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			try
			{
				myCalc.buildOperand(six.getText());
				display.setText(myCalc.getOperand());
				resetOperator();
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		}
		// minus
		else if(source.equals(minus))
		{
			if(!opClicked) 
			{
				try
				{
					myCalc.buildExpression(minus.getText());
					opClicked = true;
				}
				catch (EmptyOperandException ex)
				{
					JOptionPane.showMessageDialog(null, ex.getMessage());
				}

			}
		}
		// button 1
		else if(source.equals(one))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			try
			{
				myCalc.buildOperand(one.getText());
				display.setText(myCalc.getOperand());
				resetOperator();
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
			
		}
		// button 2
		else if(source.equals(two))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			
			try
			{
				myCalc.buildOperand(two.getText());
				display.setText(myCalc.getOperand());
				resetOperator();
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
			
		}
		// button 3
		else if(source.equals(three))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			try
			{
				myCalc.buildOperand(three.getText());
				display.setText(myCalc.getOperand());
				resetOperator();
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		
		}
		// plus
		else if(source.equals(plus))
		{
			if(!opClicked) 
			{
				try
				{
					myCalc.buildExpression(plus.getText());
					opClicked = true;
				}
				catch (EmptyOperandException ex)
				{
					JOptionPane.showMessageDialog(null, ex.getMessage());
				}
			}
		}
		// button 0
		else if(source.equals(zero))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			try
			{
				myCalc.buildOperand(zero.getText());
				display.setText(myCalc.getOperand());
				resetOperator();
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		}
		// point
		else if(source.equals(point))
		{
			if (resultOnDisplay && !opClicked)
			{
				myCalc.clear();
				flagMinus = false;
			}
			if(!myCalc.isDecimalPressed()) 
			{
				try
				{
					myCalc.buildOperand(point.getText());
					display.setText(myCalc.getOperand());
					myCalc.setDecimalPressed(true);
					resetOperator();
				}
				catch (LongOperandException ex)
				{
					JOptionPane.showMessageDialog(null, ex.getMessage());
				}
				
			}
		}
		// equal button
		else if(source.equals(equal))
		{
			try
			{
				result = String.valueOf(myCalc.calculate());
				myCalc.buildOperand(result);
				display.setText(result);
				if(result.charAt(0) == '-')
					flagMinus = true;
				else
					flagMinus = false;
				resetOperator();
				resultOnDisplay = true;
			}
			catch (ArithmeticException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
				myCalc.clear();
				display.setText("0.0");
			}
			catch (EmptyOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
			
		}
		
		// Menu options
		// Exit
		else if(source.equals(exit))
		{
			this.dispose();
		}
		
		//Hexadecimal
		else if(source.equals(hex))
		{
			try
			{
				display.setText(myCalc.convertHex(myCalc.getOperand()));
			}
			catch (EmptyOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		}
		
		//Decimal
		else if(source.equals(dec))
		{
			if (myCalc.getOperand().length() > 0)
				display.setText(myCalc.getOperand());
		}
		
		//Octal
		else if(source.equals(oct))
		{
			try
			{
				display.setText(myCalc.convertOct(myCalc.getOperand()));
			}
			catch (EmptyOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		}
		
		//Binary
		else if(source.equals(bin))
		{
			try
			{
				display.setText(myCalc.convertBin(myCalc.getOperand()));
			}
			catch (EmptyOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
			catch (LongOperandException ex)
			{
				JOptionPane.showMessageDialog(null, ex.getMessage());
			}
		}
		
		// How to use
		else if(source.equals(how))
		{
			JOptionPane.showMessageDialog(null, "Four basic operations:\n"
					+ "'+' addition, '-' subtraction, 'X' multiplication, '/' division.\n"
					+ "This calculator folows the rules of BEDMAS (multiplication and division are calculated first than addition and subtraction).\n"
					+ "The 'C' button clears the fields.\n"
					+ "'\u232b' delete the last digit.\n"
					+ "'%' calculates the current value divided by 100.\n"
					+ "'+/-' toogles the signal of the current value.\n"
					+ "'X\u00b2' squares the current value displayed.\n"
					+ "'\u221a' calculates the square root of the current value.", "How to Use", JOptionPane.INFORMATION_MESSAGE);
		}
		
		// About
		else if(source.equals(about))
		{
			JOptionPane.showMessageDialog(null, "Calculator, Vesion 1.0.\nCopyright: Ygor L. de Rezende, 2021 \nAll rights reserved.", "About", JOptionPane.INFORMATION_MESSAGE);
		}
		
	}//end actionPerformed
	
	/*Method Name: resetOperator()
	*Purpose: Resets opClicked and resultOnDisplay flags to false.
	*Accepts: nothing
	*Returns: nothing
	*/
	private void resetOperator() 
	{
		opClicked = false;
		resultOnDisplay = false;
	}//end method

}//end class
