
/**
 * Class Name:	EmptyOperandException.java	
 * Purpose:	Exception class to avoid an empty operand to be used in functions		
 * Coder: Ygor Lopez de Rezende			
 * Date: April 14 2021			
*/
public class EmptyOperandException extends Exception
{

	private static final long serialVersionUID = 1L;
	
	EmptyOperandException()
	{
		super("Empty operand!");
	}

}
