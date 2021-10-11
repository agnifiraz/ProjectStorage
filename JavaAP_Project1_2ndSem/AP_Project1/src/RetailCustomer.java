/**
 * Program: RetailCustomer
 * Purpose: This will be our very own 'HELPER' or 'UTILITY' class which will just hold some useful methods that we can call to do things for us
 * METHOD PHILOSOPHY: a method should just do one thing, but it do it very well
 * Author: Agnita Paul
 * Date: 29th june, 2021 
 */
//•	RetailCustomer is a subclass of Customer 
public class RetailCustomer extends Customer{
	
	private double totalPurchases;

	//•	There is one 4-arg constructor
	public RetailCustomer(String firstName, String lastName, String customerLevel,double totalPurchases) {
		super(firstName, lastName, customerLevel);
		this.totalPurchases=totalPurchases;
	}

	
	/**
	  *Method Name: findDiscountRate()
	  *Purpose: determines the discount rate based on total purchases: 
	  *Accepts: nothing
	  *Returns: a int value
	  */
	public int findDiscountRate() {
		int rate;
		if(this.totalPurchases>10000) {
			rate=15;
		}
		else if(this.totalPurchases>5000) {
			rate=10;

		}
		else {
			rate=5;

		}
		return rate;
	}
	public double getTotalPurchases() {
		return totalPurchases;
	}

	public void setTotalPurchases(double totalPurchases) {
		this.totalPurchases = totalPurchases;
	}

	//•	Implement incentives()     
	@Override
	public double incentives() {
		//Call findDiscountRate() to determine the discount rate.
        int rate= findDiscountRate();
        //Convert discount rate to a double
        double doubleRate=(double)rate/100;
        //multiplying total purchases by discount rate.
		return this.totalPurchases*doubleRate;
	}
	
	/**
	  *Method Name: toString()
	  *Purpose: to get a output
	  *Accepts: nothing
	  *Returns: a String value
	  */
	public String toString() {
		return String.format("%s\n"
				+"Total Purchases:      $%.2f\n"
				+"Discount Rate:        %d%%\n"
				+"Discount Incentive:   $%.2f\n"
				+"Net Purchases:        $%.2f\n",
				super.toString(),this.totalPurchases,this.findDiscountRate(),this.incentives(),(this.totalPurchases-this.incentives()));
		
	}
	
}
