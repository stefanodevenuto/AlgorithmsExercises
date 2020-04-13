package Lib;

import java.util.Arrays;

public class EditDistance{

	private static int min(int a, int b, int c){
		return Math.min(a, Math.min(b,c));
	}

	public static int editDistance(String str1, String str2){
		if(str1.length() == 0)
			return str2.length();
		if(str2.length() == 0)
			return str1.length();

		return min(1 + editDistance(str1, str2.substring(1)), 1 + editDistance(str1.substring(1), str2), str1.charAt(0) == str2.charAt(0) ? editDistance(str1.substring(1), str2.substring(1)) : Integer.MAX_VALUE);
	}

	public static int editDistanceDyn(String str1, String str2){
		
		if(str1 == null && str2 == null) return -1;
		else if(str1 == null) return str2.length();
		else if(str2 == null) return str1.length();

		int[][] memo = new int[str1.length() + 1][str2.length() + 1];

		for(int i = 0; i < str1.length(); i++)
			Arrays.fill(memo[i], -1);
		
		return editDistanceDynImplementation(str1,str2,0,0,memo);
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

}


