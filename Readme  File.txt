CS 5348 
Operating Systems Concepts
Project 1
Exploring Multiple Processes and IPC

Name: Madhusudan Pranav Venugopal
UTD id: 2021163441
netid: mxv130430

The project folder contains the folowing documents in it:

1. Source code ( CS5348_project1_programcode_Madhusudan_Pranav_Venugopal.cpp)
2. sample1.txt - ( sample test file for generating A-z and 1-10)
3. sample2.txt - ( sample test file for generating smiley face)
4. sample3.txt - ( sample test file for generating 10 iterations containing A followed by a number which is increased everytime an interrupt occurs)
5. sample4.txt - ( sample test file for generating a car) 
6. Project Summary - ( File mentioning purpose of project, implementation of project, outputs and personal experience while doing the project)
7. Readme file

Steps for compiling and executing the project:

Step 1: Open a text editor and paste the source code in it
Step 2: Save the file as <filename.cpp>
eg: 
CS5348.cpp
Step 3: Compile the file using the instruction 

g++ <filename.cpp> -o <filename>

eg:
 g++ CS5348.cpp -o CS5348

Step 4: Run the project using the instruction
./<filename> <sample filename.txt> <interrupt timer value>

or
<filename> <sample filename.txt> <interrupt timer value>
 
eg:

./CS5348 sample1.txt 20

or 
CS5348 sample1.txt 20

Step 5: Repeat step 4 for the reaming sample test files to get the various outputs
