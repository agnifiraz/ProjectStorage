/**
 * Program: Programming Contest Scoreboard Ver 1.0
 * Purpose: Show how to code a Java program that obtains data for each submission from the log file then generates and displays a contest scoreboard including a title and column labels .
 * Description: The Project which was given by Stacey Kazmir to submit it before time is up.(The Project of Winter2021 of Programming Fundamantal)
 * Calculates:  a partial scoreboard from 2019.
 * Author name: Agnita Paul
 * Date: 07 April, 2021 
 * 
 *                                               
 * PSEUDO CODE:
 * 1. Create File object and Scanner for submission file   
 * 2. Create File object and Scanner for teams file
 * 3. use nextLine() method to store the title from submission file to a String variable and make it constant
 * 4. use nextInt() method to store the total team number,total problem number,total Contest Time
 *    ,penalty time from submission file to four different variables and make these constant .
 * 5. create some useful variables here before the while loop to read the files so they are not re-created on each iteration
 * 6. A submissions array would hold the number of submissions (an integer) for each problem and for each team. This would be a two-dimensional array with one row for each team and one column for each problem. 
 * 7. A two-dimensional times array would be needed to store the time (an integer) for each problem solved by each team. Again, there would be one row for each team and one column for each problem so it would have the same dimensions as the submissions array.
 * 8. The teams array would be a regular one-dimensional array of Strings with one element per team. This would be populated by reading the teams file and assigning one team name to each element of the array.
 * 9. Make a loop to read submission file
 *    -  store values from the file to calculate the further process
 *    -  validate the values and make a method to calculate.
 *    -  If valid: increment the submissionCountArray and validity counter to keep track of each problems of each teams submission count 
 *    -  If problem solved: store the time value in your timeArray for each team of each problem and also store the solution view(Y)     
 *    -  else valid: increment Invalidity counter
 * 10. close the FileReader Scanner
 * 11. Make another loop to read teams file     
 *    - store the Names of team on timeNameArray
 *    - trim the extra space
 * 12. close the teamReader Scanner
 * 13. Make a method to keep track of total number of correct submission solved per team
 * 14. Make a method to keep track of total time  solved per team
 * 15. print the output by for loop like a the screen shot.
 * 16. print total valid submission and invalid submission                                
 */


import java.util.*;
import java.io.*;
public class AP_Scoreboard {

	public static void main(String[] args) throws FileNotFoundException //confession
	{

		//Create File object for submission file
		File submissions= new File("submissions.txt");
		//Create Scanner for submission file
		Scanner fileReader= new Scanner(submissions);
		
		//Create File object for teams file
		File teamFile=new File("teams.txt");
		//Create Scanner for teams file
		Scanner readTeam= new Scanner(teamFile);
		
		//use nextLine() method to read the title from submission file and make it constant
		String title = fileReader.nextLine();
		//use nextInt() method to read the total team number from submission file and make it constant
		final int TOTAL_TEAM = fileReader.nextInt();
		//use nextInt() method to read the total problem number from submission file and make it constant
		final int TOTAL_PROBLEM = fileReader.nextInt();
		//use nextInt() method to read the total Contest Time from submission file and make it constant
		final int TOTAL_CONTEST_TIME = fileReader.nextInt();
		//use nextInt() method to read the penalty time from submission file
		final int PENALTY = fileReader.nextInt();
		
		//create some useful variables here before the while loop to read the files so they are not re-created on each iteration
		//A submissions array would hold the number of submissions (an integer) for each problem and for each team. This would be a two-dimensional array with one row for each team and one column for each problem. 
		int[][] submissionCountArray = new int[TOTAL_TEAM+1][TOTAL_PROBLEM+1];
		//A two-dimensional times array would be needed to store the time (an integer) for each problem solved by each team. Again, there would be one row for each team and one column for each problem so it would have the same dimensions as the submissions array.
		int[][] timeArray = new int[TOTAL_TEAM+1][TOTAL_PROBLEM+1]; 
		//The teams array would be a regular one-dimensional array of Strings with one element per team. This would be populated by reading the teams file and assigning one team name to each element of the array.
		String[] teamNameArray = new String[TOTAL_TEAM+1];
		// variable to count total invalid submission
		int inValideSubmission=0;
		// variable to count total valid submission
		int valideSubmission=0;
		// variable to call the method "totalNumberProblemSolved"
		int numberProblemSolved ;
		// variable to call the method "totalTimeNeededTeam"
		int totalTimeOfSalutionTeam;
		//variable to keep track of submission value yes or not
		char[][] solutionViewProblemArrays= new char[TOTAL_TEAM+1][TOTAL_PROBLEM+1];
		
		//Loop to read submission file
		while(fileReader.hasNext()) {
			
			// store values from the file to calculate the further process
			int teamID = fileReader.nextInt();
			int time = fileReader.nextInt();
			int problemNumber = fileReader.nextInt();
			char solvedOrUnsolved = fileReader.next().charAt(0);
			
			//validate the values
			if(AP_ScoreboardMethods.SubmissionValidity(teamID, time, problemNumber,TOTAL_TEAM,TOTAL_PROBLEM,TOTAL_CONTEST_TIME)) {
				
				//increment the submissionCountArray to keep track of each problems of each teams submission count
				submissionCountArray[teamID][problemNumber]+=1;
				//increment the valid submission value
				valideSubmission++;	
				
				// tracking of input that is solved or not to get the perfect output
             if(solvedOrUnsolved=='Y') {
					
            	 solutionViewProblemArrays[teamID][problemNumber]='Y';
            	 //time of each problem assigning in timeArray[][]
					timeArray[teamID][problemNumber]=time;
					
				}
            
			}
			else {
				//increment the invalid submission value
				inValideSubmission++;
				
			}
				
			
		}
		//close fileReader not to leak memory
		fileReader.close();
		
		//variable to count the teamNameArray[]
		int teamNumber=1;
		//Loop to read team file
		while(readTeam.hasNext()) {
			
			readTeam.next(); //buffer flash
			//storing the name in the timeNameArray
			teamNameArray[teamNumber] = readTeam.nextLine();
			//to trim the extra spaces
			teamNameArray[teamNumber]=teamNameArray[teamNumber].trim();
			// increment the array index 
			teamNumber++;
			
		}
		//close readTeam not to leak memory
		readTeam.close();
		
		// Prints the lines of the program as shown in the output.
		System.out.println(title);
		
		System.out.println();
		
		System.out.println("Team                "+ "Slv/Time     "+"   P1   "+"  P2    "+" P3  "+"   P4    "+" P5   "+"  P6   "+"  P7   "+"  P8    "+" P9    "+" P10   "+" P11    ");

		System.out.println();

		// printing the output by for loop
		for(int teamNumberRow=1; teamNumberRow<= TOTAL_TEAM; teamNumberRow++ ) {
			
			//calling the methods
			numberProblemSolved= AP_ScoreboardMethods.totalNumberProblemSolved(timeArray,teamNumberRow,TOTAL_PROBLEM);
			totalTimeOfSalutionTeam = AP_ScoreboardMethods.totalTimeNeededTeam(timeArray, submissionCountArray,teamNumberRow,TOTAL_PROBLEM,PENALTY);

			//output values with proper spaces
			System.out.printf("%-20s %7s",teamNameArray[teamNumberRow],numberProblemSolved+"/"+totalTimeOfSalutionTeam);

			System.out.print("    ");
			for(int problemColomn=1; problemColomn <= TOTAL_PROBLEM; problemColomn++) {
				//to print the problem solved or not
				if(!(solutionViewProblemArrays[teamNumberRow][problemColomn]=='Y')) {
					
					solutionViewProblemArrays[teamNumberRow][problemColomn]='N';
				}
			
				//printing the output
	           	 System.out.printf("%7s",solutionViewProblemArrays[teamNumberRow][problemColomn]+"/"+submissionCountArray[teamNumberRow][problemColomn]);

				
				
			}// end 1st loop
			System.out.println();
		}// end 1st loop
		
		//printing total valid submission and invalid submission
		System.out.println(valideSubmission+ " valid submission(s) were processed.");
		System.out.println(inValideSubmission+ " submission(s) were invalid and ignored.");
				
	}

}
