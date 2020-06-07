

all: project/lib/EditDistance.class project/test/EditDistanceTests.class project/test/TestRunner.class project/app/EditDistanceApp.class

clean:
	$(RM) -rf project

project/lib/EditDistance.class: lib/EditDistance.java
	javac -d project lib/EditDistance.java

project/test/EditDistanceTests.class: test/EditDistanceTests.java
	javac -d project -cp .:Resources/Java/JUnit/junit-4.12.jar:Resources/Java/JUnit/hamcrest-core-1.3.jar test/EditDistanceTests.java

project/test/TestRunner.class: test/TestRunner.java
	javac -d project -cp .:Resources/Java/JUnit/junit-4.12.jar:Resources/Java/JUnit/hamcrest-core-1.3.jar test/TestRunner.java

project/app/EditDistanceApp.class: src/EditDistanceApp.java
	javac -d project src/EditDistanceApp.java

