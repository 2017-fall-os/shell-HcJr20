#ifndef TOKENIZER_H
#define TOKENIZER_H

void setTrackers(int i);
int getVectorSize();
char* stringcpy(char* tokenVec, char *str, char delim);
int letterCount(char *str, char delim);
int count(char *str, char delim);
char** mytoc(char* str, char delim);

#endif
