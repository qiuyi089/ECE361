# ECE 361 Homework #3 -- Binary tree ADT, reading from files, the make utility
## <i>This assignment will be worth 100 points and is due by 10:00 PM on Saturday 14-Nov-2020.  </i>  

### After completing this assignment students should have:
- Developed an application that makes use of a Binary tree ADT
- Gained experience reading and parsing files in C
- Been introduced to MLS professional soccer in the U.S. even though it's the strangest of years


### Introduction

This assignment involves inserting nodes into, and traversing binary trees in a manner that I hope you will find interesting and fun.  The application reads a file containing information on the 2020 MLS season and inserts the information into two binary trees, one for the Eastern Conference teams and another for the Western Conference teams.  The main program of the application traverses the tree(s) and displays "the Table" (the standings) for each conference.  The application also uses the data from both trees to calculate the Shield winner...the team with the best record (in points-per=game) for all of the MLS teams.  Your task is to design and implement a binary tree ADT and then to use that tree in the application.  The details are in the Homework #3 write-up and in all of the starter code that I provided.  The sample code will be helpful in understanding and crafting your ADT.  You are also tasked with providing and using a makefile for building your application.  The example that I reviewed in class today and posted (my makefile from HW #3 in Fall 2019) will help you with that.  

This assignment should be completed by 10:00 PM on Sat 14-Nov-2020.  We are using GitHub Classroom for this assignment so make your final commit to your GitHub private repository for the assignment before the deadline.  Also, please upload a .zip file of your final repository to your Homework #3 dropbox in D2L.  C Source code for your programming solutions should be text files (not .docx, etc.) that have a .c extension.  Header files should be text files that have a .h extension.  Your transcripts (logs) should be submitted as text files (.log) by either redirecting the output from your shell to a file or by using the BASH tee command to send output to both the console and a file (ex: $ echo “hello world” |tee helloworld.log).  You may also copy/paste a transcript into a .txt file and submit that.  The transript should identify yourself, show your make file in operation (make clean, make -n), show the application running successfully w/ nicely formatted Tables. I included a transcript of my application in the test results directory of the release.  You don't have to mimic my output but your output should be recognizable as a list of standings.

 Name all of the files in the repository with descriptive names.  be sure your code is organized indented appropriately, uses meaningful variable names, and includes comments that aid in understanding your code.  Readability of your code will weigh into the score you receive on the assignment.


NOTES:

- If you decide to leverage (borrow) existing code for your solutions other than the code I provided in the release please acknowledge the source. 

- You may, and, in fact, are encouraged to, collaborate with your classmates in the design of the application,  but you are all expected to submit original work.  There is a difference between collaboration and copying - you don't want to be caught doing the latter since that could affect both your final grade and the grade of the student you copied from.

- Please post questions on the assignment to the Homework #3 discussion forum on D2L.  Doing so helps your fellow students understand the assignment, makes it easier for Rishitosh and I to keep up with questions, and avoids the risk that your question will slip out of our view.  You may post anonymously in the forum.

Enjoy


