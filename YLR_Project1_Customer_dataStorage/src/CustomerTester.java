import java.text.DecimalFormat;
import java.util.ArrayList;

/**
 *Program name:	CustomerTester.java
 *Purpose: Tests the Customer classes in this package
 *Coder: Ygor L Rezende
 *Date: Mar 11 2021
 */

public class CustomerTester
{

	public static void main(String[] args)
	{
		//special format to be used when printing currency
		DecimalFormat money = new DecimalFormat("$#,###.00");
		
		//Welcome message
		System.out.println("Welcome to the Customer tester!\n" + 
				"---------------------------------------------------------------------------------------\n" + 
				"This program will instantiate objects of the Customer hierarchy and test their methods\n" + 
				"---------------------------------------------------------------------------------------\n");
		
		// 1. Create an array of type Customer named customerArray and size it to hold 3 customers. 
		ArrayList <Customer> customerArray = new ArrayList<Customer>(3);
		
		//2. Create three Customer objects 
		Customer business1 = new BusinessCustomer("Mike", "Holmes", "Business", "Home Depot", 10, 3105.50);
		Customer retail1 = new RetailCustomer("Dev", "Gelda", "Retail", 11200);
		Customer preferred1 = new PreferredCustomer("Wei", "Ping", "Preferred", 6456.85, 5);
		
		
		//3. Assign each customer object to an element of your Customer array. 
		customerArray.add(business1);
		customerArray.add(retail1);
		customerArray.add(preferred1);
		
		//4. Using a loop, print each object in the array calling the toString() method
		for(int i = 0; i < customerArray.size(); ++i)
		{
			System.out.println(customerArray.get(i).toString());
			System.out.println();//for line space
		}
		
		//5. Use another loop that will print each customer’s full name and the incentives 
		for(Customer a : customerArray) 
		{
			System.out.println(a.getFirstName() + " " + a.getLastName() + " earns a discount incentive of " + money.format(a.incentives()));
		}
		
		System.out.println();//for line space
		
		//6. Create three more Customer objects using the subclasses references
		BusinessCustomer business2 = new BusinessCustomer("Tristan", "Lee", "Business", "Starbucks", 15, 9875.25);
		RetailCustomer retail2 = new RetailCustomer("Carlos", "Beltran", "Retail", 3100.50);
		PreferredCustomer preferred2 = new PreferredCustomer("Arti", "Patel", "Preferred", 10450, 10);
		
		//7. Print each new Customer object calling the toString() method.
		System.out.println(business2.toString());
		System.out.println();//for line space
		System.out.println(retail2.toString());
		System.out.println();//for line space
		System.out.println(preferred2.toString());
		
		//8. Use the setter methods to make the changes to each of the three last customer objects
		business2.setTotalPurchases(8895);
		business2.setDiscountRate(12);
		retail2.setTotalPurchases(100500);
		preferred2.setTotalPurchases(14987.24);
		preferred2.setLastName("Patel-Ruhil");
		preferred2.setCashbackRate(13);
		
		System.out.println();//for line space
		
		//9. print each new Customer object again to show the above changes
		System.out.println(business2.toString());
		System.out.println();//for line space
		System.out.println(retail2.toString());
		System.out.println();//for line space
		System.out.println(preferred2.toString());
		
		
	}//end main

}//end class
