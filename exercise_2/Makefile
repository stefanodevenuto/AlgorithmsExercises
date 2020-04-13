

all: project/Lib/EditDistance.class project/Test/editDistanceTests.class project/Test/TestRunner.class project/App/editDistanceApp.class

clean:
	$(RM) -rf project

project/Lib/EditDistance.class: Lib/EditDistance.java
	javac -d project Lib/EditDistance.java

project/Test/editDistanceTests.class: Test/editDistanceTests.java
	javac -d project -cp .:Resources/Java/JUnit/junit-4.12.jar:Resources/Java/JUnit/hamcrest-core-1.3.jar Test/editDistanceTests.java

project/Test/TestRunner.class: Test/TestRunner.java
	javac -d project -cp .:Resources/Java/JUnit/junit-4.12.jar:Resources/Java/JUnit/hamcrest-core-1.3.jar Test/TestRunner.java

project/App/editDistanceApp.class: src/editDistanceApp.java
	javac -d project src/editDistanceApp.java

