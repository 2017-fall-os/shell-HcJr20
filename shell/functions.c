#include <sys/types.h>		/* for lseek, read */
#include <unistd.h>		/* for lseek, read */
#include <sys/stat.h>		/* for read */
#include <fcntl.h>
#include <stdlib.h>		/* for malloc */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "tokenizer.h"
#include "functions.h"
#include <sys/wait.h>

int tokenVecSize = 0;
int pathTokenSize = 0;
int size = 0;

char* getInput(char* string){
     write(1, "$ ", 2);
     int size = read(0, string, 1024);
     string[size - 1] = '\0';
     printf("Current String: %s \n", string);
}
char* getpath(char** envp){
  //get path string
}
char** buildPathTokenVector(char** envp){
         char* getPath = getenv("PATH");                   // getpath(envp);
         char ** path = mytoc(getPath, ':');
         pathTokenSize= getVectorSize();
	 return path;
}

char** buildTokenVector(char* string){
     char ** token = mytoc(string , ' ');
     tokenVecSize = getVectorSize();
     setTrackers(0);
     return token;
}

int checkExit(char* str, char* exit){
  int exitSwitch = 1;
  for(int i = 0; str[i] != 0; i++){
    if(str[i] != exit[i]){
      exitSwitch = 0;
    }
  }

  return exitSwitch;
}
void startFork(char** token, char** path){
 
  struct stat command;

  if(stat(token[0], &command) == 0 && command.st_mode & S_IXOTH){
    
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
 else{
      
    }
}
int getSize(char* tokenVec){
  int count = 0;
  for(int i = 0; tokenVec[i] != 0; i++){
    count++;
  }
  return count;
}

void freeTokenVec(char** tokenVec, char* string){
   printf("This is the size of the token: %d \n", tokenVecSize);
       for(int i = 0; i < tokenVecSize; i++){
           free(tokenVec[i]);
       }
       memset(string, 0, getSize(string));
       free(tokenVec);
       setTrackers(0);
}

void printTokenVec(char** tokenVec){

  for(int i = 0; tokenVec[i] != 0; i++){
    write(1, tokenVec[i], getSize(tokenVec[i]));
    printf("\n");
  }
}
