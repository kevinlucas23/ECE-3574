
Project 1: note
Assigned: 	1/21
Due: 	2/3

GitHub Invitation Link.

Accept the GitHub invitation, wait until you get an email saying the import is complete, and then clone the git repository to your local machine.

The goal of this assignment is to refresh your programming skills and recall material from ECE 1574/2574. You can also use this to gauge how well you are prepared for the course and calibrate your skill level to my time estimates. If you cannot complete the program, you should drop.
Description

You are a busy person. You need a handy way to track your notes. You will write a program to help you do this called note [1].

note is a text-mode (command-line) application that manages a plain text file holding your tasks. It allows you to do three basic things: add a note with a description; list notes, and mark notes as done.

The basic usage is as follows:

note [-f file] [-p priority] command

The -f file says which file to use for storage. If not present, this defaults to the file note.txt in the current directory. The -p priority option is valid only for add command.

Then in the listing

Command can be one of:

    add - add a note to the file, all remaining text is considered the description. It could have an optional -p priority, which is the priority of a note where priority is between 1-10. If not priority was given then it would use 5. The lower the number the more important the note.
    list - list all notes line-by line in the format below, if any text remains after this command it is an error. The higher priority items (i.e., lower priority number) should come first. If two notes had the same priority the newly added note would come after the last note with the same priority. Completed notes should be listed last.
    mark - marks the note on specified line as done, marking a note twice does nothing

Format for list command:

lineno:[x] note description

where the x is printed inside the brackets for notes marked done and a space for those not.

Examples:

List all notes stored in the default file.

% note list

List all notes in the file last_semester.txt.

% note -f last_semester.txt list

Add some notes, then list them, then make one as done, then list again.

% note add start HW 0
% note add "read first chapter for class"
% note -p 3 add "ask about templates during office hours"
% note list
1:[ ][3] ask about templates during office hours
2:[ ][5] start HW 0
3:[ ][5] read first chapter for class
% note mark 2
% note list
1:[ ][3] ask about templates during office hours
2:[ ][5] read first chapter for class
3:[x][5] start HW 0

Building and testing the starter code in the reference environment

Prerequisites:

    You have completed Exercise 01: Setup and have a working installation of VirtualBox and Vagrant
    You have read through the Vagrant Getting Started guide.

Steps:

    Create a working directory for your project somewhere on your computer. Open your command line terminal and make a working directory. Then change to that directory.

    Clone the todo project after accepting the GitHub invitation at this link.

    git clone https://github.com/XXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    where USER is your GitHub username. You may have to enter your GitHub username and password.

    Change to the repository directory and run vagrant to setup the virtual machine.

    vagrant up

    This will take a several minutes to complete.

    After step 3 completes. Halt the VM using:

    vagrant halt

    This is how you stop the reference environment, but leave it ready to start up again.

    Restart the VM using step 3 again. You should now see a graphical window.

    Open a command line in the VM window by right clicking and selecting Terminal emulator.

    See what directory you are in

    pwd

    You are in the /home/vagrant directory. This is the home directory for the default user setup by Vagrant. Feel free to just remove the default directories created using rm -r *.

    List the files in the host operating system shared with the machine.

    ls /vagrant

    You should see the files from the cloned repsitory.

    Build the starter code using cmake.

    cmake /vagrant

    Then

    cmake --build .

    or just

    make

    To configure and run the build in strict mode (increased warnings, warnings become errors)

    cmake -DSTRICT=True /vagrant
    make clean; make

    Run the todo executable

    ./note

    Go back to your host command line and halt the machine.

    vagrant halt

    When you no longer need the machine or want to recreate it from scratch, you can destroy it.

    vagrant destroy

    It prompts you to be sure.

    Now, use git to commit the source file you changed to the local repository.

    git add todo.cpp
    git commit -m "Implement an argument parser"

    Finally, use git push to synchronize the repository with that on GitHub

    git push

    You may have to enter your GitHub username and password.

Submission

To submit your milestone:

    Tag the git commit that you wish to be considered for grading as final.

    git tag final

    Push this change to GitHub

    git push origin final

If you need to tag a different version of your code simply create and push a new tag appending a monotonically increasing number to final using ‘-‘, e.g. final-2, final-3, etc.

Be sure you have committed all the changes you intend to. You should re-clone your repository into a separate directory and double check it is what you intend to submit. Failure to complete these steps by the due date will result in a failed submission.
Grading

    Code compiles in the reference environment: 5 points
    Test code quality and coverage: 10 points
    Code correctness: 30 points
    Code quality: 5 points
    Good development practices: 5 points

Total: 55 points

Grading Notes:

    If your code does not build in the reference environment you will receive no points.
    Correctness is determined by the proportion of instructor tests that pass (5 points each).
    Code quality means your code compiles with no warnings at a high-warning level (STRICT in the reference environment) and your unit tests have no memory leaks, as well as other criteria mentioned in class (function length, variable naming, etc).
    Good development practices is assessed by looking for regular, incremental, and well-packaged commits.

Notes:

[1] This was inspired by Notion.
