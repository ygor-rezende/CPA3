/**
	 * Class Name:	BusinessCustomer.java	
	 * Purpose:	Subclass of Customer and represents a customer who has an associated company.
	 * @author Ygor Lopez de Rezende		
	 * Date:  Mar 10 2021		
*/
public class BusinessCustomer extends Customer
{
	// fields declaration
	private String companyName;
	private int discountRate;
	private double totalPurchases;
	
	
	/**
	 * Constructs a Business Customer with 6 parameters
	 * @param firstName The customer first name
	 * @param lastName The customer last name
	 * @param customerLevel The customer level: Business, Retail or Preferred
	 * @param companyName The company name
	 * @param discountRate The discount rate
	 * @param totalPurchases The total amount of purchases
	 */
	public BusinessCustomer(String firstName, String lastName, String customerLevel, String companyName,
			int discountRate, double totalPurchases)
	{
		super(firstName, lastName, customerLevel);
		this.companyName = companyName;
		this.discountRate = discountRate;
		this.totalPurchases = totalPurchases;
	}//end constructor
	

	/**
	 * 
	 * @return The company name
	 */
	public String getCompanyName()
	{
		return companyName;
	}//end method
	

	/**
	 * 
	 * @param companyName The company name to set
	 */
	public void setCompanyName(String companyName)
	{
		this.companyName = companyName;
	}//end method
	

	/**
	 * 
	 * @return The discount rate
	 */
	public int getDiscountRate()
	{
		return discountRate;
	}//end method
	

	/**
	 * 
	 * @param discountRate The discount rate to set
	 */
	public void setDiscountRate(int discountRate)
	{
		this.discountRate = discountRate;
	}//end method
	

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
	

	@Override
	/**
	*Method Name: incentives()
	*Purpose: calculates the incentives to business customers
	*Accepts: nothing
	*@return A double with the value of the incentive
	*/
	public double incentives()
	{
		// incentive = discount rate * total purchases
		return ((double)discountRate/100) * totalPurchases;
	}//end method


	@Override
	public String toString()
	{
		
		return super.toString() + "\n" + getCustomerLevel() + " Customer for " + companyName + "\nTotal Purchases:\t" +
		money.format(totalPurchases) + "\nDiscount Rate:\t\t" + discountRate + "%\nDiscount Incentive:\t" + money.format(incentives()) + 
				"\nNet Purchases:\t\t" + money.format((totalPurchases - incentives()));
	}//end method
	

}//end class
