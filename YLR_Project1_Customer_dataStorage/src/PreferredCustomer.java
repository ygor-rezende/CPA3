/**
	 * Class Name:	PreferredCustomer.java	
	 * Purpose:	Subclass of RetailCustomer and represents a customer with cashback privileges.
	 * @author Ygor Lopez de Rezende		
	 * Date:  Mar 10 2021		
*/
public class PreferredCustomer extends RetailCustomer
{
	//fields
	private int cashbackRate;

	/**
	 * Constructs a Preferred Customer with 5 parameters
	 * @param firstName The customer first name
	 * @param lastName The customer last name
	 * @param customerLevel The customer level: Business, Retail or Preferred
	 * @param totalPurchases The total amount of purchases
	 * @param cashbackRate The cash-back rate
	 */
	public PreferredCustomer(String firstName, String lastName, String customerLevel, double totalPurchases,
			int cashbackRate)
	{
		super(firstName, lastName, customerLevel, totalPurchases);
		this.cashbackRate = cashbackRate;
	}//end constructor
	
	/**
	 * 
	 * @return The cash-back rate
	 */
	public int getCashbackRate()
	{
		return cashbackRate;
	}//end method
	

	/**
	 * 
	 * @param cashbackRate The cash-back rate to set
	 */
	public void setCashbackRate(int cashbackRate)
	{
		this.cashbackRate = cashbackRate;
	}//end method
	
	
	@Override
	/**
	*Method Name: incentives()
	*Purpose: calculates the incentives to preferred customers
	*Accepts: nothing
	*@return A double with the value of the incentive
	*/
	public double incentives()
	{
		// incentive = cashback rate * retail customer incentive + retail customer incentive 
		return ((double)cashbackRate/100) * super.incentives() + super.incentives();
	}//end method
	
	
	@Override
	public String toString()
	{
		return getCustomerID() +", " + getFirstName() + " " + getLastName() + "\n" + getCustomerLevel() + " Customer" + "\nTotal Purchases:\t"
				+ money.format(getTotalPurchases()) + "\nDiscount Rate:\t\t" + findDiscountRate() + "%\nDiscount Incentive:\t"
				+ money.format(incentives()) + "\nNet Purchases:\t\t" + money.format((getTotalPurchases() - incentives())) 
				+ "\nCashback Rate:\t\t" + cashbackRate + "%";
	}//end method
	
	
}//end class
