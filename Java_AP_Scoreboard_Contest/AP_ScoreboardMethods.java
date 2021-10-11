/**
 * Program: AP_ScoreboardMethods
 * Purpose: This will be our very own 'HELPER' or 'UTILITY' class which will just hold some useful methods that we can call to do things for us
 * METHOD PHILOSOPHY: a method should just do one thing, but it do it very well
 * Author: Agnita Paul
 * Date: 07 April, 2021 
 */

public class AP_ScoreboardMethods {
	
	/**
	 * Method Name: SubmissionValidity()
	 * Purpose: a public class method that validates submission file's team ID, time, and problem ID
	 * Accepts: three int: teamID, time, and problemNumber
	 * Returns: boolean true and false. If the values are valid , it will return true else false.
	 * Author/Date: Agnita Paul, 07 April, 2021
	 */

	public static boolean SubmissionValidity(int teamID, int time, int problemNumber,int totalTeam,int totalProblem,int totalContestTime) {
		
		if( teamID>= 1 && teamID <=totalTeam) {
			if(time >=0 && time <= totalContestTime) {
				if(problemNumber >= 1 && problemNumber <= totalProblem) {
					
					return true;
					
				}
			}
		}
		return false;
	}
	
	
	/**
	 * Method Name: totalNumberProblemSolved()
	 * Purpose: a public class method that counts the total number of problem solved
	 * Accepts: one array and two int: int[][]timeArray ,int teamNumber, int totalProblem
	 * Returns: the total number of problem solved
	 * Author/Date: Agnita Paul, 07 April, 2021
	 */

	
	public static int totalNumberProblemSolved(int[][]timeArray ,int teamNumber, int totalProblem) {
		
		int numberProblemSolved=0;
		
		for(int i=1;i<=totalProblem;i++) {
			
			if(timeArray[teamNumber][i]>0) {
				
				numberProblemSolved++;
			}
			
		}
		return numberProblemSolved;
	}
	
	
	/**
	 * Method Name: totalTimeNeededTeam()
	 * Purpose: a public class method that counts the total time needed per team.
	 * Accepts: two arrays and three int: int[][]timeArray, int[][]submissionCountArray,int teamNumber, int totalProblem, int penalty
	 * Returns: the total time needed per team.
	 * Author/Date: Agnita Paul, 07 April, 2021
	 */


	
	public static int totalTimeNeededTeam (int[][]timeArray, int[][]submissionCountArray,int teamNumber, int totalProblem, int penalty) {
		
		int totalTimeTeam=0;
		
		for(int i=1;i<=totalProblem;i++) {
			
			if(timeArray[teamNumber][i]>0) {
				
				totalTimeTeam += timeArray[teamNumber][i]+(penalty*(submissionCountArray[teamNumber][i]-1));
			}
			
		}
		
		return totalTimeTeam;
	}
	
	
	
	
	
}
