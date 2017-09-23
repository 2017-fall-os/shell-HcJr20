#include <sys/types.h>		/* for lseek, read */
#include <unistd.h>		/* for lseek, read */
#include <sys/stat.h>		/* for read */
#include <fcntl.h>		/* for read */
#include <stdlib.h>		/* for malloc */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "tokenizer.h"



// compare to check for exit
int checkExit(char* str, char* exit){
  int exitEnabled = 1;
  for(int i = 0; str[i] != 0; i++){
    if(str[i] != exit[i]){
      exitEnabled = 0;
    }
  }

  return exitEnabled;
}

void startFork(char** token, char** path){
printf("entered startFork\n");
struct stat command;
int found = stat(token[0], &command) == 0 && command.st_mode & S_IXOTH;
if(found){
    printf("Hello Poochy You are about to fork");
    int process = fork();
    if(process < 0){
       printf("Fork Failed \n");
    }
    else if(process == 0){
       printf("In child process");
    // execve(token[0], token); 
    }
    else{
       int waitP = wait(NULL);
       printf("In parent process");
    }
}
 else if(!found){
      for(int i = 0; PATH != 0; i++){
          
      }
    }
}

int main(int argc, char** argv, char**envp){
  int run = 1;
  char* exit = "exit";
  char string[100];
  // make program exit by typing exit
  while(run){
    // take user input
    write(1, "$ ", 2);
    int size = read(0, string, sizeof string);
    string[size - 1] = '\0';
    printf("Current String: %s \n", string);
    // check if exit entered
     if(checkExit(string, exit)){
      break;
    }   
     // build tokenizer
 
       char ** token = mytoc(string , ' ');
       
    
       char* getpath = getenv("PATH");
       char ** path = mytoc(getpath, ':');
       printf("This is the char at 0,0: %c \n", token[0][0]); 
       startFork(token, path);

    // free up the space
       for(int i = 0; i < getVectorSize(); i++){
          
	  free(token[i]);
       } 
         memset(string, 0, size - 1);
         free(token);

       //reset globals in tokenizer.c
	
       setTrackers(0);
   }
    return 0;
}
