#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char* getInput(char* string);
char* getpath(char** envp);
char** buildPathTokenVector(char** envp);
char** buildTokenVector(char* string);
int checkExit(char* str, char* exit);
void startFork(char** token, char** path);
int getSize(char* tokenVec);
void freeTokenVec(char** tokenVec, char* string);
void printTokenVec(char** tokenVec);

#endif
