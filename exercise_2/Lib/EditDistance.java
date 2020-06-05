package Lib;

import java.util.Arrays;

/**
* <h1>EditDistance</h1>
* The EditDistance class implements two version of the edit distance alghoritm,
* the first in the classic way and the second with dynamic programming.
* <p>
*
* @author  De Venuto Stefano
* @version 1.0
* @since   2020-06-05
*/

public class EditDistance{

	private static int min(int a, int b, int c){
		return Math.min(a, Math.min(b,c));
	}

	private static int editDistanceImplementation(String str1, String str2, int i, int j){
		if(str1.length() == i)
			return str2.length() - j;
		if(str2.length() == j)
			return str1.length() - i;

		return min(1 + editDistanceImplementation(str1, str2, i, j+1), 1 + editDistanceImplementation(str1, str2, i+1, j), str1.charAt(i) == str2.charAt(j) ? editDistanceImplementation(str1, str2, i+1, j+1) : Integer.MAX_VALUE);
	}

	private static int editDistanceDynImplementation(String str1, String str2, int i, int j, int[][] memo){
		
		if(str1.length() == i){
			return memo[i][j] = str2.length() - j;
		}

		if(str2.length() == j){
			return memo[i][j] = str1.length() - i;
		}

		if (memo[i][j] != -1) 
        	return memo[i][j];

		if(str1.charAt(i) == str2.charAt(j))
			return memo[i][j] = min( 1 + editDistanceDynImplementation(str1, str2, i,j + 1, memo), 1 + editDistanceDynImplementation(str1, str2, i + 1,j, memo), editDistanceDynImplementation(str1, str2, i + 1,j + 1, memo));
		else
			return memo[i][j] = Math.min( 1 + editDistanceDynImplementation(str1, str2, i,j + 1, memo), 1 + editDistanceDynImplementation(str1, str2, i + 1,j, memo));

	}

	/**
	* <h1>editDistance</h1>
	* The editDistance function implements the edit distance alghortim the classic way.
	* It takes the two strings and compute the distance.
	*
	* @param str1 The first string to use 
	* @param str2 The second string to use
	* @return int The distance of the two ones.
	*/
	public static int editDistance(String str1, String str2){

		return editDistanceImplementation(str1, str2, 0, 0);
	}


	/**
	* <h1>editDistanceDyn</h1>
	* The editDistanceDyn function implements the edit distance alghortim with the use of the dynamic programming.
	* It takes the two strings and compute the distance.
	*
	* @param str1 The first string to use 
	* @param str2 The second string to use
	* @return int The distance of the two ones.
	*/
	public static int editDistanceDyn(String str1, String str2){

		int[][] memo = new int[str1.length() + 1][str2.length() + 1];

		for(int i = 0; i < str1.length(); i++)
			Arrays.fill(memo[i], -1);
		
		return editDistanceDynImplementation(str1,str2,0,0,memo);
	}

}


