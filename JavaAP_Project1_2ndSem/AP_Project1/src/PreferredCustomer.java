/**
 * Program: PreferredCustomer
 * Purpose: This will be our very own 'HELPER' or 'UTILITY' class which will just hold some useful methods that we can call to do things for us
 * METHOD PHILOSOPHY: a method should just do one thing, but it do it very well
 * Author: Agnita Paul
 * Date: 29th june, 2021 
 */
//•	PreferredCustomer is a subclass of RetailCustomer 
public class PreferredCustomer extends RetailCustomer{
	
	private int cashbackRate;

	//•	There is one 5-arg constructor
	public PreferredCustomer(String firstName, String lastName, String customerLevel,double totalPurchases,int cashbackRate) {
		super(firstName, lastName, customerLevel,totalPurchases);
		this.cashbackRate=cashbackRate;
	}

	//•	Implement incentives() 
	@Override
	public double incentives() {

		double rate;
		//Convert discount rate to a double. 
		rate=(double)cashbackRate/100;
		double discountIncentive=super.incentives();
		// multiplying the cashback rate by the incentive earned by a Retail Customer. 
		double newDiscount=discountIncentive+(discountIncentive*rate);		
		return newDiscount;
	}


	public int getCashbackRate() {
		return cashbackRate;
	}

	public void setCashbackRate(int cashbackRate) {
		this.cashbackRate = cashbackRate;
	}
	
	/**
	  *Method Name: toString()
	  *Purpose: to get a output
	  *Accepts: nothing
	  *Returns: a String value
	  */
	public String toString() {
		return String.format("%s"
				+"Cashback Rate:        %d%%\n",
				super.toString(),this.cashbackRate);
	}
	

}
