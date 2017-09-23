#include <sys/types.h>		/* for lseek, read */
#include <unistd.h>		/* for lseek, read */
#include <sys/stat.h>		/* for read */
#include <fcntl.h>
#include <stdlib.h>		/* for malloc */
#include <stdio.h>
#include "tokenizer.h"

int tracker = 0;
int atracker = 0;
int wordCount = 0;

// set tracker variables
void setTrackers(int i){
 tracker = i;
 atracker = i;
}

// retrieve the number of words in vector
int getVectorSize(){
  return wordCount + 1;
}

// copy string into token vector
char* stringcpy(char* tokenVec, char* str, char delim){
  
  int tvIndex = 0;
  int found = 0;
  int previous = 0;

  while(str[atracker] != 0){

    if(str[atracker] == delim && found){
     
      tokenVec[tvIndex] = (char*)0;
      atracker++;
      
      return tokenVec;
    }
     
    if( (str[atracker] == '\0') && found){
      tokenVec[tvIndex] = (char*)0;
       atracker ++;
       
	return tokenVec;
    }
    if(str[tracker] == delim && !found){
      continue;
    }
    if(str[atracker] != delim){
      tokenVec[tvIndex] = str[atracker];
      tvIndex++;
      found = 1;
    }
    atracker++;
  }
  tvIndex++;
  tokenVec[tvIndex] = (char*)0;
  
  return tokenVec;
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
	  word[i] = letterCount(str, delim) +1;
	  tokenVec[i] = (char*) malloc(sizeof(word[i]));
	  }
	else{
	 tokenVec[i] = (char *)0;
       }
     }
  
     for(int i = 0; i < wordCount + 1; i++){
       if(i != wordCount){
	 tokenVec[i] = stringcpy(tokenVec[i], str, delim);
	 write(1, tokenVec[i], word[i]);
	 write(1, "\n", 1);
       }
       else{
	 tokenVec[i] = (char*)0;
       }
     }
     return tokenVec;
}
