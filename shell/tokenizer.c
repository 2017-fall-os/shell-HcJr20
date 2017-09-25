#include <sys/types.h>		/* for lseek, read */
#include <unistd.h>		/* for lseek, read */
#include <sys/stat.h>		/* for read */
#include <fcntl.h>
#include <stdlib.h>		/* for malloc */
#include <stdio.h>
#include "tokenizer.h"

int tracker = 0;
int strIndex = 0;
int wordCount = 0;

// set tracker variables
void setTrackers(int i){
 tracker = i;
 strIndex = i;
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
  

  while(str[strIndex] != 0){
  if(str[strIndex] == delim && found){
      tokenVec[tvIndex] = '\0';
      strIndex++;
      return tokenVec;
    }
    if(str[strIndex] == delim && !found){
      continue;
    }
    if(str[strIndex] != delim){
      tokenVec[tvIndex] = str[strIndex];
      tvIndex++;
      found = 1;
    }
    strIndex++;
  }

  
  tvIndex++;
  tokenVec[tvIndex] = '\0';
  
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
	 tokenVec[i] = '\0';
       } 
     }
     printf("String being tokenized is: %s \n", str);
     printf("Printing in first loop \n");
     // first print ok
     for(int i = 0; i < wordCount + 1; i++){
       if(i != wordCount){
	 tokenVec[i] = stringcpy(tokenVec[i], str, delim);
	//starts here
	    write(1, tokenVec[i], word[i] - 1);
	    write(1, "\n", 1);
	
       }
        else{
	 tokenVec[i] = '\0';
	 } 
     }
     printf("Outside of first for loop \n");
      for(int i = 0; i < wordCount + 1; i++){
     
           write(1, tokenVec[i], word[i] - 1);
	    write(1, "\n", 1);
	
       
      }
    
     return tokenVec;
}

