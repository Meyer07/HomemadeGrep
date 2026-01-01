# HomemadeGrep
This is a homemade grep UNIX command implementation for a Systems Programming Homework in C
this program uses some program functions in order to make the program more effecient for time purposes


this program was one of the last in my Systems Porgamming course in C
this program has a two different functions implemented in the program. 

The first one is a helper function that checks if a file found by the search algorithm is a text file
it does this by checking if the file has the text '.txt' in it or not

the second function is the search algorithm used to search the subdirectories of a given directory 
and concatenates any valid directories and their path to be reprinted to the terminal for user information 

the actual main function which utilizes the previous two functions. the function checks for a file to search for in a directory also asked promted by the program
then the program checks for any flags with the C and H commands being mandatory flags of the program with the I flag being optional 
before the flag check the program checks to see if a valid command was given by the user then the program checks if the given directory is a valid directory 

after all of those checks the program runs and checks the directories and prints any found directories and prints the total amount of directories searched to get the information



THis program as you can read from the big comment section at the beginning of the program comment section was kind of a pain in the butt for me because I hate working with files however this homework was sort of built off the previous two homeworks that were scanning different forms of files or words in files. This is just one implementeaiton and a very long one, a firend of mine did the same thing in a little under half the lines of code and used more processes in its implementation however he had more difficulties with bugs in his but he figured them out and got the assignment in. 
