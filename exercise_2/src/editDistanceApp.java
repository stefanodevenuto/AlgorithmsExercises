package App;

import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;
import Lib.EditDistance;

// Structure to store Data File
class StringDistance{
	public String word;		// The string in the dictionary
	public int distance;	// The distance with 

	public StringDistance(String word, int distance){
		this.word = word;
		this.distance = distance;
	}
}

public class editDistanceApp{

	public static void printUsage(){
		System.out.println("Usage:\njava < path to correctme file > < dictionary path >");
	}

	public static ArrayList<String> loadData(String[] args, int index) throws Exception{

		if(args.length != 2){
			throw new IllegalArgumentException("Error on Argument Number (Must be 2)\n");
		}

		Scanner s = new Scanner(new File(args[index]));
		ArrayList<String> list = new ArrayList<String>();
		while (s.hasNext()){
		    list.add(s.next());
		}
		s.close();

		return list;
	}

	public static ArrayList<ArrayList<StringDistance>> getDistances(ArrayList<String> dictionaryList, ArrayList<String> correctMeList){
		ArrayList<ArrayList<StringDistance>> distances = new ArrayList<ArrayList<StringDistance>>();

		for(int i = 0; i < correctMeList.size(); i++){
			distances.add(new ArrayList<StringDistance>());
		}

		for(int i = 0; i < correctMeList.size(); i++){
      		for(String dictionaryWord : dictionaryList){
      			distances.get(i).add(new StringDistance(dictionaryWord,EditDistance.editDistanceDyn(correctMeList.get(i), dictionaryWord)));
      		}
      	}

      	return distances;
	}

	public static ArrayList<ArrayList<StringDistance>> getMinDistanceArray(ArrayList<ArrayList<StringDistance>> distances){
		ArrayList<ArrayList<StringDistance>> minDistanceArray = new ArrayList<ArrayList<StringDistance>>();

		for(ArrayList<StringDistance> list : distances){
			minDistanceArray.add(getMinDuplicates(list));
		}

		return minDistanceArray;
	}

	public static ArrayList<StringDistance> getMinDuplicates(ArrayList<StringDistance> list){
		ArrayList<StringDistance> minDuplicatesArray = new ArrayList<StringDistance>();
		StringDistance minString = list.get(0);

		for(StringDistance current : list){
			if(current.distance <= minString.distance)
				minString = current;
		}

		for(StringDistance current : list){
			if(current.distance == minString.distance)
				minDuplicatesArray.add(current);
		}

		return minDuplicatesArray;
	}

	public static void printResults(ArrayList<ArrayList<StringDistance>> result, ArrayList<String> strings){
		
		for(int i = 0; i < result.size(); i++){
			ArrayList<StringDistance> stringDistanceArray = result.get(i);
			System.out.format("Word: %15s\tEdit Distance (%d) with: \t{", strings.get(i), stringDistanceArray.get(0).distance);
			for(StringDistance stringDistance : stringDistanceArray){
				System.out.print(stringDistance.word + " ");
			}
			System.out.println("}");
		}

	}

	public static void main(String[] args) {
		try{
			ArrayList<String> correctMeList = loadData(args, 0);
	      	ArrayList<String> dictionaryList = loadData(args, 1);
	      	
	      	ArrayList<ArrayList<StringDistance>> distances = getDistances(dictionaryList, correctMeList);

	      	ArrayList<ArrayList<StringDistance>> minEditDistanceArray = getMinDistanceArray(distances);

	    	printResults(minEditDistanceArray, correctMeList);
	    }catch(Exception e){
	    	System.out.println(e);
	    	printUsage();
	    }
	}
}