/**
	 * Class Name:	CustomerTester	
	 * Purpose:	This program will instantiate objects of the objects of the Customer hierarchy and test their methods
	 * Coder:	Agnita Paul		
	 * Date:	29th June, 2021		
*/

public class CustomerTester {

	public static void main(String[] args) {

		//write a short description
		System.out.println("Welcome to the Customer tester!");
		System.out.println("-----------------------------------------------------------------------------------------------------");
		System.out.println("This program will instantiate objects of the objects of the Customer hierarchy and test their methods");
		System.out.println("-----------------------------------------------------------------------------------------------------");


		//create an array of type Customer named customerArray and size it to hold 3 customers
		Customer[] customerArray=new Customer[3];

		//	Create three Customer objects as specified instruction
		Customer customer1=new BusinessCustomer("Mike", "Holmes","Business Customer with Home Depot","Home Depot", 10,3105.50);
		Customer customer2=new RetailCustomer("Dev","Gelda","Retail Customer",11200);
		Customer customer3=new PreferredCustomer("Wei","Ping","Preferrent Customer",6456.85,5);
	
		//assign each customer object to an element of Customer array
		customerArray[0]=customer1;
		customerArray[1]=customer2;
		customerArray[2]=customer3;
		
		for(int i=0;i<customerArray.length;i++) {

			//Using a loop, print each object in the array calling the toString() method
			System.out.println(customerArray[i].toString());
			System.out.println();
		}
		
		//Use another loop that will print each customer’s full name and the incentives he/she is entitled to
		for(int i=0;i<customerArray.length;i++) {

			//+" "++" earns a discount incentive of $"+
			System.out.printf("%s %s earns a discount incentive of $%.2f\n",customerArray[i].getFirstName(),customerArray[i].getLastName(),customerArray[i].incentives());
		}
		
		//Create three more Customer objects. For these three objects, do not use superclass reference variables to create the three objects, use their subclass types for the variables.
		BusinessCustomer customerMore1=new BusinessCustomer("Tristan", "Lee","Business Customer with Starbucks","Starbucks", 15,9875.25);
		RetailCustomer customerMore2=new RetailCustomer("Carlos","Beltran","Retail Customer",3100.50);
		PreferredCustomer customerMore3=new PreferredCustomer("Arti","Patel","Preferrent Customer",10450.00,10);
	
		System.out.println();

		//Print each new Customer object calling the toString() method. 
		System.out.println(customerMore1.toString());
		System.out.println(customerMore2.toString());
		System.out.println(customerMore3.toString());
		
		//Use the setter methods to make the following changes
		customerMore1.setTotalPurchases(8895.00);
		customerMore1.setDiscountRate(12);
		
		customerMore2.setTotalPurchases(100500.00);
		
		customerMore3.setTotalPurchases(14987.24);
		customerMore3.setLastName("Patel-Ruhil");
		customerMore3.setCashbackRate(13);
		
		//print each new Customer object again. 
		System.out.println(customerMore1.toString());
		System.out.println(customerMore2.toString());
		System.out.println(customerMore3.toString());

		

		
	}

}
