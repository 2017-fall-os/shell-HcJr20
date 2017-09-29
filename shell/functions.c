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


int getSize(char* tokenVec){
  int count = 0;
  for(int i = 0; tokenVec[i] != 0; i++){
    count++;
  }
  return count;
}
char* getInput(char* string){
     write(1, "$ ", 2);
     int size = read(0, string, 1024);
     string[size - 1] = '\0';
}

char* getpath(char** envp){
  
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
char* concat(char* tmp, char* path, char* token){
  int size = getSize(path) + getSize(token) + 2;
  tmp = malloc(size);
  char* t = tmp;
  int i = 0;
  int j = 0;
  while(path[i] != 0){
    t[i] = path[i];
    i++;
  }
  t[i] = path[0];
  i++;
  while(token[j] != 0){
    t[i] = token[j];
    i++;
    j++;
  }

  t[i] = '\0';
  return tmp;  
}
char** copyConcat(char** tokenVec, char* command){
  int size = getSize(command) + 1;
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
void runExecv(char** tokenVec, char** pathVec,char** envp){

  int size = getSize(tokenVec[0]) + 1;

  char* tmp = malloc(size);
  for(int i = 0; i < size; i++){
    if(i == size - 1){
      tmp[i] = '\0';
    }
     tmp[i] = tokenVec[0][i];
  }

  for(int i = 0; pathVec[i] != 0; i++){
       char* command = concat(command, pathVec[i], tmp);
       tokenVec = copyConcat(tokenVec, command);
       execve(command, tokenVec, envp);
       free(command);
     }
  }
void startFork(char** tokenVec, char** pathVec, char** envp){
 
   int process = fork();

   if(process < 0){
       printf("Fork Failed \n");
    }
    else if(process == 0){
      
      // execute command
      execve(tokenVec[0], tokenVec, envp);

      //if not found look in path
      runExecv(tokenVec, pathVec, envp);
      //print error/not found
      printf("Command not found");
    }
    else{
       int waitP = wait(NULL);
       
    }
}
 
void freeTokenVec(char** tokenVec, char* string){
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
