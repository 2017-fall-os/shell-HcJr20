#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int getSize(char* tokenVec);
char* getInput(char* string);
char* getpath(char** envp);
char** buildPathTokenVector(char** envp, char delim);
char** buildTokenVector(char* string, char delim);
int checkExit(char* str, char* exit);
char* concat(char *tmp, char *path, char *token);
char** copyConcat(char** tokenVec, char* command);
void runExecve(char** path, char** tokenVec,char** envp);
void startFork(char** token, char** path, char** envp);
void startBackgroundProcess(char** tokenVec, char** path,  char** envp);
void startPipe(char** firstCommand, char** secondCommand, char** path, char** envp);
void freeTokenVec(char** tokenVec, char* string);
void printTokenVec(char** tokenVec);
int checkItsCD(char* cd);
int checkPipeSize(char** pipe);
int commandHasPipe(char* string);
void removeAmpersand(char** tokenVec);
int itsBackgroundProcess(char* string);

#endif
