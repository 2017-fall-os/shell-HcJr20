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

// get size of a string/token
int getSize(char* string){
  int count = 0;
  for(int i = 0; string[i] != 0; i++){
    count++;
  }
  return count;
}
// get user input 
char* getInput(char* string){
     write(1, "$ ", 2);
     int size = read(0, string, 1024);
     string[size - 1] = '\0';
}
// get the path from the enviroment variables
char* getpath(char** envp){
  int pathIndex = -1;
  for(int i = 0; envp[i] != 0; i++){
    if(envp[i][0] == 'P' && envp[i][1] == 'A'
       && envp[i][2] == 'T' && envp[i][3] == 'H'){
      pathIndex = i;
    }
  }
  if(pathIndex == -1){
    printf(" PATH not found");
    return NULL;
  }
  
  char** tmpVec = mytoc(envp[pathIndex],'=');
  
  return tmpVec[1];
}
// build token vector of PATH
char** buildPathTokenVector(char** envp, char delim){
         char* path =  getpath(envp);
         char ** pathVec = mytoc(path, ':');
         pathTokenSize= getVectorSize();
	 return pathVec;
}
// build any token vector
char** buildTokenVector(char* string, char delim){
     char ** token = mytoc(string , delim);
     tokenVecSize = getVectorSize();
     setTrackers(0);
     return token;
}
// checks if user clicked exit
int checkExit(char* str, char* exit){
  int exitSwitch = 1;
  for(int i = 0; str[i] != 0; i++){
    if(str[i] != exit[i]){
      exitSwitch = 0;
    }
  }

  return exitSwitch;
}
// concat tokenVec[0] to one of the tokens in the PATH tokenVec
char* concat(char* command, char* path, char* token){
  int size = getSize(path) + getSize(token) + 2;
  command = malloc(size);
  char* t = command;
  int i = 0;
  int j = 0;

  while(path[i] != 0){
    command[i] = path[i];
    i++;
  }
  command[i] = path[0];
  i++;
  while(token[j] != 0){
    command[i] = token[j];
    i++;
    j++;
  }

  command[i] = '\0';
  return command;  
}
// (@see concat) will get assign tokenVec[0] to a new string
char** copyConcat(char** tokenVec, char* command){
  int size = getSize(command) + 1;
  // clear tokenVec[0]
  tokenVec[0] = '\0';
  tokenVec[0] = malloc(size);

  int i = 0;
  while(i < size){
    if(i == size - 1){
      tokenVec[0][i] = '\0';
    }
    else{
      tokenVec[0][i] = command[i];
    }
    i++;
  }
  
  return tokenVec;
}
// this will iterate trough Path token vector(pathVec) and will concatenate tokenVec[0] to path tokens and will try to run execve
void runExecve(char** tokenVec, char** pathVec,char** envp){

  int size = getSize(tokenVec[0]) + 1;

  // store a temporary pointer to store original value of tokenVec[0]
  char* tmp = malloc(size);
  for(int i = 0; i < size; i++){
    if(i == size - 1){
      tmp[i] = '\0';
    }
     tmp[i] = tokenVec[0][i];
  }
  // try to find the command in path
  
  for(int i = 0; pathVec[i] != 0; i++){

      // concat path[i] and token[0]
       char* command = concat(command, pathVec[i], tmp);

       // the original value of tokenVec[0] will be lost in this reassignment;
       tokenVec = copyConcat(tokenVec, command);
      
       execve(command, tokenVec, envp);

       //free command
       free(command);
     }
  }
// begin forking for non background processes
void startFork(char** tokenVec, char** pathVec, char** envp){
 
   int process = fork();

   if(process < 0){
       printf("Fork Failed \n");
    }
    else if(process == 0){
      
      // execute command
      execve(tokenVec[0], tokenVec, envp);

      //if not found look in path
      runExecve(tokenVec, pathVec, envp);
      //print error/not found
      printf("Command not found");
    }
    else{
       int waitP = wait(NULL);
       
    }
}
// exectue fork with background processes
void startBackgroundProcess(char** tokenVec, char** pathVec, char** envp){

  int process = fork();

   if(process < 0){
       printf("Fork Failed \n");
    }
    else if(process == 0){
      
      // execute command
      execve(tokenVec[0], tokenVec, envp);

      //if not found look in path
      runExecve(tokenVec, pathVec, envp);
      //print error/not found
      printf("Command not found");
    }
    else{
      return;
       
    }
}
void startPipe(char** firstCommand,char** secondCommand, char** path, char** envp){
  int* pipeFDS = (int *) calloc(2, sizeof(int));
  pipe(pipeFDS);
  int pid = fork();
  if(pid < 0){
    printf("Fork failed \n");
  }
  else if(pid == 0){
  
       close(1);
       int origSysInput = dup(pipeFDS[1]);
       close(pipeFDS[0]);
       close(pipeFDS[1]);
       runExecve(firstCommand, path, envp);
       exit(2);
    }
  else{
    
    int waitP = wait(NULL);
    int pid2 = fork();
    if(pid2 < 0){
      printf("Fork Failed \n");
    }
    else if(pid2 == 0){
      close(0);
      int origSysReader = dup(pipeFDS[0]);
      close(pipeFDS[0]);
      close(pipeFDS[1]);
      runExecve(secondCommand, path, envp);
    }
    else{
      int waitP2 = wait(NULL);
      }
   }
}
// checks if the input containts a '&' to determine whether or not its a background process
int itsBackgroundProcess(char* string){
  for(int i = 0; string[i] != 0; i++){
    if(string[i] == '&'){
      return 1;
    }
  }
  return 0;
}
// free up any tokenVectors that were calloced
void freeTokenVec(char** tokenVec, char* string){
       for(int i = 0; i < tokenVecSize; i++){
           free(tokenVec[i]);
       }
       memset(string, 0, getSize(string));
       free(tokenVec);
       setTrackers(0);
}
// print the contents of a token vector
void printTokenVec(char** tokenVec){
   for(int i = 0; tokenVec[i] != 0; i++){
     
    write(1, tokenVec[i], getSize(tokenVec[i]));
    printf("\n");
  }
}
// check if user entered "cd" returns 1 for true 0 for false
int checkItsCD(char* cd){
  if(cd[0] == 'c' && cd[1] =='d'){
    return 1;
  }
  return 0;
}
// check the word count of a pipe command
int checkPipeSize(char** pipe){
  int counter = 0;
  for(int i = 0; pipe[i] != 0; i++){
    counter ++;
  }
  return counter;
}
// checks if user inputed a pipe
int commandHasPipe(char* string){
  int foundPipe = 0;
  for(int i = 0; string[i] != 0; i++){
    if(string[i] == '|'){
      foundPipe = 1;
    }
  }
  return foundPipe;
}
// removes ampersand from user input to execute the command when calling execve() 
void removeAmpersand(char** tokenVec){
  for(int i = 0; tokenVec[i] != 0; i++){
    if(tokenVec[i][0] == '&'){
      printf("Removed the ampersand \n");
      tokenVec[i] = '\0';
      return;
    }
  }
}
