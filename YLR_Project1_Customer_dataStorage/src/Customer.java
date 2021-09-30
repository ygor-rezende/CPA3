import java.text.DecimalFormat;

/**
	 * Name: Customer.java	
	 * Purpose: Abstract Superclass which holds fields and methods that are common to all customer subclasses. 
	 * 			All customers have a first and last name and a customerID and a customerLevel.
	 * @author Ygor Lopez de Rezende
	 * Date: Mar 10 2021	
*/
public abstract class Customer
{
	//fields declaration
	private String firstName;
	private String lastName;
	private String customerID;
	private String customerLevel;
	DecimalFormat money = new DecimalFormat("$#,###.00");
	
	
	/**
	 * Constructs a Customer with 3 parameters
	 * @param firstName The customer first name
	 * @param lastName The customer last name
	 * @param customerLevel The customer level: Business, Retail or Preferred
	 */
	public Customer(String firstName, String lastName, String customerLevel)
	{
		super();
		this.firstName = firstName;
		this.lastName = lastName;
		this.customerLevel = customerLevel;
		setCustomerID();
	}//end constructor

	
	/**
	 * 
	 * @return the First Name
	 */
	public String getFirstName()
	{
		return firstName;
	}//end method
	
	
	/**
	 * 
	 * @param firstName the First Name to set
	 */
	public void setFirstName(String firstName)
	{
		this.firstName = firstName;
	}//end method

	
	/**
	 * 
	 * @return the Last Name
	 */
	public String getLastName()
	{
		return lastName;
	}//end method

	
	/**
	 * 
	 * @param lastName the Last Name to set
	 */
	public void setLastName(String lastName)
	{
		this.lastName = lastName;
	}//end method

	
	/**
	 * 
	 * @return the Customer ID
	 */
	public String getCustomerID()
	{
		return customerID;
	}//end method
	
	
	//Creates the customerID based on the first 4-char of last name and 5 random digits
	private void setCustomerID()
	{
		int rand = 0;
		String id = "";
		for(int i = 0; i < 5; ++i) 
		{
			rand = (int)(Math.random() * 10);
			id += rand;
		}
		int len = lastName.length();
		if (len < 4) 
		{
			customerID = lastName.substring(0, len).toUpperCase();
		}
		else
		{
			customerID = lastName.substring(0, 4).toUpperCase();
		}
		//add 'X' up to len is = 4
		while(len < 4) 
		{
			customerID += "X";
			len++;
		}
		customerID += "-" + id;
	}//end method

	
	/**
	 * 
	 * @return the Customer Level
	 */
	public String getCustomerLevel()
	{
		return customerLevel;
	}//end method

	
	/**
	 * 
	 * @param customerLevel the Customer Level to set
	 */
	public void setCustomerLevel(String customerLevel)
	{
		this.customerLevel = customerLevel;
	}//end method
	
	
	/**
	*Method Name: incentives()
	*Purpose: calculates the incentives to customers
	*Accepts: nothing
	*@return A double with the value of the incentive
	*/
	public abstract double incentives();

	
	@Override
	/**
	*@return a String with Customer ID, First Name and Last Name
	*/
	public String toString()
	{
		return customerID + ", " + firstName + " " + lastName;
	}//end method
	
	
}//end class
