
Lab: Shell

Author: Hector Cervantes

Classification: Undergraduate

Date of Submission: 10-8-17

About:
	This program is a prgram the mimics a shell. The shell can execute basic commands, can
	change directories, can run background processes, and it can run pipe commands with only
	one pipe. The capabilities my shell can not handle are: re-assign enviroment variables, basic write to file,
	can not handle multiple pipes. The whole program does use the following method calls pipe, fork, dup, execve,
	wait, close, and chdir.

How to run it:

    - To run the shell program please cd into the "shell" directory
    - enter "make all" to complie the program and retrieve executables
    - enter "make demo" to run the prgoram

Contents:
	In this lab I have three files:
	   Main.c:
		This is the c file that runs my program. It prompts the user to enter a
		command.
	   tokenizer.c:
		This is the file that gets and tokenizes the users input, from main.c, to help
		execute shell commands.

           functions.c:
		This file contains all the functionality to help my shell execute commands given by the user
		and the file also contains functionality to handle the programs lifecycle.
Contributors:
	All of the following people have given me tips as to how to approach my shell lab:
	Ana Garcia, Ricardo Alvarez, Abner Palomino, David Pruitt, and Daniel Cervantes.
	


           