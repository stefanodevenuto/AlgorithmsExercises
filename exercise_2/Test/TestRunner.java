package Test;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class TestRunner {
	public static void main(String[] args) {
    	Result result = JUnitCore.runClasses(editDistanceTests.class);

		if(result.wasSuccessful())
			System.out.println("Tests completed successfully");
		else
			for (Failure failure : result.getFailures()){
        		System.out.println(failure.toString());
			}
   }
}