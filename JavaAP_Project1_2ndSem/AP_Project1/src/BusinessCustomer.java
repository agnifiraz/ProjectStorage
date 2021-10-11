/**
 * Program: BusinessCustomer
 * Purpose: This will be our very own 'HELPER' or 'UTILITY' class which will just hold some useful methods that we can call to do things for us
 * METHOD PHILOSOPHY: a method should just do one thing, but it do it very well
 * Author: Agnita Paul
 * Date: 29th june, 2021 
 */
//•	BusinessCustomer is a subclass of Customer 
public class BusinessCustomer extends Customer {
	private String companyName;
	private int discountRate;
	private double totalPurchases;

	//•	There is one 6-arg constructor
	public BusinessCustomer(String firstName, String lastName, String customerLevel,String companyName,int discountRate,double totalPurchases) {
		//call super class constructor
		super(firstName, lastName, customerLevel);
		this.companyName=companyName;
		this.discountRate=discountRate;
		this.totalPurchases=totalPurchases;
	}
	
	
	public String getCompanyName() {
		return companyName;
	}
	public void setCompanyName(String companyName) {
		this.companyName = companyName;
	}
	public int getDiscountRate() {
		return discountRate;
	}
	public void setDiscountRate(int discountRate) {
		this.discountRate = discountRate;
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

		//Convert discount rate to a double. 
		double doubleRate=(double)this.discountRate/100;
		//by multiplying total purchases by discount rate.
		return doubleRate*this.totalPurchases;
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
				super.toString(),this.totalPurchases,this.discountRate,this.incentives(),(this.totalPurchases-this.incentives()));
	}
	
		
}
