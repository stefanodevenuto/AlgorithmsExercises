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

	// Get the words and store them 
	public static ArrayList<String> loadData(String[] args, int index) throws Exception{

		if(args.length != 2){
			throw new IllegalArgumentException("Error on Argument Number (Must be 2)\n");
		}

		Scanner s = new Scanner(new File(args[index]));
		ArrayList<String> list = new ArrayList<String>();
		while (s.hasNext()){
		    list.add(s.next().replaceAll("[.,:]","").toLowerCase());
		}
		s.close();

		return list;
	}

	// Get the best distances between the to-be-corrected word and the dictionary words
	public static ArrayList<ArrayList<StringDistance>> getDistances(ArrayList<String> dictionaryList, ArrayList<String> correctMeList){
		ArrayList<ArrayList<StringDistance>> distances = new ArrayList<ArrayList<StringDistance>>();
		int min;

		for(int i = 0; i < correctMeList.size(); i++){
			distances.add(new ArrayList<StringDistance>());
		}

		for(int i = 0; i < correctMeList.size(); i++){
			min = Integer.MAX_VALUE;
      		for(String dictionaryWord : dictionaryList){
      			int distance = EditDistance.editDistanceDyn(correctMeList.get(i), dictionaryWord);

      			if(distance < min){
      				distances.get(i).clear();
      				min = distance;
      			}

      			if(distance == min)
      				distances.get(i).add(new StringDistance(dictionaryWord, distance));

      			if(distance == 0) break;
      		}
      	}

      	return distances;
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
	      	printResults(distances, correctMeList);

	    }catch(Exception e){
	    	System.out.println(e);
	    	printUsage();
	    }
	}
}
