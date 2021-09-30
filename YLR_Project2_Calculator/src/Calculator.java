import java.math.BigInteger;
import java.util.ArrayList;

/**
 * Class Name:	Calculator.java	
 * Purpose:	Base class with properties and methods to build a calculator object		
 * Coder: Ygor Lopez de Rezende			
 * Date: April 14 2021			
*/
public class Calculator
{
	private String operand;
	private String operator;
	private boolean decimalPressed;
	private ArrayList<String> list = new ArrayList<String>();
	
	//Default constructor
	public Calculator() 
	{
		operand = "";
		operator = "";
		decimalPressed = false;
	}

	//getters and setters
	public String getOperand()
	{
		return operand;
	}

	public void setOperand(String operand)
	{
		this.operand = operand;
	}

	public String getOperator()
	{
		return operator;
	}

	public void setOperator(String operator)
	{
		this.operator = operator;
	}
	
	public boolean isDecimalPressed()
	{
		return decimalPressed;
	}

	public void setDecimalPressed(boolean decimalPressed)
	{
		this.decimalPressed = decimalPressed;
	}
	
	/*Method Name: clear()
	*Purpose: clear fields and list
	*Accepts: Nothing
	*Returns: Nothing
	*/
	public void clear()
	{
		operand = "";
		operator = "";
		decimalPressed = false;
		list.clear();
	}
	
	/*Method Name: backspace()
	*Purpose: Delete the last digit of the value received (throws EmptyOperandException)
	*Accepts: a String with the value to be trimmed
	*Returns: the value received with the last digit removed
	*/
	public String backspace(String value) throws EmptyOperandException
	{
		if(value.length() < 1)	
			throw new EmptyOperandException();
		else
			return value.substring(0, value.length()-1);
	}
	
	/*Method Name: findPercentage()
	*Purpose: calculates the percentage of a value (throws EmptyOperandException)
	*Accepts: a String
	*Returns: A string with the value received as a percentage in decimal format
	*/
	public String findPercentage(String value) throws EmptyOperandException
	{
		if(value.length() < 1)
		{
			throw new EmptyOperandException();
		}
		else 
		{
			operand = String.valueOf((Double.parseDouble(value) / 100));
			return operand;
		}
	}//end method
	
	/*Method Name: toogglePlusMinus()
	*Purpose: Adds or remove the signal “-“ to the beginning of operand (throws EmptyOperandException)
	*Accepts: a boolean
	*Returns: a String with the operand with the signal flipped.
	*/
	public String toogglePlusMinus(boolean flagMinus) throws EmptyOperandException
	{
		if(operand.length() < 1)
		{
			throw new EmptyOperandException();
		}
		else
		{
			if(flagMinus)
			{
				operand = "-" + operand;
				return operand;
			}	
			else 
			{
				operand = operand.substring(1);
				return operand;
			}
		}//end else	
	}//end method
	
	/*Method Name: findSquared()
	*Purpose: Squares a value received (throws EmptyOperandException)
	*Accepts: a String with the value to be squared
	*Returns: a String with the square of the value.
	*/
	public String findSquared(String value) throws EmptyOperandException
	{
		if(value.length() < 1)
		{
			throw new EmptyOperandException();
		}
		else
		{
			operand = String.valueOf(Double.parseDouble(value) * Double.parseDouble(value));
			return operand;
		}
		
	}
	
	/*Method Name: findSquareRoot()
	*Purpose: calculates the square root of a value received (throws EmptyOperandException)
	*Accepts: a String with the value to be root squared
	*Returns: a String with the square root of the value.
	*/
	public String findSquareRoot(String value) throws EmptyOperandException
	{
		if(value.length() < 1)
		{
			throw new EmptyOperandException();
		}
		else
		{
			operand = String.valueOf(Math.sqrt(Double.parseDouble(value)));
			return operand;
		}
	}
	
	/*Method Name: buildOperand()
	*Purpose: Concatenates the operand and the value received (throws LongOperandException)
	*Accepts: a String with the value to be concatenated at the end of the operand
	*Returns: nothing.
	*/
	public void buildOperand(String value) throws LongOperandException
	{
		if (operand.length() > 20)
			throw new LongOperandException();
		else
			operand += value;
	}
	
	/*Method Name: buildExpression()
	*Purpose: Assigns the value received to operator and add operand and operator to the list (throws EmptyOperandException)
	*Accepts: a String with the value to be assigned to operator
	*Returns: nothing.
	*/
	public void buildExpression(String value) throws EmptyOperandException
	{
		if(operand.length() < 1)
		{
			throw new EmptyOperandException();
		}
		else
		{
			operator = value;
			list.add(operand);
			list.add(operator);
			
			// reseting properties
			operator = "";
			operand = "";
			decimalPressed = false;
		}
	}
	
	/*Method Name: calculate()
	*Purpose: calculates the answer of the expression using the operands and operators in 
	*		  the list applying the rules of BEDMAS (throws EmptyOperandException and ArithmeticException)
	*Accepts: nothing.
	*Returns: a double with the answer of the expression.
	*/
	public double calculate() throws EmptyOperandException, ArithmeticException
	{
		double result = 0;
		String op = "";
		if (operand.length() < 1)
		{
			throw new EmptyOperandException();
		}
		else
		{
			list.add(operand);
			for (int i = 0; i < list.size(); i++)
			{
				// The operands are saved on even indexes of 'list' and the operators on odd indexes
				if (i % 2 != 0)
				{
					op = list.get(i);
					if (op.contentEquals("X"))
					{
						result = Double.parseDouble(list.get(i - 1)) * Double.parseDouble(list.get(i + 1));
						// Replace the values and operator with the result
						list.add(i - 1, String.valueOf(result));
						list.remove(i);
						list.remove(i);	
						list.remove(i);
						i = 0; // reseting i to restart the loop
						continue;
					}
					else if(op.contentEquals("/"))
					{
						if(Double.parseDouble(list.get(i + 1)) == 0)
						{
							throw new ArithmeticException("Error! Division by zero.");
						}
						else
						{
							result = Double.parseDouble(list.get(i - 1)) / Double.parseDouble(list.get(i + 1));
							// Replace the values and operator with the result
							list.add(i - 1, String.valueOf(result));
							list.remove(i);
							list.remove(i);	
							list.remove(i);
							i = 0; // reseting i to restart the loop
							continue;
						}
						
					}
				}//end if
			}//end for
			for (int i = 0; i < list.size(); i++)
			{
				op = list.get(i);
				if (i % 2 != 0)
				{
					if(op.contentEquals("+"))
					{
						result = Double.parseDouble(list.get(i - 1)) + Double.parseDouble(list.get(i + 1));
						// Replace the values and operator with the result
						list.add(i - 1, String.valueOf(result));
						list.remove(i);
						list.remove(i);	
						list.remove(i);
						i = 0; // reseting i to restart the loop
						continue;
					}
					else if(op.contentEquals("-"))
					{
						result = Double.parseDouble(list.get(i - 1)) - Double.parseDouble(list.get(i + 1));
						// Replace the values and operator with the result
						list.add(i - 1, String.valueOf(result));
						list.remove(i);
						list.remove(i);	
						list.remove(i);
						i = 0; // reseting i to restart the loop
						continue;
					}
				}
				
			}//end for
			clear();
			return result;
		}//end else (operand not empty)
		
	}//end calculate()
	
	/*Method Name: convertHex()
	*Purpose: Converts a decimal value to hexadecimal (throws EmptyOperandException, LongOperandException)
	*Accepts: a string with the value to be converted.
	*Returns: a string with the value converted.
	*/
	public String convertHex(String value) throws EmptyOperandException, LongOperandException
	{
		if (value.length() < 1)
			throw new EmptyOperandException();
		else
		{
			
			BigInteger val = new BigInteger(String.valueOf(Math.round(Double.parseDouble(value))));
			int rest = 0;
			String hex = "";
			while (val != BigInteger.valueOf(0))
			{
				rest = val.remainder(BigInteger.valueOf(16)).intValue();
				val = val.divide(BigInteger.valueOf(16));
				if(rest < 10)
				{
					hex = String.valueOf(rest) + hex;
				}
				else
				{
					switch(rest)
					{
						case 10: hex = "A" + hex;
							break;
						case 11: hex = "B" + hex;
							break;
						case 12: hex = "C" + hex;
							break;
						case 13: hex = "D" + hex;
							break;
						case 14: hex = "E" + hex;
							break;
						case 15: hex = "F" + hex;
							break;
					}//end switch
				}//end else
			}//end while
			if (hex.length() > 20)
				throw new LongOperandException();
			else
				return hex;
		}
	}// end method
	
	/*Method Name: convertOct()
	*Purpose: Converts a decimal value to octal (throws EmptyOperandException, LongOperandException)
	*Accepts: a string with the value to be converted.
	*Returns: a string with the value converted.
	*/
	public String convertOct(String value) throws EmptyOperandException, LongOperandException
	{
		if (value.length() < 1)
			throw new EmptyOperandException();
		else
		{
			BigInteger val = new BigInteger (String.valueOf(Math.round(Double.parseDouble(value))));
			int rest = 0;
			String oct = "";
			while (val != BigInteger.valueOf(0))
			{
				rest = val.remainder(BigInteger.valueOf(8)).intValue();
				val = val.divide(BigInteger.valueOf(8));
				oct = String.valueOf(rest) + oct;
			}//end while
			if (oct.length() > 20)
				throw new LongOperandException();
			else
				return oct;
		}
		}// end method
		
		/*Method Name: convertBin()
		*Purpose: Converts a decimal value to binary (throws EmptyOperandException, LongOperandException)
		*Accepts: a string with the value to be converted.
		*Returns: a string with the value converted.
		*/
		public String convertBin(String value) throws EmptyOperandException, LongOperandException
		{
			if (value.length() < 1)
				throw new EmptyOperandException();
			else
			{
				BigInteger val = new BigInteger(String.valueOf(Math.round(Double.parseDouble(value))));
				int rest = 0;
				String bin = "";
				while (val != BigInteger.valueOf(0))
				{
					rest = val.remainder(BigInteger.valueOf(2)).intValue();
					val = val.divide(BigInteger.valueOf(2));
					bin = String.valueOf(rest) + bin;
				}//end while
				if (bin.length() > 20)
					throw new LongOperandException();
				else
					return bin;
			}
		
		}// end method

	@Override
	public String toString()
	{
		return "Calculator [operand=" + operand + ", operator=" + operator + ", decimalPressed=" + decimalPressed
				+ ", list=" + list + "]";
	}
	
	
	
}//end class


