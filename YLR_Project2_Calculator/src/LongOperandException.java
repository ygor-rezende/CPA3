
/**
 * Class Name:	EmptyOperandException.java	
 * Purpose:	Exception class to avoid the operand to be longer than 21 digits (limit of display).		
 * Coder: Ygor Lopez de Rezende			
 * Date: April 14 2021			
*/
public class LongOperandException extends Exception
{

	private static final long serialVersionUID = 1L;
	
	LongOperandException()
	{
		super("Too many digits! Maximum = 21.");
	}

}
