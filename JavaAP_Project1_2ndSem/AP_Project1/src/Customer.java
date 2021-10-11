/**
 * Program: Customer
 * Purpose: This will be our very own 'HELPER' or 'UTILITY' class which will just hold some useful methods that we can call to do things for us
 * METHOD PHILOSOPHY: a method should just do one thing, but it do it very well
 * Author: Agnita Paul
 * Date: 29th june, 2021 
 */
//•	Customer is an abstract superclass
public abstract class Customer {

	private String firstName;
	private String lastName;
	private String customerID;
	private String customerLevel;
	
	//•	incentives() is an abstract method which will be implemented by each subclass of Customer
	public abstract double incentives();
	
	//•	There is one 3-arg constructor
	public Customer(String firstName,String lastName,String customerLevel){
	
		this.firstName=firstName;
		this.lastName=lastName;
		this.customerLevel=customerLevel;
		// call setCustomerID() to initialize the field called customerID.
		setCustomerID(customerID);
	
	}
	
	/**
	  *Method Name: toString()
	  *Purpose: to get a output
	  *Accepts: nothing
	  *Returns: a String value
	  */
	public String toString() {
		
		return this.customerID+", "+this.firstName+" "+ this.lastName+"\n"+
		this.customerLevel;
	}
	
	public String getFirstName() {
		return firstName;
	}
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}
	public String getLastName() {
		return lastName;
	}
	public void setLastName(String lastName) {
		this.lastName = lastName;
	}
	public String getCustomerID() {
		return customerID;
	}
	private void setCustomerID(String customerID) {
		//count the length of word
		int count=0;
		for(int i=0;i<lastName.length();i++) {
			count++;
		}
		//.  A customer’s ID is made up of the first 4 characters of his last name, converted to upper case,
		//If a customer’s last name is less than four characters in length, assign ‘X’ for any outstanding characters.
		char a=0, b = 0,c=0,d=0;
		if(count==2) {
			a=Character.toUpperCase(lastName.charAt(0));
			 b=Character.toUpperCase(lastName.charAt(1));
			 c='X';
			 d='X'; 

		}
		else if(count==3) {
			a=Character.toUpperCase(lastName.charAt(0));
			 b=Character.toUpperCase(lastName.charAt(1));
			 c=Character.toUpperCase(lastName.charAt(2));
			 d='X';
		}
		else if(count==1) {
			a=Character.toUpperCase(lastName.charAt(0));
			 b='X';
			 c='X';
			 d='X';
		}
		else {
			a=Character.toUpperCase(lastName.charAt(0));
			 b=Character.toUpperCase(lastName.charAt(1));
			 c=Character.toUpperCase(lastName.charAt(2));
			 d=Character.toUpperCase(lastName.charAt(3));
		}

		//create arrays to store value
		char[] lastCustomerName= {a,b,c,d};
		int[] randomNumber=new int[5];
		String randomNumberString="";
		for(int i=0;i<5;i++) {
			
			// 5 randomly-generated int’s between 0-9
			randomNumber[i]=(int)(Math.random()*9+0);
			String convertString=Integer.toString(randomNumber[i]);
			randomNumberString+=convertString;
		}

		//generate customerID
		String mainString=  String.valueOf(lastCustomerName)+"-"+randomNumberString;
		this.customerID = mainString;
	}
	public String getCustomerLevel() {
		return customerLevel;
	}
	public void setCustomerLevel(String customerLevel) {
		this.customerLevel = customerLevel;
	}
	
	
}
