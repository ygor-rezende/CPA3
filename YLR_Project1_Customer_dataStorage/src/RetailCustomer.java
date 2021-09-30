/**
	 * Class Name:	RetailCustomer.java	
	 * Purpose:	Subclass of Customer and represents a customer who is frequent.
	 * @author Ygor Lopez de Rezende		
	 * Date:  Mar 10 2021		
*/
public class RetailCustomer extends Customer
{
	//fields declaration
	private double totalPurchases;
	
	/**
	 * Constructs a Retail Customer with 4 parameters
	 * @param firstName The customer first name
	 * @param lastName The customer last name
	 * @param customerLevel The customer level: Business, Retail or Preferred
	 * @param totalPurchases The total amount of purchases
	 */
	public RetailCustomer(String firstName, String lastName, String customerLevel, double totalPurchases)
	{
		super(firstName, lastName, customerLevel);
		this.totalPurchases = totalPurchases;
	}//end constructor
	

	/**
	 * 
	 * @return The total amount of purchases
	 */
	public double getTotalPurchases()
	{
		return totalPurchases;
	}//end method
	

	/**
	 * 
	 * @param totalPurchases The total amount of purchases to set
	 */
	public void setTotalPurchases(double totalPurchases)
	{
		this.totalPurchases = totalPurchases;
	}//end method
	

	/**
	*Method Name: findDiscountRate()
	*Purpose: calculates the discount rate based on total purchases amount
	*Accepts: nothing
	*@return A double with the discount rate from 0 to 15
	*/
	public int findDiscountRate()
	{
		if(totalPurchases > 10000)
		{
			return 15;
		}
		else if(totalPurchases > 5000)
		{
			return 10;
		}
		else if(totalPurchases > 1000)
		{
			return 5;
		}
		else
		{
			return 0;
		}
	}//end method
	
	
	@Override
	/**
	*Method Name: incentives()
	*Purpose: calculates the incentives to retail customers
	*Accepts: nothing
	*@return A double with the value of the incentive
	*/
	public double incentives()
	{
		// incentive = discount rate * total purchases
		return ((double)findDiscountRate()/100) * totalPurchases;
	}//end method
	
	
	@Override
	public String toString()
	{
		return super.toString() + "\n" + getCustomerLevel() + " Customer" + "\nTotal Purchases:\t"
				+ money.format(totalPurchases) + "\nDiscount Rate:\t\t" + findDiscountRate() + "%\nDiscount Incentive:\t" + money.format(incentives()) + 
				"\nNet Purchases:\t\t" + money.format((totalPurchases - incentives()));
	}//end method

}//end class
