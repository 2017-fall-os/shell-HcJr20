#include <sys/types.h>		/* for lseek, read */
#include <unistd.h>		/* for lseek, read */
#include <sys/stat.h>		/* for read */
#include <fcntl.h>		/* for read */
#include <stdlib.h>		/* for malloc */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "tokenizer.h"
#include "functions.h"

int main(int argc, char** argv, char** envp){

  int run = 1;
  char* exit = "exit";
  char string[1024];
 
  while(run){
     // get user input
     getInput(string);
     
     if(checkExit(string, exit)){
      break;
     }

     char** tokenVec = buildTokenVector(string);
     char** pathVec = buildPathTokenVector(envp);
     //printTokenVec(tokenVec);
     //printTokenVec(pathVec);

     startFork(tokenVec, pathVec, envp);

     freeTokenVec(tokenVec, string);
     
  }
    return 0;
}
