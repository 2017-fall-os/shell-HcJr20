#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int getSize(char* tokenVec);
char* getInput(char* string);
char* getpath(char** envp);
char** buildPathTokenVector(char** envp);
char** buildTokenVector(char* string);
int checkExit(char* str, char* exit);
char* concat(char *tmp, char *path, char *token);
char** copyConcat(char** tokenVec, char* command);
void runExecv(char** path, char** tokenVec,char** envp);
void startFork(char** token, char** path, char** envp);
void freeTokenVec(char** tokenVec, char* string);
void printTokenVec(char** tokenVec);

#endif
