#include <sys/types.h>		/* for lseek, read */
#include <unistd.h>		/* for lseek, read */
#include <sys/stat.h>		/* for read */
#include <fcntl.h>
#include <stdlib.h>		/* for malloc */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "tokenizer.h"

int tracker = 0;
int wordCount = 0;

// set tracker variables
void setTrackers(int i){
 tracker = i;
}

// retrieve the number of words in vector
int getVectorSize(){
  return wordCount + 1;
}

// copy string into token vector
void tokenize(char** tokenVec, char* str, char delim){
  // getting rid of double pointer
  int xIndex = 0;
  int yIndex = 0;
  int found = 0;
  int i = 0;
 
  

  while(str[i] != 0){
     
     if(str[i] == delim && found){
      tokenVec[xIndex][yIndex] = '\0';
      xIndex++;
      yIndex = 0;
      found = 0;
      i++;
      continue;
      }
    if((str[i] == delim) && !found){
      i++;
      continue;
       }
    if(str[tracker] != delim){
      tokenVec[xIndex][yIndex] = str[i];
      yIndex ++;
      found = 1;
     
    }
    i++;
   }
}
  



// count the number of letters in each word
int letterCount(char* str, char delim){

  int count = 0;
  int found = 0;

 while(str[tracker] != 0){
    if(str[tracker] == delim && found){
      tracker++;
      return count;
    }
    if( (str[tracker] == '\0') && found){
       tracker++;
      return count;
    }
    if(str[tracker] != delim){
      count ++;
      found = 1;
    }
    tracker++;
  }
  
  return count;
}

// count the number of words
int count(char* str, char delim){
 
  int count = 0;
  int wordFound = 0;
  int previous = 1; // 1 for space

  for(int i = 0; str[i] != 0; i++){
    if( str[i] != delim && previous == 1){
	count ++;
      }
    if(str[i] == delim && previous == 0){ 
    }
    if(str[i] == delim){
      previous = 1;
    }
    else{
      previous = 0;
    }
  }
   
   return count;
}


 // build the token vector 
  char** mytoc(char* str, char delim){
 
     wordCount = count(str, delim);
   
     // allocate memory for 2D vector
     
     char**  tokenVec =(char**) calloc(wordCount + 1, sizeof(char*));
     
     int word[wordCount];
        
     
     for(int i = 0; i < wordCount + 1; i++){
        if(i != wordCount){
	  word[i] = letterCount(str, delim);
	  tokenVec[i] = (char*) malloc(word[i]);
	}
        else{
	 tokenVec[i] = '\0';
       } 
     }

     tokenize(tokenVec, str, delim);  
      
     return tokenVec;
}

